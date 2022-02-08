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


/**************************
 *    Class PosToTerm:    *
 **************************/

/* --------------- Constructor/Destructor: --------------- */

PosToTerm::PosToTerm( int n )
{
  domsize = 0;
  max_domsize = n;
  if (n == 0) range = NULL;
  else
    {
      range = new Tree*[n];
      for (int i = 0; i < n; i++) range[i] = NULL;
    }
}

PosToTerm::~PosToTerm( )
{
  if (range)
    {
      for (int i = 0; i < max_domsize; i++)
	if (range[i]) delete range[i];
      delete range;
    }
}

/* --------------- Get/Set: --------------- */

void PosToTerm::set( int i, Tree *t )
{
  if (i < 0 || i >= max_domsize)
    ERROR("void PosToTerm::set(int i,Tree *t)","i out of range");

  if (range[i] == NULL && t != NULL) domsize++;
  if (range[i] != NULL && t == NULL) domsize--;
  if (range[i]) delete range[i];
  range[i] = t;
}


/* --------------- Operators: --------------- */

Tree* PosToTerm::operator [] ( int i ) const
{
  if (i < 0 || i >= max_domsize)
    ERROR("Tree* PosToTerm::operator [] (int i) const","i out of range");
  return range[i];
}

bool PosToTerm::operator == ( const PosToTerm& p ) const
{
  for (int i = 0; i < max_domsize; i++)
    if (range[i] == p.range[i]) continue;
    else if (range[i] == NULL || p.range[i] == NULL) return false;
    else if (*(range[i]) != *(p.range[i])) return false;
  return true;
}


/* --------------- Operations over the domain: --------------- */

bool PosToTerm::restrict_dom_to( bool F[] )
{
  bool ans = false;
  for (int i = 0; i < max_domsize; i++)
    if (!F[i] && range[i])
      { ans = true; delete range[i]; range[i] = NULL; domsize--; }
  return ans;
}

bool PosToTerm::in_domain( int i ) const
{
  if (i < 0 || i >= max_domsize)
    ERROR("bool PosToTerm::in_domain(int i) const","i out of range");
  return range[i] != NULL;
}

bool PosToTerm::includes( Mode *m ) const
{
  if (m == NULL) return true;

  int i;
  m->init();
  while (m->exists())
    {
      i = m->next();
      if (i < 0 || i >= max_domsize)
	ERROR("bool PosToTerm::includes(Mode *m) const","an element of m is out of range");
      if (range[i] == NULL) return false;
    }
  return true;
}


/* --------------- Iteration over the domain: --------------- */

void PosToTerm::init( )
{
  for (current = 0; current < max_domsize; current++)
    if (range[current]) return;
}

int PosToTerm::next( )
{
  int n = current++;
  while (current < max_domsize)
    if (range[current]) break;
    else current++;
  return n;
}

bool PosToTerm::exists( )
{ return current < max_domsize; }


/* --------------- Misc: --------------- */

PosToTerm* PosToTerm::copy( ) const
{
  PosToTerm *pos = new PosToTerm(max_domsize);
  pos->domsize = domsize;
  for (int i = 0; i < max_domsize; i++)
    if (range[i]) pos->range[i] = range[i]->copy();
  return pos;
}


/* --------------- Output: --------------- */

ostream& operator << ( ostream& out, const PosToTerm& p )
{
  bool b = false;
  out << '[';
  for (int i = 0; i < p.max_domsize; i++)
    if (p.range[i])
      {
	if (i > 0 && b) out << ", ";
	out << i+1 << " -> ";
	p.range[i]->display(out);
	b = true;
      }
  out << ']';
  return out;
}



/********************
 *    Class Sop:    *
 ********************/

/* --------------- Destructor: --------------- */

Sop::~Sop( )
{
  list<sop_entry>::iterator it;
  for (it = range.begin(); it != range.end(); it++)
    if (it->tau_p) delete it->tau_p;
}


/* --------------- Operators: --------------- */

PosToTerm* Sop::operator []  ( Tree* A )
{
  int p = A->rel(), n_p = A->arity();

  list<sop_entry>::iterator it;
  for (it = range.begin(); it != range.end(); it++)
    if ((*it).p == p && (*it).n_p == n_p) return (*it).tau_p;

  PosToTerm *tau_p = new PosToTerm(n_p);
  for (int i = 0; i < n_p; i++)
    tau_p->set(i, new Tree(-1));
  range.push_back(sop_entry(p, n_p, tau_p));
  return tau_p;
}


/* --------------- Get/Set: --------------- */

bool Sop::includes( int p, int n_p, Mode *m ) const
{
  if (m == NULL) return true;

  list<sop_entry>::const_iterator it;
  for (it = range.begin(); it != range.end(); it++)
    if ((*it).p == p && (*it).n_p == n_p) return ((*it).tau_p)->includes(m);
  return true;
}


/* --------------- Auxiliary functions: --------------- */

