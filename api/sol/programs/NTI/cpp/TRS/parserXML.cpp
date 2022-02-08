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

int LexanXML::fail()
{
  switch (start)
    {
    case 0:  start = 1;  break;
    case 1:  start = 4;  break;
    case 4: error("lexical error"); break;
    default: error("compiler error");
    }
  return start;
}

// Checks whether the given tag starts with the given prefix
// followed by a space or by the closing tag character '>'.
bool LexanXML::tagStartsWith( const char* tag, const char* prefix )
{
  int l = strlen(prefix);

  if (0 != strncmp(tag, prefix, l) || l >= strlen(tag)) return false;

  // From here, we necessarily have l < strlen(tag).
  char tag_l = tag[l];
  return  (tag_l == '>' || tag_l == '\n' || is_space(tag_l));
}

// Checks whether the given string ends with the given suffix.
bool LexanXML::endsWith( const char *str, const char *suffix )
{
  if (!str || !suffix) return false;

  size_t lenstr = strlen(str);
  size_t lensuffix = strlen(suffix);
  if (lensuffix >  lenstr) return false;
  return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

int LexanXML::nexttoken( istream& in, Symbtab& symbtab )
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
	/* Tags: */
      case 1:
	if (c == '<')
	  {
	    b = 0;
	    in_buffer(c, b);
	    state = 2;
	  }
	else state = fail();
	break;
      case 2:
	c = in.get();
	if (is_space(c)) in_buffer(' ', b);
	else in_buffer(c, b);
	if (c == '>') state = 3;
	break;
      case 3:
	in_buffer(EOS, b);
	// TAG <?xml
	if (strcmp(lexbuf, "<?xml?>") == 0)
	  return XML_TAG;
	else if (tagStartsWith(lexbuf, "<?xml"))
	  {
	    if (endsWith(lexbuf, "?>"))
	      return XML_TAG;
	    else
	      error("tag '<?xml' not ended by '?>'");
	  }
	// TAG <?xml-stylesheet
	else if (tagStartsWith(lexbuf, "<?xml-stylesheet"))
	  {
	    if (endsWith(lexbuf, "?>"))
	      return XML_STYLESHEET_TAG;
	    else
	      error("tag '<?xml-stylesheet' not ended by '?>'");
	  }
	// TAG <problem
	else if (tagStartsWith(lexbuf, "<problem"))
	  return OPEN_PROBLEM_TAG;
	else if (strcmp(lexbuf, "</problem>") == 0)
	  return CLOSE_PROBLEM_TAG;
	// TAG <trs
	else if (tagStartsWith(lexbuf, "<trs"))
	  return OPEN_TRS_TAG;
	else if (strcmp(lexbuf, "</trs>") == 0)
	  return CLOSE_TRS_TAG;
	// TAG <rules
	else if (tagStartsWith(lexbuf, "<rules"))
	  return OPEN_RULES_TAG;
	else if (strcmp(lexbuf, "</rules>") == 0)
	  return CLOSE_RULES_TAG;
	// TAG <rule
	else if (tagStartsWith(lexbuf, "<rule"))
	  return OPEN_RULE_TAG;
	else if (strcmp(lexbuf, "</rule>") == 0)
	  return CLOSE_RULE_TAG;
	// TAG <lhs
	else if (tagStartsWith(lexbuf, "<lhs"))
	  return OPEN_LHS_TAG;
	else if (strcmp(lexbuf, "</lhs>") == 0)
	  return CLOSE_LHS_TAG;
	// TAG <rhs
	else if (tagStartsWith(lexbuf, "<rhs"))
	  return OPEN_RHS_TAG;
	else if (strcmp(lexbuf, "</rhs>") == 0)
	  return CLOSE_RHS_TAG;
	// TAG <var
	else if (tagStartsWith(lexbuf, "<var"))
	  return OPEN_VAR_TAG;
	else if (strcmp(lexbuf, "</var>") == 0)
	  return CLOSE_VAR_TAG;
	// TAG <funapp
	else if (tagStartsWith(lexbuf, "<funapp"))
	  return OPEN_FUNAPP_TAG;
	else if (strcmp(lexbuf, "</funapp>") == 0)
	  return CLOSE_FUNAPP_TAG;
	// TAG <name
	else if (tagStartsWith(lexbuf, "<name"))
	  return OPEN_NAME_TAG;
	else if (strcmp(lexbuf, "</name>") == 0)
	  return CLOSE_NAME_TAG;
	// TAG <arg
	else if (tagStartsWith(lexbuf, "<arg"))
	  return OPEN_ARG_TAG;
	else if (strcmp(lexbuf, "</arg>") == 0)
	  return CLOSE_ARG_TAG;
	// TAG <signature
	else if (tagStartsWith(lexbuf, "<signature"))
	  return OPEN_SIGN_TAG;
	else if (strcmp(lexbuf, "</signature>") == 0)
	  return CLOSE_SIGN_TAG;
	// TAG <funcsym
	else if (tagStartsWith(lexbuf, "<funcsym"))
	  return OPEN_FUNCSYM_TAG;
	else if (strcmp(lexbuf, "</funcsym>") == 0)
	  return CLOSE_FUNCSYM_TAG;
	// TAG <arity
	else if (tagStartsWith(lexbuf, "<arity"))
	  return OPEN_ARITY_TAG;
	else if (strcmp(lexbuf, "</arity>") == 0)
	  return CLOSE_ARITY_TAG;
	// TAG <stragegy
	else if (tagStartsWith(lexbuf, "<strategy"))
	  return OPEN_STRATEGY_TAG;
	else if (strcmp(lexbuf, "</strategy>") == 0)
	  return CLOSE_STRATEGY_TAG;
	// TAG <metainformation
	else if (tagStartsWith(lexbuf, "<metainformation"))
	  return OPEN_METAINFO_TAG;
	else if (strcmp(lexbuf, "</metainformation>") == 0)
	  return CLOSE_METAINFO_TAG;
	// TAG <originalfilename
	else if (tagStartsWith(lexbuf, "<originalfilename"))
	  return OPEN_FILENAME_TAG;
	else if (strcmp(lexbuf, "</originalfilename>") == 0)
	  return CLOSE_FILENAME_TAG;
	// TAG unknown
	else
	  error("unknown tag");
	break;
	/* id + keywords: */
      case 4:
	b = 0;
	in_buffer(c, b);
	state = 5;
	break;
      case 5:
	c = in.get();
	if (c != '<' && !is_space(c) && c != '\n' && c != EOF)
	  in_buffer(c, b);
	else state = 6;
	break;
      case 6:
	// it's an id or a keyword:
	in.putback(c);
	in_buffer(EOS, b);
	token_attr = symbtab.insert(lexbuf, ID);
	return symbtab.get_token(token_attr);
	/* Default behavior: */
      default: error("compiler error");
      }
}



