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


/*********************
 *  class Position:  *
 *********************/


/* --------------- Output: --------------- */

ostream& operator << ( ostream& out, const Position& p )
{
  if (p.path.size() == 0) out << "epsilon";
  else
    {
      unsigned int i = 1;
      list<int>::const_iterator it;
      for (it = p.path.begin(); it != p.path.end(); it++, i++)
	{
	  out << *it;
	  if (i < p.path.size()) out << '.';
	}
    }
  return out;
}


/*****************
 *  class Tree:  *
 *****************/

/* --------------- Constructors/Destructor: --------------- */

Tree::Tree( int r, int n, Symbtab *s )
{
  // Construct myself:
  symbtab = s;
  root    = r;
  nb_args = n;
  if (n > 0)
    {
      args = new Tree*[n];
      for (int i = 0; i < n; i++) args[i] = NULL;
    }
  else args = NULL;
}

Tree::~Tree( )
{
  root    = NONE;
  if (args)
    {
      for (int i = 0; i < nb_args; i++) delete args[i];
      delete [] args;
    }
  args = NULL;
  nb_args = 0;
}


/* --------------- Operators: --------------- */

Tree& Tree::operator = ( const Tree& t )
{
  if (this != &t)
    {
      symbtab = t.symbtab;
      root    = t.root;
      nb_args = t.nb_args;
      if (args) delete [] args;
      if (nb_args == 0) args = NULL;
      else
	{
	  args = new Tree*[nb_args];
	  for (int i = 0; i < nb_args; i++)
	    {
	      args[i] = new Tree();
	      *(args[i]) = *(t.args[i]);
	    }
	}
    }
  return *this;
}

Tree*& Tree::operator [] ( int i )
{
  if (i < 0 || nb_args <= i || args == NULL)
    {
      string msg;
      if (i < 0) msg = "index is a negative integer";
      else if (nb_args <= i) msg = "index is greater than tree arity";
      else if (args == NULL) msg = "args tab is NULL";

      ERROR("Tree*& Tree::operator [] (int i)", msg);
    }
  return args[i];
}

Tree* Tree::operator [] ( int i ) const
{
  string msg = "Tree* Tree::operator [] (int i) const";
  if (i < 0) ERROR(msg, "index is a negative integer");
  if (nb_args <= i) ERROR(msg, "index is greater than tree arity");
  if (args == NULL) ERROR(msg, "args tab is NULL");

  return args[i];
}

bool Tree::operator == ( const Tree& t ) const
{
  if (root != t.root || nb_args != t.nb_args) return false;

  if (args == NULL) return (t.args == NULL);
  if (t.args == NULL) return false;

  for (int i = 0; i < nb_args; i++)
    {
      if (args[i] == NULL && t.args[i] == NULL) continue;
      if (args[i] == NULL || t.args[i] == NULL) return false;
      if (*(args[i]) != *(t.args[i])) return false;
    }
  return true;
}


/* --------------- Get/Set: --------------- */

Tree* Tree::get( Position where )
{
  Tree *t = this;

  where.init();
  while (where.exists())
    {
      t = (*t)[where.next()];
      if (t == NULL)
	ERROR("void Tree::set(Position& p,Tree *t)","no subterm at position p");
    }

  return t;
}

Tree* Tree::set( Position& p, Tree *new_subterm )
{
  if (new_subterm == NULL)
    ERROR("void Tree::set(const list<int>& pos,Tree *t)","t is NULL");

  if (p.length() == 0) *this = *new_subterm;
  else
    {
      Tree *t = this;
      p.init();
      int n = p.next();
      for (int i = 1; i < p.length(); i++)
	{
	  t = (*t)[n];
	  if (t == NULL)
	    ERROR("void Tree::set(Position& p,Tree *t)","no subterm at position p");
	  n = p.next();
	}

      if ((*t)[n]) delete (*t)[n];
      (*t)[n] = new_subterm->copy();
    }
  return this;
}

int Tree::maxv( ) const
{
  int n = 0;
  if (is_var()) n = -1*root;
  else
    {
      int m;
      for (int i = 0; i < nb_args; i++)
	{
	  m = args[i]->maxv();
	  if (n < m) n = m;
	}
    }
  return n;
}

