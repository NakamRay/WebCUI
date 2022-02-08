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


/***************************************
 *  Max size of a substitution domain  *
 ***************************************/

#define SUBS_SIZE      100


/*****************************************************
 *    A class to model substitution of variables:    *
 *****************************************************/

class Substitution
{
 private:
  Tree* range[SUBS_SIZE];
  int   nb_maps; // used in is_epsilon

 public:
  // Constructors/Destructor:
  Substitution                ( );
  Substitution                ( const Substitution& );
  ~Substitution               ( );
  // Get/Set:
  void          set           ( Tree *X, Tree *t );  // Add X/t to *this
  void          clean         ( );                   // Delete every X/X
  bool          is_epsilon    ( ) const { return nb_maps == 0; };
  // Operators:
  Substitution& operator =    ( const Substitution& );
  bool          operator +    ( Substitution* );     // Union -- returns false if union is not defined
  Substitution* operator *    ( Substitution* );     // Composition
  Tree*         operator ()   ( Tree *&t ) const;    // Apply *this to t - return the new t
  Tree*         operator []   ( Tree *X ) const;     // Return image of X
  // Misc:
  Substitution* copy          ( ) const; // Return a copy of *this
  // Output:
  friend ostream& operator << ( ostream&, const Substitution& );
};
