/**
 * Copyright 2008 Etienne Payet <etienne.payet@univ-reunion.fr>
 *
 * This file is part of NTI.
 *
 * NTI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, version 3 of the License or
 * any later version.
 *
 * NTI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with NTI. If not, see <http://www.gnu.org/licenses/>.
 */


#include "global.h"



/* ----------------------------------------------------------- */

Program *P = NULL;
void *data = NULL;  // data used to perform analyses
bool xml = false, trs = false, srs = false, lp = false;
// Some options regarding TRSs and SRSs:
int direction = 0; // 0 = forwards, backwards and forwards+backwards in parallel
                   // 1 = forwards
                   // 2 = backwards
                   // 3 = forwards+backwards
bool elim = true, var = true;
int k = 1;

/* ----------------------------------------------------------- */

void print_usage( )
{
  cerr << endl
       << "Usage 1: ./nti <file> <time limit> [direction] [elim] [var]" << endl
       << "  Non-termination analysis of the TRS/SRS in the provided file" << endl
       << "  trying, in parallel, forward unfoldings only, backward unfoldings only" << endl
       << "  and forward+backward unfoldings together." << endl
       << "  Result is sent to standard output." << endl
       << "  <file> has one of the following suffixes:" << endl
       << "  - .xml for a TRS or an SRS in the XML syntax"<< endl
       << "  - .trs or .srs for a TRS or an SRS in the old syntax"<< endl
       << "  <file> has to conform to the TPDB syntax specification" << endl
       << "    (see http://termination-portal.org/wiki/TPDB)" << endl
       << "  <time limit> = maximal CPU time in seconds allowed to give an answer." << endl
       << "  [direction] (optional) can be:" << endl
       << "  -forward : prove with forward unfoldings only" << endl
       << "  -backward : prove with backward unfoldings only" << endl
       << "  -both : prove with forward+backward unfoldings together" << endl
       << "  [elim] (optional) can be:" << endl
       << "  -noelim : do not eliminate useless unfolded rules" << endl
       << "  [var] (optional) can be:" << endl
       << "  -novar : do not unfold variable positions" << endl << endl
       << "Usage 2: ./nti <file.pl> <time limit>" << endl
       << "  Non-termination analysis of the logic program in file.pl." << endl
       << "  Result is sent to standard output." << endl
       << "  <file.pl> has to conform to the TPDB syntax specification" << endl
       << "    (see http://termination-portal.org/wiki/TPDB)" << endl
       << "  <time limit> = maximal CPU time in seconds allowed to give an answer." << endl
       << endl;
  exit(EXIT_FAILURE);
}

// A function to read the options for proving
// non-termination of a TRS or SRS:
void read_options( char *s )
{
  if (strcmp(s, "-forward") == 0) direction = 1;
  else if (strcmp(s, "-backward") == 0) direction = 2;
  else if (strcmp(s, "-both") == 0) direction = 3;
  else if (strcmp(s, "-noelim") == 0)  elim = false;
  else if (strcmp(s, "-novar") == 0) var = false;
  else if (strlen(s) >= 4 && s[0] == '-' && s[1] == 'k' && s[2] == '=')
    k = atoi(s+3);
  else print_usage();
}

// The functions that are called when Ctrl+c:
void sigint_handler( int n )
{
  // Exit:
  exit(EXIT_FAILURE);
}

void sigint_handler_proof( int n )
{
  P->display_if_killed(cout);
  // Exit:
  exit(EXIT_FAILURE);
}



/* ----------------------------------------------------------- */

int main( int argc, char* argv[] )
{
  // Ctrl+c:
  signal(SIGINT, sigint_handler);

  // Check command line arguments:
  if (argc < 3) print_usage();
  char *file_name  = argv[1];
  unsigned int l = strlen(file_name);
  if (l >= 4)
    {
      xml = (strcmp(file_name+(l-4), ".xml") == 0);
      srs = (strcmp(file_name+(l-4), ".srs") == 0);
      trs = (strcmp(file_name+(l-4), ".trs") == 0);
    }
  if (l >= 3) lp = (strcmp(file_name+(l-3), ".pl") == 0);
  if (!xml && !srs && !trs && !lp) print_usage();
  if ((xml || srs || trs) && argc >= 4)
    for (int i = 3; i < argc; i++) read_options(argv[i]);

  // Parsing the program:
  Symbtab symbtab;
  Parser  *parser;
  if (xml)
    {
      parser = new ParserXML;
      data   = new Option(direction, elim, var, k);
    }
  if (trs)
    {
      symbtab.insert("RULES", RULES);
      symbtab.insert("->", ARROW);
      symbtab.insert("VAR", VAR);
      parser = new ParserTRS;
      data   = new Option(direction, elim, var, k);
    }
  if (srs)
    {
      symbtab.insert("RULES", RULES);
      symbtab.insert("->", ARROW);
      parser = new ParserSRS;
      data   = new Option(direction, elim, var, k);
    }
  if (lp)
    {
      parser = new ParserLP;
    }
  P = parser->parse(file_name, symbtab);
  delete parser; parser = NULL;

  // Prove non-termination:
  pid_t prove_process = fork();
  if (prove_process < 0) { perror("fork"); exit(EXIT_FAILURE); }
  else if (prove_process)
    {
      pid_t clock_process = fork();
      if (clock_process < 0) { perror("fork"); exit(EXIT_FAILURE); }
      else if (clock_process)
	{
	  // Father waits end of proof:
	  waitpid(prove_process, NULL, 0);
	  // then kill clock_process:
	  kill(clock_process, SIGINT);
	  while (wait(NULL) > 0);
	  // and free memory:
	  if (P) { delete P; P = NULL; }
	}
      else
	{
	  // Sleep 'n' seconds
	  sleep(atoi(argv[2]));
	  // then interrupt non-termination proof:
	  cout << "TIME OUT" << endl;
	  killpg(0, SIGINT);
	  while (wait(NULL) > 0);
	  exit(EXIT_FAILURE);
	}
    }
  else
    {
      // Ctrl+c:
      signal(SIGINT, sigint_handler_proof);
      // Son proves non-termination:
      P->prove(data);
    }

  return EXIT_SUCCESS;
}
