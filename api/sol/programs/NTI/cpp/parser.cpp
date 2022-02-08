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
#include <fstream>


/******************
 *  class Lexan:  *
 ******************/


/* ------------------- Error handling: ---------------------- */

void Lexan::error( const string& s ) const
{
  cerr << "Error while reading '" << file_name << "'. " << endl
       << "Line " << lineno << ": " << s << '.' << endl;
  exit(EXIT_FAILURE);
}


/* -------------- Does c correspond to a space? --------------- */

bool Lexan::is_space( char c ) const
{
  return (
	  c == ' '  || // space char
	  c == '\t' || // horizontal tab
	  c == '\v' || // vertical tab
	  c == '\r' || // carriage return
	  c == '\f' || // new page
	  c == '\b'    // backspace
	  );
}


/* -------------- Lexical analysis: --------------- */

void Lexan::in_buffer( int c, int& b )
{
  if (b < BSIZE)
    {
      lexbuf[b] = c;
      b = b+1;
    }
  else error("Lexem is too long");
}


/* ------------------- Get/Set: ---------------------- */

void Lexan::reset( char *name )
{
  file_name  = name;
  lineno     = 1;
  for (int i = 0; i < BSIZE; i++) lexbuf[i] = EOS;
}



/*******************
 *  class Parser:  *
 *******************/

/* ------------------- Constructors/Destructor: ---------------------- */

Parser::Parser( )
{
  symbtab   = NULL;
  lookahead = 0;
  lexan     = NULL;
  file_name = NULL;
}

Parser::~Parser( )
{ if (lexan) delete lexan; }


/* ------------------- Error handling: ---------------------- */

void Parser::error( const string& s ) const
{
  cerr << "Error while reading '" << file_name << "'" << endl
       << "Line " << lexan->current_line() << ": " << s << endl;
  exit(EXIT_FAILURE);
}


/* ------------------- Match: --------------------- */

void Parser::match( int tok, istream& in )
{
  if (lookahead == tok) lookahead = lexan->nexttoken(in, *symbtab);
  else error("syntax error");
}
