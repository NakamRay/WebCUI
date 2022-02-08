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
 * Tokens with corresponding lexemes:
 *   done       = {EOF}
 *   var        = {VAR}
 *   rules      = {RULES}
 *   id         = non-empty sequences of characters except space,
 *                '(', ')', '"', ',' and excluding special sequence
 *                '->' and keywords VAR and RULES
 *   string    = '"' . any_character* . '"'
 *
 * Start symbol = Spec
 *
 * Rules:
 *   Spec  -> '(' Decl ')' Spec  |  epsilon
 *   Decl  -> var Lid  |  rules Lr  |  id L
 *   L     -> '->' L  |  id L  |  string L  | '(' L ')' L
 *          |  ',' L  |  epsilon
 *   Lid   -> id Lid | epsilon
 *   Lr    -> R Lr  |  epsilon
 *   R     -> T '->' T
 *   T     -> id  |  id '(' ')'  |  id '(' Lt ')'
 *   Lt    -> T  |  T ',' Lt
 */


/**********************************************
 *  A class to implement a lexical analyser:  *
 **********************************************/

class LexanTRS: public Lexan
{
 public:
  // Lexical analysis:
  int    fail         ( );
  int    nexttoken    ( istream&, Symbtab& );
};


/********************************************
 *  A class to implement a program parser:  *
 ********************************************/

class ParserTRS: public Parser
{
 private:
  bool     var;             // am I in 'parse variables only' mode?
  bool     lvar;            // am I parsing a list of variables ?

  // Parsing:
  void     Spec        ( istream&, Program& ); // the start symbol to parse a program
  void     Decl        ( istream&, Program& );
  void     L           ( istream& );
  void     Lid         ( istream& );
  void     Lr          ( istream&, Program& );
  Rule*    R           ( istream& );
  void     Lt          ( istream&, list<Tree*>& );
  Tree*    T           ( istream& );

 public:
  // Constructor:
  ParserTRS            ( ) { lexan = new LexanTRS; };
  // Parsing:
  Program*     parse   ( char* file_name, Symbtab& );
};
