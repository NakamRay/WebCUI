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


/************************
 *    Looping pairs:    *
 ************************/

class Loop_pair
{
 private:
  Program* BinSeq;
  Sop*     tau;

 public:
  // Constructors/Destructor:
  Loop_pair  ( Rule *r,     Sop *tau = NULL );
  Loop_pair  ( Program *BP, Sop *tau = NULL );
  ~Loop_pair ( );
  // Operators:
  bool   operator == ( Loop_pair& ) const;
  // Misc:
  void   plug        ( Rule*, Mode*, Dict& ) const;
  // Output:
  friend ostream& operator << ( ostream&, const Loop_pair& );
};


/***********************
 *    Dictionaries:    *
 ***********************/

class Dict
{
 private:
  list<Loop_pair*> elements;
  list<Loop_pair*>::iterator current;

 public:
  // Constructors/Destructor:
  ~Dict ( );
  // Add/Remove:
  void         push_back ( Loop_pair* lp ) { elements.push_back(lp); };
  void         merge     ( Dict* D ) { elements.splice(elements.end(), D->elements); };
  // Iteration:
  void         init      ( ) { current = elements.begin(); };
  Loop_pair*   next      ( ) { return *(current++); };
  bool         exists    ( ) { return (current != elements.end()); };
  // Misc:
  unsigned int size      ( ) const { return elements.size();  };
  Loop_pair*   front     ( ) const { return elements.front(); };
  // Output:
  friend ostream& operator << ( ostream&, const Dict& );
};
