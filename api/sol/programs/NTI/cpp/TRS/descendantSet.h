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


/********************************************************************************
 * A class to encode the set of descendants Delta(t) of a tree t as:            *
 *   - a tree f(Delta(t_1),...,Delta(t_m)) when t has the form f(t_1,...,t_m)   *
 * together with:                                                               *
 *   - a set {g_1,...,g_p} where for each i, t ->_G g_i                         *
 * where G is the graph of functional dependencies                              *
 ********************************************************************************/

class DescendantSet
{
 private:
  Symbtab         *symbtab;  // used for display
  // f(Delta(t_1),...,Delta(t_m)):
  int             root;      // f
  int             nb_args;   // m
  DescendantSet   **args;    // Delta(t_1),...,Delta(t_m)
  // {g_1,...,g_p}:
  int             p;
  bool            *tabg;     // an array of bool to encode this set

 public:
  // Constructors/Destructor:
  DescendantSet                     ( int root, int nb_args, Symbtab* );
  ~DescendantSet                    ( );
  // Get/Set:
  int             rel               ( ) const { return root; };
  int             arity             ( ) const { return nb_args; };
  void            set               ( int i, DescendantSet* Delta ); // replace Delta(t_i) with Delta
  void            add               ( int g ); // add g to {g_1,...,g_p}
  // Semi-unification:
  bool            semi_unifies_with ( const DescendantSet& ) const;
  bool            semi_unifies_with ( const Tree& ) const;
  // Input/Output:
  friend ostream& operator <<       ( ostream&, const DescendantSet& );
};
