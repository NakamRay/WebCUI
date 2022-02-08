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
 *   done      = {EOF}
 *   rules     = {RULES}
 *   id        = non-empty sequences of characters except space,
 *               '(', ')', '"' and ',' and excluding special
 *               sequence '->' and keyword RULES
 *   string    = '"' . any_character* . '"'
 *
 * Non-terminal symbols:
 *   Spec = start symbol,
 *   Decl = a declaration
 *   L    = any list
 *   Lr   = list of rules
 *   R    = rule,
 *   W    = word
 *
 * Rules:
 *   Spec -> done  |  '(' Decl ')' Spec
 *   Decl -> rules Lr  |  rules | id L
 *   L  -> '->' L  |  id L  |  string L  |  '(' L ')' L
         | ',' L  | epsilon
 *   Lr -> R ',' Lr  |  R
 *   R  -> W '->' W  |  W '->'
 *   W  -> id  |  id W
 */


/**********************************************
 *  A class to implement a lexical analyser:  *
 **********************************************/

class LexanSRS: public Lexan
{
 public:
  // Lexical analysis:
  int    fail         ( );
  int    nexttoken    ( istream&, Symbtab& );
};


/********************************************
 *  A class to implement a program parser:  *
 ********************************************/

class ParserSRS: public Parser
{
 private:
  // Parsing:
  void     Spec        ( istream&, Program& ); // the start symbol to parse a program
  void     Decl        ( istream&, Program& );
  void     L           ( istream& );
  void     Lr          ( istream&, Program& );
  Rule*    R           ( istream& );
  Tree*    W           ( istream& );

 public:
  // Constructor:
  ParserSRS            ( ) { lexan = new LexanSRS; };
  // Parsing:
  Program*   parse     ( char* file_name, Symbtab& );
};
