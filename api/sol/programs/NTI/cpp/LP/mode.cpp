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



/*****************
 *  class Mode:  *
 *****************/

/* --------------- Get/Set: --------------- */

void Mode::insert_sorted ( int i )
{
  list<int>::iterator it;
  for (it = positions.begin(); it != positions.end(); it++)
    if (*it == i) return;
    else if (i < *it) { positions.insert(it,i); return; }
  positions.push_back(i);
}


/* --------------- Misc: --------------- */

bool Mode::includes( Mode *m ) const
{
  if (m == NULL) return true;
  if (positions.size() < (m->positions).size()) return false;

  list<int>::const_iterator it;
  list<int>::iterator it_m;
  for (it = positions.begin(), it_m = (m->positions).begin();
       it_m != (m->positions).end();
       it_m++)
    {
      while (it != positions.end()) if (*it == *it_m) break; else it++;
      if (it == positions.end()) return false;
    }
  return true;
}

bool Mode::is_included_in ( Mode* m, PosToTerm* tau_p ) const
{
  list<int>::const_iterator it;
  list<int>::iterator it_m;
  for (it = positions.begin(), it_m = (m->positions).begin();
       it != positions.end();
       it++)
    {
      if ((*tau_p)[*it] == NULL)
	{
	  while (it_m != (m->positions).end())
	    if (*it == *it_m) break; else it_m++;
	  if (it_m == (m->positions).end()) return false;
	}
    }
  return true;
}


/* --------------- Output: --------------- */

ostream& operator << ( ostream& out, const Mode& m )
{
  list<int>::const_iterator it;
  unsigned int i;

  out << '[';
  for (i = 1, it = m.positions.begin(); it != m.positions.end(); it++, i++)
    {
      out << *it+1;
      if (i < m.positions.size()) out << ", ";
    }
  out << ']';

  return out;
}



/**********************
 *  class MultiMode:  *
 **********************/

/* --------------- Constructors/Destructor: --------------- */

void MultiMode::destroy( )
{
  list<Mode*>::iterator it;
  for (it = modes.begin(); it != modes.end(); it++)
    if (*it) delete *it;
  modes.clear();
}

MultiMode::~MultiMode( )
{ destroy(); }


/* --------------- Operators: --------------- */

MultiMode& MultiMode::operator = ( const MultiMode& mm )
{
  if (this != &mm)
    {
      destroy();

      Mode *m;
      list<Mode*>::const_iterator it;
      for (it = mm.modes.begin(); it != mm.modes.end(); it++)
	if (*it)
	  {
	    m = new Mode;
	    *m = **it;
	    modes.push_back(m);
	  }
	else modes.push_back(NULL);
    }
  return *this;
}


/* --------------- Output: --------------- */

ostream& operator << ( ostream& out, const MultiMode& mm )
{
  list<Mode*>::const_iterator it;
  unsigned int i;

  out << '[';
  for (i = 1, it = mm.modes.begin(); it != mm.modes.end(); it++, i++)
    {
      if (*it == NULL) out << "NULL mode";
      else out << **it;
      if (i < mm.modes.size()) out << ", ";
    }
  out << ']';

  return out;
}
