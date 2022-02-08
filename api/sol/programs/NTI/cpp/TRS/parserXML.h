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
 *   done          = {EOF}
 *   anything      = *
 *   xml           = {<?xml ... ?>}
 *   xmlStyleSheet = {<?xml-stylesheet ... ?>}
 *   problem       = {<problem ... >}
 *   endProblem    = {</problem>}
 *   trs           = {<trs ... >}
 *   endTrs        = {</trs>}
 *   rules         = {<rules ... >}
 *   endRules      = {</rules>}
 *   rule          = {<rule ... >}
 *   endRule       = {</rule>}
 *   lhs           = {<lhs ... >}
 *   endLhs        = {</lhs>}
 *   rhs           = {<rhs ... >}
 *   endRhs        = {</rhs>}
 *   var           = {<var ... >}
 *   endVar        = {</var>}
 *   funapp        = {<funapp ... >}
 *   endFunapp     = {</funapp>}
 *   name          = {<name ... >}
 *   endName       = {</name>}
 *   arg           = {<arg ... >}
 *   endArg        = {</arg>}
 *   sig           = {<signature ...>}
 *   endSig        = {</signature}
 *   funcsym       = {<funcsym ... >}
 *   endFuncsym    = {</funcsym>}
 *   arity         = {<arity ...>}
 *   endArity      = {</arity>}
 *   strategy      = {<strategy ...>}
 *   endStrategy   = {</strategy>}
 *   metainfo      = {<metainformation ...>}
 *   endMetainfo   = {</metainformation>}
 *   filename      = {<originalfilename ...>}
 *   endFilename   = {</originalfilename>}
 *   id            = non-empty sequences of characters except spaces and '<'
 *   int           = non-empty sequences of digits
 *
 * Start symbol = S
 *
 * Rules:
 *   Rules:
 *   S     -> X
 *            problem
 *              trs
 *                rules Lr endRules
 *                sig Lsymb endSig
 *              endTrs
 *              strategy id endStrategy
 *              M
 *            endProblem
 *   X     -> xml | xml xmlStyleSheet
 *   Lr    -> epsilon | R Lr
 *   R     -> rule lhs F endLhs rhs T endRhs endRule
 *   T     -> V | F
 *   V     -> var id endVar
 *   F     -> funapp name id endName Largs endFunapp
 *   Largs -> epsilon | arg T endArg Largs
 *   Lsymb -> epsilon | Symb Lsymb
 *   Symb  -> funcsym name id endName arity int endArity endFuncsym
 *   M     -> epsilon | metainfo anything endMetainfo
 */


/**********************************************
 *  A class to implement a lexical analyser:  *
 **********************************************/

class LexanXML: public Lexan
{
 private:
  bool tagStartsWith( const char*, const char* );
  bool endsWith( const char*, const char* );

 public:
  // Lexical analysis:
  int    fail         ( );
  int    nexttoken    ( istream&, Symbtab& );
};


/********************************************
 *  A class to implement a program parser:  *
 ********************************************/

class ParserXML: public Parser
{
  // Parsing:
  void     S        ( istream&, Program& ); // the start symbol to parse a program
  void     X        ( istream& );
  void     Lr       ( istream&, Program& );
  Rule*    R        ( istream& );
  Tree*    T        ( istream& );
  Tree*    V        ( istream& );
  Tree*    F        ( istream& );
  void     Largs    ( istream&, list<Tree*>& );
  void     Lsymb    ( istream& );
  void     Symb     ( istream& );
  void     M        ( istream& );

 public:
  // Constructor:
  ParserXML            ( ) { lexan = new LexanXML; };
  // Parsing:
  Program*     parse   ( char* file_name, Symbtab& );
};
