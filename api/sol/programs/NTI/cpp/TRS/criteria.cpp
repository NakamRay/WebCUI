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


/* --------------- match tests: --------------- */

Tree* match_test( Tree *l, Tree *r, Substitution*& theta )
{
  if (more_general(l, r, theta)) return l->copy();
  else return NULL;
}

Tree* deep_match_test( Tree *l, Tree *r, Substitution*& theta, Position& p )
{
  r->init();
  while (r->exists())
    if (more_general(l, r->next(p), theta)) return l->copy();
  return NULL;
}


/* --------------- unification tests: --------------- */

Tree* unify_test( Tree *l, Tree *r, Substitution*& theta )
{
  Tree *l_copy = NULL;

  theta = NULL;
  if (unify(l, r, theta))
    {
      l_copy = l->copy();
      (*theta)(l_copy);
    }

  return l_copy;
}

Tree* deep_unify_test( Tree *l, Tree *r, Substitution*& theta, Position& p )
{
  Tree *l_copy = NULL;

  theta = NULL;
  r->init();
  while (r->exists())
    if (unify(l, r->next(p), theta))
      {
	l_copy = l->copy();
	(*theta)(l_copy);
	return l_copy;
      }

  return NULL;
}


/* --------------- both match and unification tests: --------------- */

Tree* unify_or_match_test( Tree *l, Tree *r, Substitution*& theta )
{
  Tree *t = unify_test(l, r, theta);
  if (t == NULL) t = match_test(l, r, theta);
  return t;
}

Tree* deep_unify_or_match_test( Tree *l, Tree *r, Substitution*& theta, Position& p )
{
  p.clear();
  Tree *t = deep_unify_test(l, r, theta, p);
  if (t == NULL) { p.clear(); t = deep_match_test(l, r, theta, p); }
  return t;
}
