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


/************************
 *   Class Loop_pair:   *
 ************************/

/* --------------- Constructor/Destructor: --------------- */

Loop_pair::Loop_pair( Rule *r, Sop *t )
{
  BinSeq = new Program;
  BinSeq->push_back(r);
  tau = t;
}

Loop_pair::Loop_pair( Program *BP, Sop *t )
{ BinSeq = BP; tau = t; }

Loop_pair::~Loop_pair( )
{
  if (BinSeq) delete BinSeq;
  if (tau)    delete tau;
}


/* --------------- Operators: --------------- */

bool Loop_pair::operator == ( Loop_pair& lp ) const
{
  Tree      *h    = BinSeq->front()->head();
  PosToTerm *p    = (*tau)[h];
  Tree      *h_lp = (lp.BinSeq)->front()->head();
  PosToTerm *p_lp = (*(lp.tau))[h_lp];

  return (*h == *h_lp) && (*p == *p_lp);
}


/* --------------- Misc: --------------- */

void Loop_pair::plug( Rule *r, Mode *m, Dict& D ) const
{
  Tree *H;
  Rule *r1;
  Program *BS;
  Sop *new_tau;
  Mode *ground_H;

  H = r->head();
  ground_H = H->ground_pos();
  r1 = BinSeq->front();
  if (tau_more_general(r->body(0), r1->head(), tau))
    {
      BS = new Program;
      BS->push_back(r->copy());
      BinSeq->init();
      while (BinSeq->exists()) BS->push_back(BinSeq->next()->copy());

      new_tau = new Sop;
      new_tau->set_DN(BS, H, tau);
      if (m == NULL || m->is_included_in(ground_H, (*new_tau)[H]))
	D.push_back(new Loop_pair(BS, new_tau));
      else
	{
	  delete new_tau;
	  delete BS;
	}
    }

  delete ground_H;
}


/* --------------- Output: --------------- */

ostream& operator << ( ostream& out, const Loop_pair& lp )
{
  Tree *h = (lp.BinSeq)->front()->head();
  PosToTerm *p = (*(lp.tau))[h];

  out << '(' << *h << ", " <<  *p << ')';

  return out;
}


/*****************
 *  Class Dict:  *
 *****************/

/* --------------- Constructors/Destructor: --------------- */

Dict::~Dict( )
{
  list<Loop_pair*>::iterator it;
  for (it = elements.begin(); it != elements.end(); it++)
    if (*it) delete *it;
}


/* --------------- Output: --------------- */

ostream& operator << ( ostream& out, const Dict& D )
{
  list<Loop_pair*> already;
  list<Loop_pair*>::const_iterator it;
  list<Loop_pair*>::iterator it_find;

  for (it = D.elements.begin(); it != D.elements.end(); it++)
    {
      for (it_find = already.begin(); it_find != already.end(); it_find++)
	if (**it_find == **it) break;
      if (it_find == already.end())
	{
	  out << **it << endl;
	  already.push_front(*it);
	}
    }

  return out;
}
