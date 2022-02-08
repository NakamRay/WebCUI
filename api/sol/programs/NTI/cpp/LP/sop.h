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


/*************************************************
 *    Set of positions with associated terms:    *
 *************************************************/

class PosToTerm
{
 private:
  Tree* *range;      // a dynamic array
  int   current;     // used for iteration
  int   max_domsize; // max nb of elements of the domain
  int   domsize;     // nb of elements of the domain

 public:
  // Constructors/Destructor:
  PosToTerm                  ( int max_domsize );
  ~PosToTerm                 ( );
  // Get/Set:
  void        set             ( int, Tree* );
  int         card            ( ) const { return domsize; };
  // Operators:
  Tree*       operator []     ( int ) const;
  bool        operator ==     ( const PosToTerm& ) const;
  // Operations over the domain:
  bool        restrict_dom_to ( bool F[] );
  bool        in_domain       ( int ) const;
  bool        includes        ( Mode *m ) const; // is m included in Dom(*this) ?
  // Iteration over the domain:
  void        init            ( );
  int         next            ( );
  bool        exists          ( );
  // Misc:
  PosToTerm*  copy            ( ) const; // returns a copy of *this
  // Output:
  friend ostream& operator << ( ostream&, const PosToTerm& );
};


struct sop_entry
{
  int p;             // predicate symbol
  int n_p;           // arity of p
  PosToTerm *tau_p;  // associated set of positions

  sop_entry( int q, int n_q, PosToTerm *tau_q )
  { p = q; n_p = n_q; tau_p = tau_q; };
};

// Set Of Positions:
class Sop
{
 private:
  list<sop_entry> range;

 public:
  // Destructor:
  ~Sop                     ( );
  // Operators:
  PosToTerm*  operator []  ( Tree* );
  // Get/Set:
  bool        includes     ( int symbol, int arity, Mode *m ) const; // is m included in Dom((*this)[symbol]) ?
  // Set *this to be a DN set of position for a single rule or a program
  // using the mode m for symbol rel(A) and the set of positions tau:
  void        set_DN       ( Rule* r,     Tree* A, Sop* tau = NULL );
  void        set_DN       ( Program* BP, Tree* A, Sop* tau = NULL );
  // Output:
  friend ostream& operator <<  ( ostream&, const Sop& );
};
