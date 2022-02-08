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


/**
 * Tokens and lexemes:
 *   done           = {EOF}
 *   id            = lowercase_letter.(digit + letter + '_')*
 *   var           = (uppercase_letter + '_').(digit + letter + '_')^+
 *   anonymous_var = '_'
 *   int           = digit.digit*
 *   mode          = { '%query:' }
 *
 * Non-terminal symbols:
 *   Lr   = list of rules (start symbol),
 *   R    = rule,
 *   U    = Prolog directive
 *   M    = declaration of a mode
 *   La   = list of atoms,
 *   A    = atom,
 *   F    = function,
 *   Lt   = list of trees,
 *   T    = tree,
 *   Li   = Prolog list
 *
 * Rules:
 *   Lr   -> R Lr | U Lr | M Lr | done
 *   R    -> F '.'  | F ':-' La '.'
 *   U    -> ':-' A '.'
 *   M    -> mode F '.'
 *   La   -> A  |  A ',' La
 *   A    -> F  |  T = T
 *   F    -> id  |  id '(' Lt ')'
 *   Lt   -> T  |  T ',' Lt
 *   T    -> F | var | int | Li
 *   Li   -> '[' ']'  |  '[' Lt ']'  |  '[' Lt '|' var ']'
 */


/**********************************************
 *  A class to implement a lexical analyser:  *
 **********************************************/

class LexanLP: public Lexan
{
 private:
  int    var_index;       // an index to handle useless variables '_'
  int    new_var_index   ( ) { return var_index--; };

 public:
  // Constructors:
  LexanLP                ( ) { var_index = -1 * SYMBTAB_SIZE; };
  // Lexical analysis:
  int    fail            ( );
  int    nexttoken       ( istream&, Symbtab& );
  // Get/Set:
  void   reset           ( char *file_name );
};


/********************************************
 *  A class to implement a program parser:  *
 ********************************************/

class ParserLP: public Parser
{
 private:
  // Parsing:
  void      Lr     ( istream&, ProgramLP& );
  Rule*     R      ( istream& );
  void      U      ( istream& );
  Tree*     M      ( istream& );
  void      La     ( istream&, list<Tree*>& );
  Tree*     A      ( istream& );
  Tree*     F      ( istream& );
  void      Lt     ( istream&, list<Tree*>& );
  Tree*     T      ( istream& );
  Tree*     Li     ( istream& );

 public:
  // Constructor:
  ParserLP             ( ) { lexan = new LexanLP; };
  // Parsing:
  Program*  parse      ( char *file_name, Symbtab& );
};
