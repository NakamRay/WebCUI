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



/*************************
 *  class UnfoldedRule:  *
 *************************/

/* --------------- Constructors/Destructor: --------------- */

UnfoldedRule::UnfoldedRule( Tree *head, Tree *body,
			    int iteration, Position p, Substitution *theta,
			    Rule *parentX, Rule *parentR, bool forward_or_backward, bool elim,
			    bool normalize, int max_var ): Rule(head, body, normalize, max_var)
{
  this->iteration           = iteration;
  this->p                   = p;
  this->theta               = theta;
  this->parentX             = parentX;
  this->parentR             = parentR;
  this->forward_or_backward = forward_or_backward;
  this->elim                = elim;
}

UnfoldedRule::UnfoldedRule( Tree *head, Tree *body, bool elim ): Rule(head, body)
{
  this->iteration = 0;
  this->theta     = NULL;
  this->parentX   = NULL;
  this->parentR   = NULL;
  this->elim      = elim;
}

UnfoldedRule::~UnfoldedRule( )
{
  if (theta) delete theta;
  if (parentR) delete parentR;
}


/* --------------- Misc: --------------- */

Rule* UnfoldedRule::copy( ) const
{
  if (!h)
    ERROR("Rule* UnfoldedRule::copy() const", "Head of rule is NULL");

  Substitution *theta_copy = (theta == NULL)?NULL:theta->copy();
  Rule *parentR_copy = (parentR == NULL)?NULL:parentR->copy();
  UnfoldedRule *r  = new UnfoldedRule(h->copy(), NULL,
				      iteration, p, theta_copy,
				      parentX, parentR_copy, forward_or_backward, elim,
				      false, max_var);
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


/* --------------- Input/Output: --------------- */

void UnfoldedRule::display( ostream& out ) const
{
  if (parentX)
    {
      int i = iteration - 1;
      if (forward_or_backward)
	out << *parentX
	    << "let r" << i << " be the right-hand side of this rule" << endl
	    << "p" << i << " = " << p
	    << " is a position in r" << i << endl
	    << "we have r" << i << "|p" << i << " = " << *(parentX->body(0)->get(p)) << endl
	    << *parentR << " is in R" << endl
	    << "let l'" << i << " be the left-hand side of this rule" << endl
	    << "theta" << i << " = " << *theta
	    << " is a mgu of r" << i << "|p" << i << " and l'" << i << endl << endl
	    << "==> ";
      else
	out << *parentX
	    << "let l" << i << " be the left-hand side of this rule" << endl
	    << "p" << i << " = " << p
	    << " is a position in l" << i << endl
	    << "we have l" << i << "|p" << i << " = " << *(parentX->head()->get(p)) << endl
	    << *parentR << " is in R" << endl
	    << "let r'" << i << " be the right-hand side of this rule" << endl
	    << "theta" << i << " = " << *theta
	    << " is a mgu of l" << i << "|p" << i << " and r'" << i << endl << endl
	    << "==> ";
    }

  Rule::display(out);

  if (elim)
    if (iteration == 0) out << " is in elim_R(R)" << endl;
    else out << " is in EU_R^" << iteration << endl;
  else
    if (iteration == 0) out << " is in R" << endl;
    else out << " is in U_R^" << iteration << endl;
}