int nb_common_vars( Tree *t1, Tree *t2 )
{
  if (t1->is_var())
    {
      if (t2->occurs(t1->rel())) return 1;
      else return 0;
    }
  int n = 0;
  for (int i = 0; i < t1->arity(); i++)
    n += nb_common_vars((*t1)[i],t2);
  return n;
}

bool* isolated_args( Tree *t )
{
  int n = t->arity();

  if (n == 0) return NULL;

  bool ok;
  bool *F = new bool[n];

  for (int i = 0; i < n; i++)
    {
      ok = true;
      for (int j = 0; j < n && ok; j++)
	if ( j != i && nb_common_vars((*t)[j],(*t)[i]) ) ok = false;
      if (ok) F[i] = true;
      else F[i] = false;
    }

  return F;
}


/* --------------- Computing DN sets of positions with associated terms: --------------- */

void satisfy_DN1( Sop& tau, Program* BP )
{
  Tree *h;
  bool *F;

  BP->init();
  while (BP->exists())
    {
      h = BP->next()->head();
      F = isolated_args(h);
      tau[h]->restrict_dom_to(F);
      delete F;
    }
}

void satisfy_DN2( Sop& tau, Program* BP )
{
  Tree *h;
  PosToTerm *tau_h;
  bool *F;
  int i;

  BP->init();
  while (BP->exists())
    {
      h = BP->next()->head();
      tau_h = tau[h];
      F = new bool[h->arity()];
      for (int k = 0; k < h->arity(); k++) F[k] = false;

      tau_h->init();
      while (tau_h->exists())
	{
	  i = tau_h->next();
	  if (more_general( (*h)[i], (*tau_h)[i] ))
	    F[i] = true;
	  else if (more_general( (*tau_h)[i], (*h)[i] ))
	    { F[i] = true; tau_h->set(i,(*h)[i]->copy()); }
	  else F[i] = false;
	}
      tau_h->restrict_dom_to(F);
      delete F;
    }
}

void satisfy_DN3( Sop& tau, Program* BP )
{
  Tree *b;
  Rule *r;
  PosToTerm *tau_b;
  bool *F;
  int i;

  BP->init();
  while (BP->exists())
    {
      r = BP->next();
      if (!r->is_fact())
      {
	b = r->body(0);
	tau_b = tau[b];
	F = new bool[b->arity()];
	for (int k = 0; k < b->arity(); k++) F[k] = false;

	tau_b->init();
	while (tau_b->exists())
	  {
	    i = tau_b->next();
	    if (more_general( (*tau_b)[i], (*b)[i] ))
	      F[i] = true;
	  }
	tau_b->restrict_dom_to(F);
	delete F;
      }
    }
}

bool satisfy_DN4( Sop& tau, Program* BP )
{
  Tree *h, *b;
  Rule *r;
  PosToTerm *tau_h, *tau_b;
  bool *F;
  bool ok, ans;
  int i;

  ans = true;
  BP->init();
  while (BP->exists())
    {
      r = BP->next();
      if (!r->is_fact())
	{
	  h = r->head();
	  b = r->body(0);
	  tau_h = tau[h];
	  tau_b = tau[b];
	  F = new bool[h->arity()];
	  for (int k = 0; k < h->arity(); k++) F[k] = false;
	  ok = true;

	  tau_h->init();
	  while (tau_h->exists())
	    {
	      i = tau_h->next();
	      ok = true;
	      for (int j = 0; j < b->arity() && ok; j++)
		if (!tau_b->in_domain(j))
		  if (nb_common_vars((*h)[i],(*b)[j])) ok = false;
	      if (ok) F[i] = true;
	    }
	  ans = ans && !tau_h->restrict_dom_to(F);
	  delete F;
	}
    }
  return ans;
}

void Sop::set_DN( Program* BP, Tree* A, Sop* tau )
{
  int p = A->rel(), n_p = A->arity();

  range.clear();
  if (tau != NULL)
    {
      list<sop_entry>::iterator it;
      for (it = (tau->range).begin(); it != (tau->range).end(); it++)
	if (it->p != p || it->n_p != n_p)
	  range.push_back(sop_entry(it->p, it->n_p, it->tau_p->copy()));
    }

  PosToTerm *tau_p = new PosToTerm(n_p);
  for (int i = 0; i < n_p; i++) tau_p->set(i, new Tree(-1));
  range.push_back(sop_entry(p, n_p, tau_p));

  satisfy_DN1(*this, BP);
  satisfy_DN2(*this, BP);
  satisfy_DN3(*this, BP);
  while (!satisfy_DN4(*this, BP));
}

void Sop::set_DN( Rule* r, Tree *A, Sop* tau )
{
  ProgramLP BP;
  BP.push_back(r);
  set_DN(&BP, A, tau);
  BP.clear();
}


/* --------------- Output: --------------- */

ostream& operator << ( ostream& out, const Sop& tau )
{
  bool b = false;
  out << '<';
  list<sop_entry>::const_iterator it;
  for (it = tau.range.begin(); it != tau.range.end(); it++)
    {
      if (it != tau.range.begin() && b) out << ", ";
      out << (*it).p << " -> " << *((*it).tau_p);
      b = true;
    }
  out << '>';

  return out;
}
