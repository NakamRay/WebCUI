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


/******************************************
 *  Rules computed when unfolding a TRS:  *
 ******************************************/

/*
 *  T_R(X) = { (l -> r[p<-r'])theta | l -> r in X,
 *                                  | p in Pos(r),
 *                                  | l' -> r' in R renamed with fresh variables,
 *                                  | theta in mgu(r|p, l')
 *           }
 *           U
 *           { (l[p<-l'] -> r)theta | l -> r in X,
 *                                  | p in Pos(l),
 *                                  | l' -> r' in R renamed with fresh variables,
 *                                  | theta in mgu(l|p, r')
 *           }
 */

class UnfoldedRule: public Rule
{
 private:
  int           iteration;  // corresponding iteration of T_R
  Position      p;          // refers to p in above definition
  Substitution  *theta;     // refers to theta in the above definition
  Rule          *parentX;   // refers to l->r in above definition
  Rule          *parentR;   // refers to l'->r' in above definition
  bool          forward_or_backward; // true (resp. false) indicates that this rule was
                                     // obtained from a forward (resp. backward) narrowing
  bool          elim;       // true (resp. false) indicates that this rule was obtained
                            // with useless rules elimination on (resp. off)

 public:
  // Constructors/Destructor:
  UnfoldedRule         ( Tree *head, Tree *body,
			 int iteration, Position p, Substitution *theta,
			 Rule *parentX, Rule *parentR, bool forward_or_backward, bool elim,
			 bool normalize=true, int max_var=0 );
  UnfoldedRule         ( Tree *head, Tree *body, bool elim );
  ~UnfoldedRule        ( );
  // Misc:
  Rule*   copy         ( ) const;
  // Input/Output:
  void    display      ( ostream& ) const;
};