/***********************************
 *            ParserXML            *
 ***********************************/

/* ------------------- Parsing: --------------------- */

/**
 * S -> X
 *      problem
 *        trs
 *          rules Lr endRules
 *          sig Lsymb endSig
 *        endTrs
 *        strategy id endStrategy
 *        M
 *      endProblem
 */
void ParserXML::S( istream& in, Program& P )
{
  X(in);
  match(OPEN_PROBLEM_TAG, in);

  match(OPEN_TRS_TAG, in);
  match(OPEN_RULES_TAG, in);
  Lr(in, P);
  match(CLOSE_RULES_TAG, in);
  match(OPEN_SIGN_TAG, in);
  Lsymb(in);
  match(CLOSE_SIGN_TAG, in);
  match(CLOSE_TRS_TAG, in);

  match(OPEN_STRATEGY_TAG, in);
  match(ID, in);
  match(CLOSE_STRATEGY_TAG, in);

  M(in);

  match(CLOSE_PROBLEM_TAG, in);

  if (lookahead != DONE) error("syntax error");
}

// X -> xml | xml xmlStyleSheet
void ParserXML::X( istream& in )
{
  match(XML_TAG, in);
  if (lookahead == XML_STYLESHEET_TAG)
    match(XML_STYLESHEET_TAG, in);
}

