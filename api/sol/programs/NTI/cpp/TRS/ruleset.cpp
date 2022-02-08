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


/* --------------- Constructors/Destructor: --------------- */

RuleSet::RuleSet( )
{
  tab = new list<Rule*>*[DIM];
  for (int i = 0; i < DIM; i++)
    tab[i] = new list<Rule*>[DIM];
}

RuleSet::~RuleSet( )
{
  list<Rule*>::iterator it;
  for (int i = 0; i < DIM; i++)
    {
      for (int j = 0; j < DIM; j++)
	{
	  for (it = tab[i][j].begin(); it != tab[i][j].end(); it++) delete *it;
	  tab[i][j].clear();
	}
      delete [] tab[i];
    }
  delete [] tab;
}


/* --------------- Insert: --------------- */

void RuleSet::insert( int l, int r, Rule *R )
{
  if (l < 0 || DIM <= l || r < 0 || DIM <= r)
    ERROR("void RuleSet::insert( int l, int r, Rule *R )",
	  "index out of range");

  tab[l][r].push_front(R->copy());
}


/* --------------- Find: --------------- */

bool RuleSet::member( int l, int r, Rule *R ) const
{
  if (l < 0 || DIM <= l || r < 0 || DIM <= r)
    ERROR("bool RuleSet::member( int l, int r, Rule *R ) const",
	  "index out of range");

  list<Rule*>::iterator it;
  for (it = tab[l][r].begin(); it != tab[l][r].end(); it++)
    if (**it == *R) return true;
  return false;
}


/* --------------- Clear: --------------- */

void RuleSet::clear( )
{
  for (int i = 0; i < DIM; i++)
    for (int j = 0; j < DIM; j++)
      tab[i][j].clear();
}
