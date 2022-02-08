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
#include <sstream>


/********************
 *  class LexanLP:  *
 ********************/

/* -------------- Lexical analysis: --------------- */

int LexanLP::fail( )
{
  switch (start)
    {
    case 0:  start = 1;  break;
    case 1:  start = 3;  break;
    case 3:  start = 7;  break;
    case 7:  start = 10;  break;
    case 10:  start = 13; break;
    case 13: start = 15; break;
    case 15: error("lexical error"); break;
    default: error("compiler error");
    }
  return start;
}

int LexanLP::nexttoken( istream& in, Symbtab& symbtab )
{
  int  b, c;
  bool mode;
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
	/* One line comments: */
      case 1:
	if (c == '%') state = 2;
	else state = fail();
	break;
      case 2:
	mode = true;
	for (int i = 0; i < 6 && mode; i++)
	  {
	    c = in.get();
	    if (c == EOF) return DONE;
	    else
	      {
		if (i == 0 && c != 'q') mode = false;
		else if (i == 1 && c != 'u') mode = false;
		else if (i == 2 && c != 'e') mode = false;
		else if (i == 3 && c != 'r') mode = false;
		else if (i == 4 && c != 'y') mode = false;
		else if (i == 5 && c != ':') mode = false;
	      }
	  }
	if (mode) return MODE;
	else
	  {
	    while (c != '\n') c = in.get();
	    start = 0;
	    state = 0; 
	    lineno++;	    
	  }
	break;
	/* Multi-line comments: */
      case 3:
	if (c == '/') state = 4;
	else state = fail();
	break;
      case 4:
	c = in.get();
	if (c == '*') state = 5;
	else { in.putback(c); return '/'; }
	break;
      case 5:
	c = in.get();
	if (c == '*') state = 6;
	else if (c == '\n') lineno++;
	else if (c == EOF) error("non-ended comment");
	break;
      case 6:
	c = in.get();
	if (c == '/') { start = 0; state = 0; }
	else state = 5;
	break;
	/* Identifiers + variables: */
      case 7:
	if (isalpha(c) || c == '_') { b = 0; in_buffer(c, b); state = 8; }
	else state = fail();
	break;
      case 8:
	c = in.get();
	if (isalnum(c) || c == '_') in_buffer(c, b);
	else state = 9;
	break;
      case 9:
	in.putback(c);
	in_buffer(EOS, b);
	if (lexbuf[0] == '_' && lexbuf[1] == EOS)
	  {
	    token_attr = new_var_index();
	    return VAR;
	  }
	if (lexbuf[0] == '_' || isupper(lexbuf[0]))
	  {
	    token_attr = -1*symbtab.insert(lexbuf, VAR) - 1;
	    return VAR;
	  }
	token_attr = symbtab.insert(lexbuf, ID);
	return symbtab.get_token(token_attr);
	/* Positive integers: */
      case 10:
	if (isdigit(c))  { b = 0; in_buffer(c, b); state = 11; }
	else state = fail();
	break;
      case 11:
	c = in.get();
	if (isdigit(c)) in_buffer(c, b);
	else state = 12;
	break;
      case 12:
	in.putback(c);
	in_buffer(EOS, b);
	token_attr = symbtab.insert(lexbuf, INT);
	return INT;
	/* Leftarrow: */
      case 13:
	if (c == ':') state = 14;
	else state = fail();
	break;
      case 14:
	c = in.get();
	if (c == '-') return ARROW;
	else { in.putback(c); state = 15; }
	break;
	/* Other character: */
      case 15:
	if (c == '(' || c == ')' || c == '[' || c == ']' ||
	    c == ',' || c == '.' || c == '/' || c == '|')
	  return c;
	else if (c == '=')
	  {
	    token_attr = symbtab.insert("=", EQ);
	    return EQ;
	  }
	else state = fail();
	break;
	/* Default behavior: */
      default: error("compiler error");
      }
}


/* ------------------- Get/Set: ---------------------- */

void LexanLP::reset( char *name )
{
  Lexan::reset(name);
  var_index = -1 * SYMBTAB_SIZE;
}



/*********************
 *  class ParserLP:  *
 *********************/

/* ------------------- Parsing: --------------------- */

// Lr -> R Lr | U Lr | M Lr | done
void ParserLP::Lr( istream& in, ProgramLP& P )
{
  if (lookahead == ID) { P.push_back(R(in)); Lr(in, P); }
  else if (lookahead == ARROW) { U(in); Lr(in, P); }
  else if (lookahead == MODE) { P.set_query(M(in)); Lr(in, P); }
  else if (lookahead != DONE) error("syntax error");
}

