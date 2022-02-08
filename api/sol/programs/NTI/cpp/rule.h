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


/************
 *  Rules:  *
 ************/
class Rule
{
 protected:
  Tree *h;      // the head of the rule
  Tree **b;     // the body of the rule = dynamic array of pointers
  int  b_size;  // the number of atoms in the body
  int  max_var; // the max variable index (>=0) in the rule

 public:
  // Constructors/Destructor:
  Rule                         ( Tree *head, Tree *body = NULL,
				 bool normalize=true, int max_var=0 );
  Rule                         ( Tree *head, const list<Tree*>& body,
				 bool normalize=true, int max_var=0 );
  virtual ~Rule                ( );
  // Get/Set:
  bool            is_fact      ( )       const { return b_size == 0; };
  Tree*           head         ( )       const { return h; };
  Tree*           body         ( int i ) const; // returns the (i-1)-th element of the body
  void            set_body     ( int i, Tree* t ); // sets the (i-1)-th element of the body to t
  int             body_size    ( )       const { return b_size; };
  int             maxv         ( )       const { return max_var; };
  // Operators:
  bool            operator ==  ( const Rule& ) const;
  // Misc:
  Rule*           rename       ( int& );
  virtual Rule*   copy         ( ) const;
  void            clear_body   ( );
  // Input/Output:
  virtual void    display      ( ostream& ) const;
  friend ostream& operator <<  ( ostream&, const Rule& );
};
