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


/* --------------- Constructors: --------------- */

RuleLP::RuleLP( Tree *head, Tree *body,
		bool normalize, int max_var ): Rule(head, body, normalize, max_var)
{}

RuleLP::RuleLP( Tree *head, const list<Tree*>& body,
		bool normalize, int max_var ): Rule(head, body, normalize, max_var)
{}


/* --------------- Input/Output: --------------- */

void RuleLP::display( ostream& out ) const
{
  if (h) out << *h;
  else out << "NULL";
  if (b_size > 0) out << " :- ";
  for (int i = 0; i < b_size; i++)
    {
      if (b[i] == NULL) out << "NULL";
      else out << *(b[i]);
      if (i < b_size-1) out << ", ";
    }
  out << '.';
}