// R -> F '.' | F '->' La '.'
Rule* ParserLP::R( istream& in )
{
  Tree *head = F(in);
  list<Tree*> body;
  if (lookahead == ARROW)
    {
      match(ARROW, in);
      La(in, body);
    }
  match('.', in);
  return new RuleLP(head, body);
}

// U -> ':-' A '.'
void ParserLP::U( istream& in )
{
  match(ARROW, in);
  Tree *t = A(in);
  delete t;
  match('.', in);
}

// M -> mode F '.'
Tree* ParserLP::M( istream& in )
{
  match(MODE, in);
  Tree *t = F(in);
  match('.', in);

  return t;
}

// La -> A | A ',' La
void ParserLP::La( istream& in, list<Tree*>& l )
{
  l.push_back(A(in));
  if (lookahead == ',')
    {
      match(',', in);
      La(in, l);
    }
  else return;
}

// A -> F | T = T
Tree* ParserLP::A( istream& in )
{
  Tree *t = NULL;

  if (lookahead == ID)
    {
      Tree *t0 = F(in);
      if (lookahead == EQ) 
	{
	  int root = lexan->tokenattr();
	  match(EQ, in);
	  Tree *t1 = T(in);
	  t = new Tree(root, 2, symbtab);
	  (*t)[0] = t0;
	  (*t)[1] = t1;
	}
      else
	t = t0;
    }
  else 
    {
      Tree *t0 = T(in);
      int root = lexan->tokenattr();
      match(EQ, in);
      Tree *t1 = T(in);
      t = new Tree(root, 2, symbtab);
      (*t)[0] = t0;
      (*t)[1] = t1;      
    }

  return t;
}

// F -> id | id '(' Lt ')'
Tree* ParserLP::F( istream& in )
{
  Tree *t;
  int root, k = 0;
  list<Tree*> args_list;
  list<Tree*>::iterator it;

  root = lexan->tokenattr();
  match(ID, in);
  if (lookahead == '(')
    {
      match('(',  in);
      Lt(in, args_list);
      match(')', in);
    }

  t = new Tree(root, args_list.size(), symbtab);
  for (it = args_list.begin(); it != args_list.end(); it++)
    (*t)[k++] = *it;

  return t;
}

// Lt -> T ',' Lt | T
void ParserLP::Lt( istream& in, list<Tree*>& l )
{
  l.push_back(T(in));
  if (lookahead == ',')
    {
      match(',', in);
      Lt(in, l);
    }
  else return;
}

// T -> F | var | int | Li
Tree* ParserLP::T( istream& in )
{
  Tree *t = NULL;
  int root;

  if (lookahead == ID) t = F(in);
  else if (lookahead == VAR || lookahead == INT)
    {
      root = lexan->tokenattr();
      match(lookahead, in);
      t = new Tree(root, 0, symbtab);
    }
  else if (lookahead == '[')
    t = Li(in);
  else error("syntax error");

 return t;
}

// Li -> '[' ']'  |  '[' Lt ']'  |  '[' Lt '|' var ']'
Tree* ParserLP::Li( istream& in )
{
  List *t = NULL;

  match('[', in);
  if (lookahead == ']')
    {
      t = new List();
      match(']', in);
    }
  else
    {
      list<Tree*> elements;

      Lt(in, elements);
      if (lookahead == ']')
	{
	  match(']', in);
	  t = new List();
	  list<Tree*>::reverse_iterator it;
	  for (it = elements.rbegin(); it != elements.rend(); it++)
	    t->push_front(*it);
	}
      else if (lookahead == '|')
	{
	  match('|', in);
	  int root = lexan->tokenattr();
	  match(VAR, in);
	  match(']', in);

	  t = new List(root);
	  list<Tree*>::reverse_iterator it;
	  for (it = elements.rbegin(); it != elements.rend(); it++)
	    t->push_front(*it);
	}
      else error("syntax error");
    }
  return t;
}

Program* ParserLP::parse( char* name, Symbtab& s )
{
  file_name = name;
  symbtab   = &s;
  lexan->reset(name);

  // open file:
  ifstream in;
  in.open(file_name);
  if (!in)
    {
      cerr << "Unable to open file " << name << endl;
      exit(EXIT_FAILURE);
    }

  ProgramLP *P = new ProgramLP;

  // parse:
  lookahead = lexan->nexttoken(in, s);
  Lr(in, *P);

  // close file:
  in.close();

  return P;
}
