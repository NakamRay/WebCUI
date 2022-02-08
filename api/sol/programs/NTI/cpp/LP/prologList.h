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


/******************************************************
 * Root symbol of a tree representing a list          *
 * must be greater than SYMBTAB_SIZE (../symbtab.h):  *
 ******************************************************/

#define LISTSYMB   1000


/***********************
 *    Prolog Lists:    *
 ***********************/
class List: public Tree
{
 public:
  // Constructors/Destructor:
  List                 ( );  // constructs an empty list
  List                 ( int var ); // constructs a list variable
  // Operators:
  List& operator =     ( const List& );
  // Get/Set:
  void    push_front   ( Tree* );
  // Misc:
  Tree*   copy         ( ) const;  // returns a copy of *this
  // Input/Output:
  void    display_args ( ostream& ) const;
  void    display      ( ostream& ) const;
};
