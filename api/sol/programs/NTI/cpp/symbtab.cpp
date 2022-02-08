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


/********************
 *  class Symbtab:  *
 ********************/

/* ------------------- Error handling: ---------------------- */

void Symbtab::error( const string& s )
{
  cerr << "Error: " << s << endl;
  exit(EXIT_FAILURE);
}


/* ------------------ Constructor: -------------------- */

Symbtab::Symbtab( )
{
  next_symbtab = 0;
  last_lexemetab = -1;
}


/* ------------------ Get/Set: -------------------- */

int Symbtab::lookup( const char *s )
{
  for (int p = next_symbtab-1; p >= 0; p--)
    if (strcmp(s,symbtab[p].lexptr) == 0) return p;
  return NONE;
}

int Symbtab::insert( const char *s, int token )
{
  int p = lookup(s);
  if (p != NONE) return p;

  if (next_symbtab >= SYMBTAB_SIZE)
    error("Compiler error: symbol table is full!");

  int len = strlen(s);
  if (last_lexemetab + len + 1 >= LEXEMETAB_SIZE)
    error("Compiler error: lexeme table is full!");

  symbtab[next_symbtab].info  = NONE;
  symbtab[next_symbtab].token  = token;
  symbtab[next_symbtab].lexptr = &lexemetab[last_lexemetab+1];
  strcpy(symbtab[next_symbtab].lexptr, s);
  next_symbtab++;
  last_lexemetab = last_lexemetab + len + 1;
  return next_symbtab-1;
}

int Symbtab::get_token( int index ) const
{
  if (index < 0 || next_symbtab <= index)
    ERROR("int Symbtab::get_token(int) const", "index out of range!");
  return symbtab[index].token;
}

void Symbtab::set_token( int index, int token )
{
  if (index < 0 || next_symbtab <= index)
    ERROR("void Symbtab::set_token(int, int)", "index out of range!");
  symbtab[index].token = token;
}

int Symbtab::get_info( int index ) const
{
  if (index < 0 || next_symbtab <= index)
    ERROR("int Symbtab::get_info(int) const", "index out of range!");
  return symbtab[index].info;
}

void Symbtab::set_info( int index, int info )
{
  if (index < 0 || next_symbtab <= index)
    ERROR("void Symbtab::set_info(int, int)", "index out of range!");
  symbtab[index].info = info;
}

char* Symbtab::get_lexeme( int index ) const
{
  if (index < 0 || next_symbtab <= index)
    ERROR("char* Symbtab::get_lexeme(int) const", "index out of range!");
  return symbtab[index].lexptr;
}



/* ------------------- Output: -------------------- */

ostream& operator << ( ostream& out, const Symbtab& T )
{
  out << endl;
  for (int p = T.next_symbtab-1; p >= 0; p--)
    out << p << "\t" << (T.symbtab)[p].lexptr
	<< '\t' << (T.symbtab)[p].token
	<< '\t' << (T.symbtab)[p].info
	<< endl;
  return out;
}
