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


/********************************
 *  A rule of a logic program:  *
 ********************************/

class RuleLP: public Rule
{
 public:
  // Constructors:
  RuleLP            ( Tree *head, Tree *body = NULL,
		      bool normalize=true, int max_var=0 );
  RuleLP            ( Tree *head, const list<Tree*>& body,
		      bool normalize=true, int max_var=0 );
  // Input/Output:
  void    display   ( ostream& ) const;
};
