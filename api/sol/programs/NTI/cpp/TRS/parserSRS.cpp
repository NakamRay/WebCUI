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


#include "../global.h"
#include <fstream>

/******************************************
 *            Lexical analyser            *
 ******************************************/


/* -------------- Lexical analysis: --------------- */

int LexanSRS::fail()
{
  switch (start)
    {
    case 0:  start = 3;  break;
    case 3:  start = 5;  break;
    case 5:  start = 8;  break;
    case 8: error("lexical error"); break;
    default: error("compiler error");
    }
  return start;
}


int LexanSRS::nexttoken( istream& in, Symbtab& symbtab )
{
  int  b, c;
  state = 0; start = 0;
  while (1)
    switch (state)
      {
	/* Delim: */
      case 0:
	c = in.get();
	if (c == EOF) return DONE;
	else if (is_space(c)) {}
	else if (c == '\n') lineno++;
	else state = fail();
	break;
	/* Strings: */
      case 3:
	if (c == '"') { b = 0; state = 4; }
	else state = fail();
	break;
      case 4:
	c = in.get();
	if (c == EOF) error("non-ended string");
	else if (c != '"') in_buffer(c, b);
	else return STRING;
	break;
	/* id + keywords: */
      case 5:
	if (c != ',' && c != '(' && c != ')' && !is_space(c)
	    && c != '\n' && c != '"' && c != EOF)
	  { b = 0; in_buffer(c, b); state = 6; }
	else state = fail();
	break;
      case 6:
	c = in.get();
	if (c != ',' && c != '(' && c != ')' && !is_space(c)
	    && c != '\n' && c != '"' && c != EOF)
	  in_buffer(c, b);
	else state = 7;
	break;
      case 7:
	in.putback(c);
	in_buffer(EOS, b);
	token_attr = symbtab.insert(lexbuf, ID);
	return symbtab.get_token(token_attr);
	/* Other characters: */
      case 8:
	if (c == ',' || c == '(' || c == ')')
	  return c;
	else
	  state = fail();
	break;
	/* Default behavior: */
      default: error("compiler error");
      }
}


/***********************************
 *            ParserSRS            *
 ***********************************/


/* ------------------- Parsing: --------------------- */

// Spec -> done  |  '(' Decl ')' Spec
void ParserSRS::Spec( istream& in, Program& prog )
{
  if (lookahead == '(')
    {
      match('(', in);
      Decl(in, prog);
      match(')', in);
      Spec(in, prog);
    }
  else if (lookahead == DONE)
      match(DONE, in);
  else
    error("syntax error");
}

// Decl -> rules Lr | rules |  id L
void ParserSRS::Decl( istream& in, Program& prog )
{
  if (lookahead == RULES)
    {
      match(RULES, in);
      if (lookahead == ID) Lr(in, prog);
    }
  else if (lookahead == ID)
    {
      match(ID, in);
      L(in);
    }
  else
    error("syntax error");
}

// L -> '->' L | id L | string L | '(' L ')' L | ',' L | epsilon
void ParserSRS::L( istream& in )
{
  if (lookahead == ARROW || lookahead == ID || lookahead == STRING)
    {
      match(lookahead, in);
      L(in);
    }
  else if (lookahead == '(')
    {
      match('(', in);
      L(in);
      match(')', in);
      L(in);
    }
  else if (lookahead == ',')
    {
      match(',', in);
      L(in);
    }
  else
    return; // production L -> epsilon : nothing to do
}

// Lr -> R ',' Lr | R
void ParserSRS::Lr( istream& in, Program& P )
{
  P.push_back(R(in));
  if (lookahead == ',')
    {
      match(',', in);
      if (lookahead == ID) Lr(in, P);
      else error("syntax error");
    }
  else return;
}

// R -> W '->' W  |  W '->'
Rule* ParserSRS::R( istream& in )
{
  Rule *R;

  Tree *l = W(in);
  match(ARROW, in);
  if (lookahead == ID) R = new Rule(l, W(in));
  else R = new Rule(l, new Tree(-1, 0, symbtab));
  return R;
}

// W -> id | id W
Tree* ParserSRS::W( istream& in )
{
  int root = lexan->tokenattr();

  match(ID, in);
  Tree *t = new Tree(root, 1, symbtab);
  if (lookahead == ID) (*t)[0] = W(in);
  else (*t)[0] = new Tree(-1, 0, symbtab);
  return t;
}

// Start parsing:
Program* ParserSRS::parse( char* name, Symbtab& s )
{
  file_name = name;
  lexan->reset(name);
  symbtab = &s;

  ifstream in;
  in.open(name);
  if (!in)
    {
      cerr << "Unable to open file " << name << endl;
      exit(EXIT_FAILURE);
    }

  Program *P = new TRS;

  lookahead = lexan->nexttoken(in, s);
  Spec(in, *P);
  in.close();

  return P;
}
