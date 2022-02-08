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


/***************************
 *  A position in a term:  *
 ***************************/
class Position
{
 private:
  list<int> path;
  list<int>::iterator current; // used for iteration

 public:
  // Get/Set:
  int  length     ( ) const { return path.size(); };
  void clear      ( ) { path.clear(); };
  // Adding:
  void push_front ( int i ) { path.push_front(i); };
  void push_back  ( int i ) { path.push_back(i);  };
  // Concatenation:
  void operator * ( Position& p ) { path.splice(path.end(), p.path ); };
  // Iteration:
  void init       ( ) { current = path.begin(); };
  int  next       ( ) { return *(current++); };
  bool exists     ( ) { return current != path.end(); };
  // Output:
  friend ostream& operator << ( ostream&, const Position& );
};


/*****************************
 *  Trees (terms or atoms):  *
 *****************************/
class Tree
{
 protected:
  Symbtab *symbtab;      // used for display
  int     root;          // the top symbol of the tree
  int     nb_args;       // the arity of the top symbol
  Tree    **args;        // the arguments: a dynamic array of pointers
  int     current;       // used for iteration

 public:
  // Constructors/Destructor:
  Tree                            ( int root = NONE, int nb_args = 0, Symbtab* = NULL );
  virtual ~Tree                   ( );
  // Operators:
  virtual Tree&  operator =       ( const Tree& );
  Tree*&         operator []      ( int i );        // returns the (i-1)-th son
  Tree*          operator []      ( int i ) const;  // returns the (i-1)-th son
  bool           operator ==      ( const Tree& t ) const;
  bool           operator !=      ( const Tree& t ) const { return !(*this == t); };
  // Get/Set:
  bool           is_var           ( ) const { return (root < 0) && (nb_args == 0); };
  int            rel              ( ) const { return root; };
  int            arity            ( ) const { return nb_args; };
  Tree*          set              ( Position& where, Tree *new_subterm );
  Tree*          get              ( Position where );
  int            maxv             ( ) const;
  bool           is_not_ground    ( ) const;
  Mode*          ground_pos       ( ) const;
  Symbtab*       get_symbtab      ( ) const { return symbtab; };
  bool           is_ground_mode   ( ) const;
  // Iteration over the subterms:
  void           init             ( );
  Tree*          next             ( Position& p ); // returns the next subterm, whose position is placed in p
  bool           exists           ( );
  // Misc:
  void           parse            ( int vars[MAX_VAR], int& );
  virtual Tree*  rename           ( int n );
  virtual Tree*  copy             ( ) const;  // returns a copy of *this
  bool           occurs           ( int symbol ) const;
  bool           strict_subtree   ( Tree *t ) const; // is t a strict subterm of this ?
  bool           not_deeper_than  ( int k ) const;  // is this not deeper than k ?
  // Input/Output:
  virtual void   display_args     ( ostream& ) const;
  virtual void   display          ( ostream& ) const;
  friend ostream& operator <<     ( ostream&, const Tree& );
};
