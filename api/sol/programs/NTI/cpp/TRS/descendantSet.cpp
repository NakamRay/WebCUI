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
 *  class DescendantSet:  *
 **************************/


/* --------------- Constructors/Destructor: --------------- */

DescendantSet::DescendantSet( int r, int m, Symbtab* s )
{
  symbtab = s;
  root    = r;
  nb_args = m;
  if (m > 0)
    {
      args = new DescendantSet*[m];
      for (int i = 0; i < m; i++) args[i] = NULL;
    }
  else args = NULL;
  p = s->nb_symb();
  if (p > 0)
    {
      tabg = new bool[p+1];
      for (int i = 0; i <= p; i++) tabg[i] = false;
    }
  else tabg = NULL;
}

DescendantSet::~DescendantSet( )
{
  root = NONE;
  if (args)
    {
      for (int i = 0; i < nb_args; i++) delete args[i];
      delete [] args;
    }
  args = NULL;
  nb_args = 0;
  if (tabg) delete tabg;
  p = 0;
}


/* --------------- Get/Set: --------------- */

void DescendantSet::set( int i, DescendantSet* Delta )
{
  if (i < 0) ERROR("void DescendantSet::set( int, DescendantSet* )",
		   "index is a negative integer");
  if (nb_args <= i) ERROR("void DescendantSet::set( int, DescendantSet* )",
			  "index is greater than arity");
  if (args == NULL) ERROR("void DescendantSet::set( int, DescendantSet* )",
			  "args tab is NULL");

  args[i] = Delta;
}

void DescendantSet::add( int g )
{
  if (g > p)
    ERROR("void DescendantSet::add( int g )",
	  "g is greater than the number of symbols read in the TRS");
  if (tabg == NULL) ERROR("void DescendantSet::add( int g )", "tabg is NULL");

  if (g < 0) tabg[p] = true;
  else tabg[g] = true;
}


/* --------------- Semi-unification: --------------- */

bool DescendantSet::semi_unifies_with( const DescendantSet& Delta ) const
{
  if (p != Delta.p)
    ERROR("bool DescendantSet::semi_unifies_with (const DescendantSet&) const",
	  "symbol tables are different");

  if (root < 0 || Delta.root < 0) return true;
  if (tabg[Delta.root] || Delta.tabg[root] || tabg[p] || Delta.tabg[p]) return true;
  for (int i = 0; i <= p; i++)
    if (tabg[i] && Delta.tabg[i]) return true;
  if (root != Delta.root || nb_args != Delta.nb_args) return false;
  for (int i = 0; i < nb_args; i++)
    {
      if (args[i] == NULL && Delta.args[i] == NULL) continue;
      if (args[i] == NULL || Delta.args[i] == NULL) return false;
      if (!args[i]->semi_unifies_with(*(Delta.args[i]))) return false;
    }
  return true;
}

bool DescendantSet::semi_unifies_with( const Tree& t ) const
{
  if (root < 0 || t.is_var()) return true;
  if (tabg[t.rel()] || tabg[p]) return true;
  if (root != t.rel() || nb_args != t.arity()) return false;
  for (int i = 0; i < nb_args; i++)
    if (args[i] != NULL && !args[i]->semi_unifies_with(*t[i])) return false;
  return true;
}


/* --------------- Input/Output: --------------- */

ostream& operator <<  ( ostream& out, const DescendantSet& Delta )
{
  out << '[';
  // display f(Delta(t_1),...,Delta(t_m)):
  if (Delta.root >= 0)
    {
      out << (Delta.symbtab)->get_lexeme(Delta.root);
      if (Delta.nb_args > 0)
	{
	  out << '(';
	  for (int i = 0; i < Delta.nb_args; i++)
	    {
	      if ((Delta.args)[i] == NULL) out << "NULL";
	      else out << *((Delta.args)[i]);
	      if (i < Delta.nb_args-1) out << ',';
	    }
	  out << ')';
	}
    }
  else out << 'x';
  // display {g_1,...,g_p}:
  out << ", {";
  for (int i = 0; i < Delta.p; i++)
    {
      if ((Delta.tabg)[i])
	{
	  out << (Delta.symbtab)->get_lexeme(i);
	  if (i < Delta.p-1) out << ',';
	}
    }
  if ((Delta.tabg)[Delta.p]) out << 'x';
  out << "}]";

  return out;
}