bool Tree::is_not_ground( ) const
{
  if (is_var()) return true;
  if (args == NULL || nb_args == 0) return false;
  for (int i = 0; i < nb_args; i++)
    if (args[i]->is_not_ground()) return true;
  return false;
}

Mode* Tree::ground_pos( ) const
{
  Mode *m = new Mode;
  for (int i = nb_args-1; i >= 0; i--)
    if (!args[i]->is_not_ground()) m->insert_sorted(i);
  return m;
}

bool Tree::is_ground_mode( ) const
{
  if (0 < nb_args || root < 0) return false;

  char *s = symbtab->get_lexeme(root);
  return (s != NULL &&
	  (strcmp(s, "i") == 0 ||
	   strcmp(s, "g") == 0 ||
	   strcmp(s, "b") == 0));
}



/* --------------- Iteration over the subterms: --------------- */

void Tree::init( )
{ current = -1; }

Tree* Tree::next( Position& p )
{
  Tree *t;
  if (current == -1)
    {
      t = this;
      p.clear();
      while (++current < nb_args)
	if (args[current]) { args[current]->init(); break; }
    }
  else
    {
      t = args[current]->next(p);
      p.push_front(current);
      if (!args[current]->exists())
	while (++current < nb_args)
	  if (args[current]) { args[current]->init(); break; }
    }
  return t;
}

bool Tree::exists( )
{ return (-1 <= current && current < nb_args); }


/* --------------- Misc: --------------- */

void Tree::parse( int vars[MAX_VAR], int &k )
{
  if (is_var())
    {
      int index = -1*root-1;
      if (vars[index] == 0) vars[index] = --k;
      root = vars[index];
    }
  else
    for (int i = 0; i < nb_args; i++)
      if (args[i]) args[i]->parse(vars, k);
}

Tree* Tree::rename( int n )
{
  if (n < 0)
    ERROR("void Tree::rename(int n)","n is negative");

  if (is_var()) root -= n;
  else if (args)
    for (int i = 0; i < nb_args; i++)
      if (args[i]) args[i]->rename(n);

  return this;
}

Tree* Tree::copy( ) const
{
  Tree *t = new Tree;

  t->symbtab = symbtab;
  t->root    = root;
  t->nb_args = nb_args;
  if (args)
    {
      t->args = new Tree*[nb_args];
      for (int i = 0; i < nb_args; i++)
	if (args[i] == NULL) (t->args)[i] = NULL;
	else (t->args)[i] = (args[i])->copy();
    }

  return t;
}

bool Tree::occurs( int symbol ) const
{
  if (symbol == root) return true;
  else
    for (int i = 0; i < nb_args; i++)
      if (args[i])
	if (args[i]->occurs(symbol)) return true;
  return false;
}

bool Tree::strict_subtree( Tree *t ) const
{
  for (int i = 0; i < nb_args; i++)
    if ( args[i] != NULL &&
	 (*(args[i]) == *t || args[i]->strict_subtree(t)) )
      return true;
  return false;
}

bool Tree::not_deeper_than( int k ) const
{
  if (k < 0)
    ERROR("bool Tree::not_deeper_than( int k ) const", "k < 0");

  if (nb_args == 0) return true;

  if (k == 0) return false;
  else
    for (int i = 0; i < nb_args; i++)
      if (args[i] != NULL && !args[i]->not_deeper_than(k-1)) return false;
  return true;
}



/* --------------- Input/Output: --------------- */

void Tree::display_args( ostream& out ) const
{
  for(int i = 0; i < nb_args; i++)
    {
      if (args[i] == NULL) out << "NULL";
      else args[i]->display(out);
      if (i < nb_args-1) out << ',';
    }
}

void Tree::display( ostream& out ) const
{
  if (is_var()) out << '_' << -1*root;
  else
    {
      out << symbtab->get_lexeme(root);
      if (nb_args > 0)
	{
	  out << '(';
	  display_args(out);
	  out << ')';
	}
    }
}

ostream& operator << ( ostream& out, const Tree& t )
{
  t.display(out);
  return out;
}