// Lr -> epsilon | R Lr
void ParserXML::Lr( istream& in, Program& P )
{
  if (lookahead == OPEN_RULE_TAG)
    {
      P.push_back(R(in));
      Lr(in, P);
    }
  // production Lr -> epsilon : nothing to do
}

// R -> rule lhs T endLhs rhs T endRhs endRule
Rule* ParserXML::R( istream& in )
{
  match(OPEN_RULE_TAG, in);

  match(OPEN_LHS_TAG, in);
  Tree *lhs = F(in);
  match(CLOSE_LHS_TAG, in);

  match(OPEN_RHS_TAG, in);
  Tree *rhs = T(in);
  match(CLOSE_RHS_TAG, in);

  match(CLOSE_RULE_TAG, in);

  return new Rule(lhs, rhs);
}

// T -> V | F
Tree* ParserXML::T( istream& in )
{
  Tree *t = NULL;

  if (lookahead == OPEN_VAR_TAG) 
    t = V(in);
  else if (lookahead == OPEN_FUNAPP_TAG)
    t = F(in);
  else
    error("<var> or <funapp> expected");

  return t;
}

// V -> var id endVar
Tree* ParserXML::V( istream& in )
{
  match(OPEN_VAR_TAG, in);

  int root = -1 * lexan->tokenattr() - 1;
  match(ID, in);
  Tree *v = new Tree(root, 0, symbtab);

  match(CLOSE_VAR_TAG, in);

  return v;
}

// F -> funapp name id endName Largs endFunapp
Tree* ParserXML::F( istream& in )
{
  match(OPEN_FUNAPP_TAG, in);

  // The root functor:
  match(OPEN_NAME_TAG, in);
  int root = lexan->tokenattr();
  match(ID, in);
  match(CLOSE_NAME_TAG, in);

  // The arguments:
  list<Tree*> args_list;
  Largs(in, args_list);
  
  // Constructs the term:
  Tree *t = new Tree(root, args_list.size(), symbtab);
  int k = 0;
  list<Tree*>::iterator it;
  for (it = args_list.begin(); it != args_list.end(); it++)
    (*t)[k++] = *it;

  match(CLOSE_FUNAPP_TAG, in);
 
  return t;
}

// Largs -> epsilon | arg T endArg Largs
void ParserXML::Largs( istream& in, list<Tree*>& L )
{
  if (lookahead == OPEN_ARG_TAG)
    {
      match(OPEN_ARG_TAG, in);
      L.push_back(T(in));
      match(CLOSE_ARG_TAG, in);
      Largs(in, L);
    }
  // production Largs -> epsilon : nothing to do
}

// Lsymb -> epsilon | Symb Lsymb
void ParserXML::Lsymb( istream& in )
{
  if (lookahead == OPEN_FUNCSYM_TAG)
    {
      Symb(in);
      Lsymb(in);
    }
  // production Lsymb -> epsilon : nothing to do
}

// Symb -> funcsym name id endName arity int endArity endFuncsym
void ParserXML::Symb( istream& in )
{
  match(OPEN_FUNCSYM_TAG, in);

  match(OPEN_NAME_TAG, in);
  match(ID, in);
  match(CLOSE_NAME_TAG, in);
  
  match(OPEN_ARITY_TAG, in);
  match(ID, in);
  match(CLOSE_ARITY_TAG, in);
  
  match(CLOSE_FUNCSYM_TAG, in);
}

// M -> epsilon | metainfo anything endMetainfo
void ParserXML::M( istream& in )
{
  if (lookahead == OPEN_METAINFO_TAG) {
    match(OPEN_METAINFO_TAG, in);
    while (lookahead != CLOSE_METAINFO_TAG)
      match(lookahead, in);
    match(CLOSE_METAINFO_TAG, in);
  }
}

// Start parsing:
Program* ParserXML::parse( char* name, Symbtab& s )
{
  file_name = name;
  lexan->reset(name);
  symbtab = &s;

  // open the file:
  ifstream in;
  in.open(name);
  if (!in)
    {
      cerr << "Unable to open file " << name << endl;
      exit(EXIT_FAILURE);
    }

  Program *P = new TRS;

  // parse the file:
  lookahead = lexan->nexttoken(in, s);
  S(in, *P);

  // close the file:
  in.close();

  return P;
}
