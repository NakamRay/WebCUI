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


class Program
{
  // protected:
 public:
  list<Rule*>  rules;                 // the rules of the program
  list<Rule*>::iterator current;      // used for iteration

 public:
  // Destructor:
  virtual ~Program               ( );
  // List operations:
  unsigned int     size          ( ) const   { return rules.size(); };
  Rule*            front         ( ) const   { return rules.front(); };
  Rule*            pop_front     ( );
  void             push_back     ( Rule *r ) { rules.push_back(r); };
  bool             member        ( Rule* ) const;
  void             merge         ( Program& P ) { rules.splice(rules.end(), P.rules); };
  void             clear         ( ) { rules.clear(); };
  // Iteration:
  void             init          ( ) { current = rules.begin(); };
  Rule*            next          ( ) { return *(current++); };
  bool             exists        ( ) { return (current != rules.end()); };
  // Proving non-termination:
  virtual void     prove         ( void *data ) {};
  // Input/Output:
  virtual void     display_if_killed ( ostream& out ) const {};
  friend ostream&  operator <<   ( ostream&, const Program& );
};
