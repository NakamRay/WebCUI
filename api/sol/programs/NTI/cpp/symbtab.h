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


/*******************************
 *  Size of the symbol table:  *
 *******************************/

#define LEXEMETAB_SIZE 999     // the maximum size of a lexeme table
#define SYMBTAB_SIZE   200     // the maximum size of a symbol table


/******************************************
 *  A class to implement a symbol table:  *
 ******************************************/

struct Entry
{
  char* lexptr;
  int   token;
  int   info;   // additionnal information
};


class Symbtab
{
 private:
  Entry   symbtab[SYMBTAB_SIZE];     // a symbol table
  int     next_symbtab;              // index of next entry in symbol table
  char    lexemetab[LEXEMETAB_SIZE]; // table of lexemes
  int     last_lexemetab;            // index of last char in lexeme table

  // Error handling:
  void    error          ( const string& );

 public:
  // Constructors/Destructor:
  Symbtab                ( );
  // Get/Set:
  int     lookup         ( const char *s );            // look up in  lexemetab
  int     insert         ( const char *s, int token ); // insert into lexemetab
  int     get_token      ( int index ) const;
  void    set_token      ( int index, int token );
  int     get_info       ( int index ) const;
  void    set_info       ( int index, int info );
  char*   get_lexeme     ( int index ) const;
  int     nb_symb        ( ) const { return next_symbtab; };
  // Output:
  friend  ostream& operator << ( ostream&, const Symbtab& );
};
