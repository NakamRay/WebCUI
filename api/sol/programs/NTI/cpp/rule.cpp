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



/*****************
 *  class Rule:  *
 *****************/

/* --------------- Constructor/Destructor: --------------- */

Rule::Rule( Tree *head, Tree *body, bool norm, int maxv )
{
  h = head;
  if (body)
    {
      b = new (Tree*);
      *b = body;
      b_size = 1;
    }
  else
    { b = NULL; b_size = 0; }

  if (!norm) { max_var = maxv; return; }

  int vars[MAX_VAR];
  for (int i = 0; i < MAX_VAR; i++) vars[i] = 0;
  int k = 0;
  if (h) h->parse(vars, k);
  if (body) body->parse(vars, k);
  max_var = -1*k;
}

Rule::Rule( Tree *head, const list<Tree*>& body, bool norm, int maxv )
{
  h = head;
  b_size = body.size();
  if (b_size != 0)
    {
      b = new Tree*[b_size];
      int k = 0;
      list<Tree*>::const_iterator it;
      for (it = body.begin(); it != body.end(); it++)
	b[k++] = *it;
    }
  else b = NULL;

  if (!norm) { max_var = maxv; return; }

  int vars[MAX_VAR];
  for (int i = 0; i < MAX_VAR; i++) vars[i] = 0;
  int k = 0;
  if (h) h->parse(vars, k);
  for (int i = 0; i < b_size; i++)
    if(b[i]) b[i]->parse(vars, k);
  max_var = -1*k;
}

Rule::~Rule( )
{
  if (h) { delete h; h = NULL; }
  if (b)
    {
      for (int i = 0; i < b_size; i++)
	if (b[i]) { delete b[i]; b[i] = NULL; }
      delete [] b;
      b = NULL;
    }
}


/* --------------- Get/Set: --------------- */

Tree* Rule::body( int i ) const
{
  string func = "Tree* Rule::body(int) const";
  if (i < 0)
    ERROR(func,"index is a negative integer");
  if (b_size <= i)
    ERROR(func,"index is greater than body size");
  if (b == NULL)
    ERROR(func,"body is NULL");

  return b[i];
}

void Rule::set_body( int i, Tree* t )
{
  string func = "Tree* Rule::body(int) const";
  if (i < 0)
    ERROR(func,"index is a negative integer");
  if (b_size <= i)
    ERROR(func,"index is greater than body size");
  if (b == NULL)
    ERROR(func,"body is NULL");

  b[i] = t;
}


/* --------------- Operators: --------------- */

bool Rule::operator == ( const Rule& r ) const
{
  if (b_size != r.b_size || max_var != r.max_var) return false;

  if (h == NULL && r.h != NULL) return false;
  if (h != NULL && r.h == NULL) return false;
  if (h != NULL && *h != *(r.h)) return false;

  for (int i = 0; i < b_size; i++)
    if (b[i] == NULL && (r.b)[i] == NULL) continue;
    else if (b[i] == NULL || (r.b)[i] == NULL) return false;
    else if (*(b[i]) != *(r.b[i])) return false;

  return true;
}


/* --------------- Misc: --------------- */

Rule* Rule::rename( int& n )
{
  if (n < 0)
    ERROR("void Rule::rename(int& n)","n is negative");

  if (h) h->rename(n);
  if (b)
    for (int i = 0; i < b_size; i++)
      if (b[i]) b[i]->rename(n);

  max_var += n;
  n = max_var;

  return this;
}

Rule* Rule::copy( ) const
{
  if (!h)
    ERROR("Rule* Rule::copy() const", "Head of rule is NULL");

  Rule *r  = new Rule(h->copy(), NULL, false, max_var);
  r->b_size  = b_size;
  if (b)
    {
      r->b = new Tree*[b_size];
      for (int i = 0; i < b_size; i++)
	if (b[i]) (r->b)[i] = b[i]->copy();
    }
  else r->b = NULL;

  return r;
}

void Rule::clear_body( )
{
  if (b)
    for (int i = 0; i < b_size; i++) b[i] = NULL;
}


/* --------------- Input/Output: --------------- */

void Rule::display( ostream& out ) const
{
  if (h) out << *h;
  else out << "NULL";
  if (b_size > 0) out << " -> ";
  for (int i = 0; i < b_size; i++)
    {
      if (b[i] == NULL) out << "NULL";
      else out << *(b[i]);
      if (i < b_size-1) out << ", ";
    }
}

ostream& operator <<  ( ostream& out, const Rule& r )
{
  r.display(out);
  return out;
}
