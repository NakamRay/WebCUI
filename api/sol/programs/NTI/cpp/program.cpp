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


/********************
 *  class Program:  *
 ********************/

/* --------------- Constructors/Destructor: --------------- */

Program::~Program( )
{
  list<Rule*>::iterator it;
  for (it = rules.begin(); it != rules.end(); it++)
    if (*it) delete *it;
  rules.clear();
}


/* --------------- List operations: --------------- */

Rule* Program::pop_front( )
{
  Rule* first = rules.front();
  rules.pop_front();
  return first;
}

bool Program::member( Rule *r ) const
{
  list<Rule*>::const_iterator it;
  for (it = rules.begin(); it != rules.end(); it++)
    if (**it == *r) return true;
  return false;
}


/* --------------- Input/Output: --------------- */

ostream& operator << ( ostream& out, const Program& P )
{
  list<Rule*>::const_iterator it;
  out << '{' << endl;
  for(it = P.rules.begin(); it != P.rules.end(); it++)
    if (*it == NULL) out << "  NULL rule" << endl;
    else out << "  " << **it << endl;
  out << '}' << P.rules.size() << " rule(s)" << endl;
  return out;
}
