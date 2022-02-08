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

int LexanTRS::fail()
{
  switch (start)
    {
    case 0:  start = 3;  break;
    case 3:  start = 5;  break;
    case 5:  start = 8; break;
    case 8: error("lexical error"); break;
    default: error("compiler error");
    }
  return start;
}


int LexanTRS::nexttoken( istream& in, Symbtab& symbtab )
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
	  {
	    b = 0;
	    in_buffer(c, b);
	    state = 6;
	  }
	else state = fail();
	break;
      case 6:
	c = in.get();
	if (c != ',' && c != '(' && c != ')' && !is_space(c)
	    && c != '\t' && c != '\n' && c != '"' && c != EOF)
	  in_buffer(c, b);
	else state = 7;
	break;
      case 7:
	// it's an id or a keyword:
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
 *            ParserTRS            *
 ***********************************/

/* ------------------- Parsing: --------------------- */

// Spec -> done  |  '(' Decl ')' Spec
void ParserTRS::Spec( istream& in, Program& P )
{
  if (lookahead == '(')
    {
      match('(', in);
      Decl(in, P);
      match(')', in);
      Spec(in, P);
    }
  else if (lookahead != DONE)
    error("syntax error");
}

// Decl  -> var Lid  |  rules Lr  |  id L
void ParserTRS::Decl( istream& in, Program& P )
{
  if (lookahead == VAR)
    {
      match(VAR, in);
      lvar = true;
      Lid(in);
      lvar = false;
    }
  else if (lookahead == RULES)
    {
      match(RULES, in);
      if (lookahead == ID) Lr(in, P);
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
void ParserTRS::L( istream& in )
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

// Lid -> id Lid | epsilon
void ParserTRS::Lid( istream& in )
{
  if (lookahead == ID)
    {
      int p = lexan->tokenattr();
      match(lookahead, in);
      if (lvar && var) symbtab->set_info(p, VAR);
      Lid(in);
    }
  else
    return; // production Lid -> epsilon : nothing to do
}

// Lr -> R Lr  |  epsilon
void ParserTRS::Lr( istream& in, Program& P )
{
  if (lookahead == ID)
    {
      if (var) R(in);
      else P.push_back(R(in));
      Lr(in, P);
    }
  else return;
}

// R -> T '->' T
Rule* ParserTRS::R( istream& in )
{
  Rule *r = NULL;

  Tree *l = T(in);
  match(ARROW, in);
  if (var) T(in); else r = new Rule(l, T(in));

  return r;
}

// T -> id  |  id '(' ')'  |  id '(' Lt ')'
Tree* ParserTRS::T( istream& in )
{
  Tree *t = NULL;
  int k = 0;
  int root = lexan->tokenattr();
  list<Tree*> args_list;
  list<Tree*>::iterator it;

  if (lookahead == ID)
    {
      match(lookahead, in);
      if (lookahead == '(')
	{
	  match('(',  in);
	  if (lookahead == ID) Lt(in, args_list);
	  match(')', in);
	}
      if (!var)
	{
	  if (symbtab->get_info(root) == VAR) root = -1*root-1;
	  t = new Tree(root, args_list.size(), symbtab);
	  for (it = args_list.begin(); it != args_list.end(); it++)
	    (*t)[k++] = *it;
	}
    }
  else
    error("syntax error: missing id");

  return t;
}

// Lt -> T | T ',' Lt
void ParserTRS::Lt( istream& in, list<Tree*>& L )
{
  if (var) T(in); else L.push_back(T(in));
  if (lookahead == ',')
    {
      match(',', in);
      Lt(in, L);
    }
  else return;
}


// Start parsing:
Program* ParserTRS::parse( char* name, Symbtab& s )
{
  file_name = name;
  lexan->reset(name);
  symbtab = &s;
  lvar = false;

  // open the file:
  ifstream in;
  in.open(name);
  if (!in)
    {
      cerr << "Unable to open file " << name << endl;
      exit(EXIT_FAILURE);
    }

  Program *P = new TRS;

  // parse variables only:
  lookahead = lexan->nexttoken(in, s);
  var = true;
  Spec(in, *P);

  // restart from the beginning of the file:
  in.clear(ios::goodbit);
  in.seekg(0);

  // completely parse the file:
  lookahead = lexan->nexttoken(in, s);
  var = false;
  Spec(in, *P);

  // close the file:
  in.close();

  return P;
}
