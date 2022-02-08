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


class Mode
{
 private:
  list<int> positions;
  list<int>::iterator current;

 public:
  // Get/Set:
  void insert_sorted ( int );
  // Iteration:
  void  init           ( ) { current = positions.begin(); };
  int   next           ( ) { return *(current++); };
  bool  exists         ( ) { return (current != positions.end()); };
  // Misc:
  bool  includes       ( Mode* ) const;
  bool  is_included_in ( Mode*, PosToTerm* ) const;
  // Output:
  friend ostream& operator << ( ostream&, const Mode& );
};


class MultiMode
{
 private:
  list<Mode*> modes;
  list<Mode*>::iterator current;

 public:
  // Constructors/Destructor:
  void       destroy    ( );
  ~MultiMode            ( );
  // Operators:
  MultiMode& operator = ( const MultiMode& );
  // Get/Set:
  void       push_back  ( Mode *m ) { modes.push_back(m); };
  void       clear      ( ) { modes.clear(); };
  // Iteration:
  void       init       ( ) { current = modes.begin(); };
  Mode*      next       ( ) { return *(current++); };
  bool       exists     ( ) { return (current != modes.end()); };
  // Output:
  friend ostream& operator << ( ostream&, const MultiMode& );
};
