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


/************************************************************
 *  A class that implements a data structure used to store  *
 *  unfolded rules.                                         *
 ************************************************************/

#define DIM            100 // the dimension of defined tab below


class RuleSet
{
 private:
  list<Rule*> **tab; // a DIM x DIM array

 public:
  // Constructor, destructor:
  RuleSet     ( );
  ~RuleSet    ( );
  // Insert:
  void insert ( int, int, Rule* );
  // Find:
  bool member ( int, int, Rule* ) const;
  // Clear:
  void clear  ( );
};
