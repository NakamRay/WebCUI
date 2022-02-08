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


/**************************************
 *  Graph of functional dependencies  *
 **************************************/

struct Edge
{
  Tree *start;
  int end;

  Edge ( Tree *start, int end )
  { this->start = start; this->end = end; };

  ~Edge ()
  { if (start) delete start; };

  void display ( ostream&, const Symbtab& ) const;
};

class Graph
{
 private:
  list<Edge*> edges;
  list<Edge*>::iterator current; // used for iteration

  // these functions are used to compute the set of descendants:
  void  descendants_aux ( Tree*, DescendantSet& ) const;
  void  descendants     ( Tree*, DescendantSet& ) const; // computes Delta(t, 0) - {root(t)}

 public:
  // Constructors/Destructor:
  ~Graph                       ( );
  // Get/Set:
  bool             add_edge    ( Tree *start, int end );
  DescendantSet*   descendants ( Tree* t, int k ); // computes Delta(t, k)
  // Iteration:
  void             init        ( ) { current = edges.begin(); };
  bool             exists      ( ) { return current != edges.end(); };
  Edge*            next        ( ) { return *(current++); };
  // Input/Output:
  void             display     ( ostream&, const Symbtab& ) const;
};


/*************************
 *  Term Rewrite System  *
 *************************/

class TRS: public Program
{
 private:
  Graph         *graph_forward;   // the graph for the forward analysis
  Graph         *graph_backward;  // the graph for the backward analysis
  bool          *defined_symbols; // the set of defined symbols of the TRS
  list<Rule*>   garbage;          // rules to delete when non-termination proof is over
  bool          go_on;            // used for proving non-termination
  ostringstream proof;            // the non-termination proof output
  int           prune_depth;      // used to create the forward graph
  unsigned int  nb_generated_rules;
  bool          forwards, backwards;

  // these functions are used to compute the eliminating unfoldings:
  void         add                     ( Program&, Program&, RuleSet&, Rule* );
  bool         unfold                  ( Tree*, Rule*, Program&, RuleSet&, bool, int, int,
					 bool, bool );
  // these functions are used to compute the graphs of functional dependencies:
  bool         complete_forward        ( );
  bool         complete_backward       ( );
  // these functions are used during the eliminating process:
  void         beta_R                  ( Rule *R, Program& Result, int k );
  bool         useful_R                ( Tree *l, Tree *r, int k ) const;
  // these functions are used for proving non-termination:
  bool         prove                   ( bool forward, bool backward, bool elim, bool var );
  void         prove_parallel          ( bool elim, bool var );

 public:
   // Constructors/Destructor:
  TRS                                  ( );
  ~TRS                                 ( );
  // Graphs of functional dependencies:
  void         create_graph_forward    ( );
  void         create_graph_backward   ( );
  // Defined symbols:
  void         create_defined_symbols  ( );
  // Elimination function applied to every rule in 'this':
  bool         elim_R                  ( Program& Result, RuleSet& H, int k, bool elim );
  // Elimination function applied to rule R:
  bool         elim_R                  ( Rule *R, Program& Result, int k, bool elim );
  // Eliminating unfoldings:
  bool         EU_R                    ( Program& X, Program& Unf, RuleSet& H, int n, int k,
					 bool elim, bool var );
  // Prove non-termination:
  void         prove                   ( void *data );
  // Input/Output:
  void         display_if_killed       ( ostream& ) const;
  void         display_graph_forward   ( ostream&, const Symbtab& ) const;
  void         display_graph_backward  ( ostream&, const Symbtab& ) const;
};



/*******************************************
 * A class to handle command line options: *
 *******************************************/

class Option
{
 public:
  int  direction;
  bool elim;
  bool var;
  int  prune_depth;

  Option ( int dir, bool e, bool v, int p )
    { direction = dir; elim = e; var = v; prune_depth = p; }
};
