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


/* --------------- More general: --------------- */

bool more_general( Tree *t1, Tree *t2, Substitution *&theta )
{
  if (t1->is_var())
    { theta = new Substitution; theta->set(t1,t2); return true; }

  if (t1->rel() != t2->rel() || t1->arity() != t2->arity())
    {
      if (theta) delete theta;
      theta = NULL;
      return false;
    }

  theta = new Substitution;
  Substitution *gamma = NULL;
  for (int i = 0; i < t1->arity(); i++)
    if (more_general((*t1)[i], (*t2)[i], gamma))
      if ((*theta)+gamma) { delete gamma; gamma = NULL; }
      else
	{
	  delete theta; theta = NULL;
	  delete gamma;
	  return false;
	}
    else
      {
	delete theta; theta = NULL;
	return false;
      }

  return true;
}

bool more_general( Tree *t1, Tree *t2 )
{
  Substitution *theta = NULL;
  bool ans = more_general(t1, t2, theta);
  if (theta) delete theta;
  return ans;
}


/* --------------- Variant: --------------- */

bool variant( Tree *t1, Tree *t2 )
{ return more_general(t1,t2) && more_general(t2,t1); }


/* --------------- tau-More general: --------------- */

bool tau_more_general( Tree *t1, Tree *t2, Sop *tau, Substitution *&theta )
{
  if (t1->is_var())
    { theta = new Substitution; theta->set(t1,t2); return true; }

  if (t1->rel() != t2->rel() || t1->arity() != t2->arity())
    {
      if (theta) delete theta;
      theta = NULL;
      return false;
    }

  theta = new Substitution;
  Substitution *gamma = NULL;
  for (int i = 0; i < t1->arity(); i++)
    {
      if ((*tau)[t1]->in_domain(i))
	{
	  if (more_general( (*(*tau)[t1])[i], (*t1)[i] ))
	    continue;
	  else
	    {
	      delete theta; theta = NULL;
	      return false;
	    }
	}
      if (more_general((*t1)[i], (*t2)[i], gamma))
	{
	  if ((*theta)+gamma) { delete gamma; gamma = NULL; continue; }
	  else
	    {
	      delete theta; theta = NULL;
	      delete gamma;
	      return false;
	    }
	}
      delete theta; theta = NULL;
      return false;}


  return true;
}

bool tau_more_general( Tree *t1, Tree *t2, Sop *tau )
{
  Substitution *theta = NULL;
  bool ans = tau_more_general(t1, t2, tau, theta);
  if (theta) delete theta;
  return ans;
}


/* --------------- Unification: --------------- */

bool unify( Tree *t1, Tree *t2, Substitution *&theta )
{
  if (t1->rel() != t2->rel())
    {
      if (t1->is_var() && !t2->occurs(t1->rel()))
	{ theta = new Substitution; theta->set(t1,t2); return true; }
      if (t2->is_var() && !t1->occurs(t2->rel()))
	{ theta = new Substitution; theta->set(t2,t1); return true; }
      theta = NULL; return false;
    }

  if (t1->arity() != t2->arity()) { theta = NULL; return false; }

  theta = new Substitution;
  if (t1->arity() != 0)
    {
      Substitution *gamma = NULL;
      Tree *t1_copy = t1->copy();
      Tree *t2_copy = t2->copy();
      for (int i = 0; i < t1->arity(); i++)
	if ( unify((*t1_copy)[i], (*t2_copy)[i], gamma) )
	  {
	    (*gamma)(t1_copy); (*gamma)(t2_copy);
	    (*theta)*gamma;
	    delete gamma; gamma = NULL;
	  }
	else
	  {
	    delete theta; theta = NULL;
	    delete t1_copy; delete t2_copy;
	    return false;
	  }
      delete t1_copy; delete t2_copy;
    }
  return true;
}

bool unify( Tree *t1, Tree *t2 )
{
  Substitution *theta = NULL;
  bool ans = unify(t1, t2, theta);
  if (theta) delete theta;
  return ans;
}
