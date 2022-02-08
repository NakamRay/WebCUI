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


/*************************
 *  Tokens for parsing:  *
 *************************/

// General tokens:
#define DONE          256
#define ID            257
#define VAR           258
#define STRING        259
#define INT           260
#define ARROW         261
#define RULES         262

// XML tokens:
#define XML_TAG            263
#define XML_STYLESHEET_TAG 264
#define OPEN_PROBLEM_TAG   265
#define CLOSE_PROBLEM_TAG  266
#define OPEN_TRS_TAG       267
#define CLOSE_TRS_TAG      268
#define OPEN_RULES_TAG     269
#define CLOSE_RULES_TAG    270
#define OPEN_RULE_TAG      271
#define CLOSE_RULE_TAG     272
#define OPEN_LHS_TAG       273
#define CLOSE_LHS_TAG      274
#define OPEN_RHS_TAG       275
#define CLOSE_RHS_TAG      276
#define OPEN_VAR_TAG       277
#define CLOSE_VAR_TAG      278
#define OPEN_FUNAPP_TAG    279
#define CLOSE_FUNAPP_TAG   280
#define OPEN_NAME_TAG      281
#define CLOSE_NAME_TAG     282
#define OPEN_ARG_TAG       283
#define CLOSE_ARG_TAG      284
#define OPEN_SIGN_TAG      285
#define CLOSE_SIGN_TAG     286
#define OPEN_FUNCSYM_TAG   287
#define CLOSE_FUNCSYM_TAG  288
#define OPEN_ARITY_TAG     289
#define CLOSE_ARITY_TAG    290
#define OPEN_STRATEGY_TAG  291
#define CLOSE_STRATEGY_TAG 292
#define OPEN_METAINFO_TAG  293
#define CLOSE_METAINFO_TAG 294
#define OPEN_FILENAME_TAG  295
#define CLOSE_FILENAME_TAG 296

// LP tokens:
#define MODE  297
#define EQ    298


/****************************************************
 *  Size of lexical buffer (max size of a lexeme):  *
 ****************************************************/
#define BSIZE         300


/**********************************************
 *  A class to implement a lexical analyser:  *
 **********************************************/

class Lexan
{
 protected:
  char    *file_name;      // name of the file which is processed
  int     lineno;          // current line number in source file
  int     state, start;
  char    lexbuf[BSIZE];
  int     token_attr;

  // Error handling:
  void         error        ( const string& ) const;
  // Does c correspond to a space?
  bool         is_space     ( char c ) const;

 public:
  // Constructors/Destructor:
  Lexan                     ( ) { file_name = NULL; lineno = 1; };
  virtual      ~Lexan       ( ) {};
  // Lexical analysis:
  void         in_buffer    ( int, int& );
  virtual int  fail         ( ) = 0;
  virtual int  nexttoken    ( istream&, Symbtab& ) = 0;
  // Get/Set:
  int          tokenattr    ( ) const { return token_attr; };
  int          current_line ( ) const { return lineno; };
  virtual void reset        ( char *file_name );
};




/********************************************
 *  A class to implement a program parser:  *
 ********************************************/

class Parser
{
 protected:
  Symbtab      *symbtab;
  int          lookahead;
  Lexan        *lexan;          // a lexical analyser
  char         *file_name;      // the name of the file to parse

  // Error handling:
  void         error       ( const string& s ) const;
  // Does the lookahead match token:
  void         match       ( int token, istream& );

 public:
  // Constructor/Destructor:
  Parser                   ( );
  virtual      ~Parser     ( );
  // Parsing:
  virtual Program* parse   ( char *file_name, Symbtab& ) = 0;
};
