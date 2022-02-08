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


/********************
 *  class Program:  *
 ********************/

/* --------------- Bottom-up binary unfoldings: --------------- */

void add_bot( Rule *r, Program& X, Program& new_X )
{
  if (X.member(r)) delete r;
  else if (new_X.member(r)) delete r;
  else new_X.push_back(r);
}

void ProgramLP::rec_add_bot( Rule *r, int i, int maxvar, const Substitution& theta,
			     Program& X, Program& new_X ) const
{
  Rule *new_r, *r_X_copy;
  Tree *H, *B, *B_i;
  Substitution *mu = NULL;
  int m;

  // If every atom of the body has been unfolded:
  if (i >= r->body_size())
    {
      H = r->head()->copy();
      new_r = new RuleLP( theta(H) );
      add_bot(new_r, X, new_X);
      return;
    }
  // Else, we consider b_i = the i-th atom of the body
  B_i = r->body(i);
  // Unfold b_i using the rules of id:
  H = r->head()->copy(); B = B_i->copy();
  new_r = new RuleLP(theta(H), theta(B));
  add_bot(new_r, X, new_X);
  // Unfold b_i using the rules of X:
  list<Rule*>::iterator it;
  for (it = X.rules.begin(); it != X.rules.end(); it++)
    {
      if ((*it)->head()->rel() != B_i->rel()) continue;
      m = maxvar;
      B = B_i->copy();
      r_X_copy = (*it)->copy()->rename(m);
      if (unify(theta(B), r_X_copy->head(), mu))
	{
	  delete B;
	  Substitution new_theta = theta;
	  new_theta*mu;
	  if ((*it)->is_fact())
	    { // Unfolding b_i using a fact:
	      delete r_X_copy;
	      rec_add_bot(r, i+1, m, new_theta, X, new_X);
	    }
	  else
	    { // Unfolding b_i using a binary rule:
	      H = r->head()->copy(); B = r_X_copy->body(0);
	      new_r = new RuleLP(new_theta(H), new_theta(B));
	      add_bot(new_r, X, new_X);
	      r_X_copy->clear_body(); delete r_X_copy;
	    }
	  delete mu; mu = NULL;
	}
      else { delete B; delete r_X_copy; }
    }
}

void ProgramLP::T_P_beta( Program& X, Program& new_X ) const
{
  list<Rule*>::const_iterator itp;
  for (itp = rules.begin(); itp != rules.end(); itp++)
    {
      Substitution theta;
      rec_add_bot(*itp, 0, (*itp)->maxv(), theta, X, new_X);
    }
}


/* --------------- Tools for non-termination: --------------- */

void unit_loop( Rule *r, Mode *m, Dict& D )
{
  Sop  *tau;
  Tree *H = r->head(), *B = r->body(0);
  Mode *ground_H = H->ground_pos();

  tau = new Sop;
  tau->set_DN(r, H);
  if ( (m == NULL || m->is_included_in(ground_H, (*tau)[H])) &&
       tau_more_general(B, H, tau) )
    D.push_back(new Loop_pair(r->copy(), tau));
  else delete tau;

  delete ground_H;
}

void loops_from_dict( Rule *r, Mode *m, Dict& D, Dict& DD )
{
  D.init();
  while (D.exists()) (D.next())->plug(r, m, DD);
}

Mode* mode_from( Tree *A )
{
  Mode *m = new Mode;
  for (int i = 0; i < A->arity(); i++)
    {
      if ((*A)[i]->is_ground_mode())
	m->insert_sorted(i);
    }
  return m;
}


/* --------------- Bottom-up non-termination: --------------- */

void ProgramLP::prove( void *unused )
{
  Dict D_p, D_q;
  int k, p, q, n_p, n_q;
  Rule *r;
  Program Unf, new_Unf;
  Mode *m_p;

  if (query == NULL) {
    cout << "No target query!" << endl;
    return;
  }

  p = ((Tree*) query)->rel(); n_p = ((Tree*) query)->arity();
  m_p = mode_from((Tree*) query);

  // Computes iterations of T_P_beta:
  for (k = 0; D_p.size() == 0; k++)
    {
      T_P_beta(Unf, new_Unf);

      // Unit loops:
      new_Unf.init();
      while (D_p.size() == 0 && new_Unf.exists())
	{
	  r = new_Unf.next();

	  if (r->is_fact()) continue;
	  q = r->head()->rel(); n_q = r->head()->arity();
	  if (r->body(0)->rel() != q || r->body(0)->arity() != n_q) continue;

	  if (q == p && n_q == n_p) unit_loop(r, m_p, D_p);
	  else unit_loop(r, NULL, D_q);
	}

      // Loops from dict:
      new_Unf.init();
      while (D_p.size() == 0 && new_Unf.exists())
	{
	  r = new_Unf.next();

	  if (r->is_fact() || r->head()->rel() != p || r->head()->arity() != n_p) continue;
	  if (r->body(0)->rel() == p && r->body(0)->arity() == n_p) continue;

	  loops_from_dict(r, m_p, D_q, D_p);
	}

      Unf.merge(new_Unf);
    }

  delete m_p;

  if (D_p.size())
    cout << "NO" << endl
	 << "[Etienne Payet and Fred Mesnard. "
	 << "Non-termination inference of logic programs. TOPLAS 2006]" << endl
	 << "The following looping pair has been inferred at iteration "
	 << k << " of T_P_beta:" << endl
	 << "  " << *(D_p.front()) << endl
	 << "which proves non-termination of mode " << *query << endl;
  else cout << "DON'T KNOW!" << endl
	    << "Non-termination proof of mode " << *query
	    << " failed!" << endl;
}
