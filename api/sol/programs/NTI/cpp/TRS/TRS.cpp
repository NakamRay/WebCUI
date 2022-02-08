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


#include "../global.h"



/****************************************
 *  Graphs of functional dependencies:  *
 ****************************************/

/* --------------- Constructors/Destructor: --------------- */

Graph::~Graph( )
{
  list<Edge*>::iterator it;
  for (it = edges.begin(); it != edges.end(); it++)
    if (*it) delete *it;
  edges.clear();
}


/* --------------- Get/Set: --------------- */

bool Graph::add_edge( Tree *start, int end)
{
  if (end < 0) end = -1;

  list<Edge*>::iterator it;
  for (it = edges.begin(); it != edges.end(); it++)
    if ( variant((*it)->start, start) && (*it)->end == end ) return false;

  edges.push_back(new Edge(start->copy(), end));
  return true;
}

void Graph::descendants_aux( Tree* t, DescendantSet& Delta_t ) const
{
  list<Edge*>::const_iterator it;
  for (it = edges.begin(); it != edges.end(); it++)
    //if (unify((*it)->start, t)) Delta_t.add((*it)->end);
    if ((*it)->start->is_var() || (*it)->start->rel() == t->rel())
      Delta_t.add((*it)->end);
}

void Graph::descendants( Tree* t, DescendantSet& Delta_t ) const
{
  // first, rename t so that it is variable
  // disjoint with the graph:
  Tree *t_copy = t->copy()->rename(t->get_symbtab()->nb_symb());
  // then, compute the descendants:
  descendants_aux(t_copy, Delta_t);
  delete t_copy;
}

DescendantSet* Graph::descendants( Tree* t, int k )
{
  if (t == NULL)
    ERROR("DescendantSet* Graph::descendants( Tree* t, int k )", "t is NULL");
  if (k < 0)
    ERROR("DescendantSet* Graph::descendants( Tree* t, int k )", "k < 0");

  DescendantSet *Delta = new DescendantSet(t->rel(), t->arity(), t->get_symbtab());
  descendants(t, *Delta); // computes {g_1,...,g_p}
  if (k > 0)
    // computes f(Delta(t_1),...,Delta(t_m)):
    for (int i = 0; i < t->arity(); i++)
      Delta->set(i, descendants((*t)[i], k-1));

  return Delta;
}


/* --------------- Input/Output: --------------- */

void Edge::display( ostream& out, const Symbtab& symbtab ) const
{
  if (start) out << *start;
  else out << "NULL";

  out << " -> ";

  if (end >= 0) out << symbtab.get_lexeme(end);
  else out << end; //"<var>";
}

void Graph::display( ostream& out, const Symbtab& symbtab ) const
{
  list<Edge*>::const_iterator it;
  for (it = edges.begin(); it != edges.end(); it++)
    {
      if (*it) (*it)->display(out, symbtab);
      else out << "NULL";
      out << endl;
    }
}




/***************************
 *  Term Rewrite Systems:  *
 ***************************/

/* --------------- Constructor/Destructor: --------------- */

TRS::TRS( )
{
  graph_forward = graph_backward = NULL;
  defined_symbols = NULL;
  prune_depth = 0;
  nb_generated_rules = 0;
  forwards = backwards = false;
}

TRS::~TRS( )
{
  if (graph_forward)   delete graph_forward;
  if (graph_backward)  delete graph_backward;
  if (defined_symbols) delete [] defined_symbols;

  list<Rule*>::iterator it;
  for (it = garbage.begin(); it != garbage.end(); it++) delete *it;
  garbage.clear();
}


/* --------------- Graph for the forward analysis : --------------- */

bool TRS::complete_forward( )
{
  Edge *edge;
  bool has_changed = false;
  list<Rule*>::iterator it;

  graph_forward->init();
  while (graph_forward->exists())
    {
      edge = graph_forward->next();
      for (it = rules.begin(); it != rules.end(); it++)
	if (edge->end == (*it)->head()->rel() || edge->end < 0)
	  has_changed = graph_forward->add_edge(edge->start, (*it)->body(0)->rel());
    }
  return has_changed;
}

void TRS::create_graph_forward( )
{
  graph_forward = new Graph;

  /*
  list<Rule*>::iterator it;
  for (it = rules.begin(); it != rules.end(); it++)
    graph_forward->add_edge((*it)->head(), (*it)->body(0)->rel());
  */

  Tree* r, *r_p;
  Position p;
  list<Rule*>::iterator it;
  for (it = rules.begin(); it != rules.end(); it++)
    {
      r = (*it)->body(0);
      r->init();
      while (r->exists())
	{
	  r_p = r->next(p);
	  //if (p.length() <= prune_depth && !r_p->is_var())
	  if (p.length() <= prune_depth && (p.length() == 0 || !r_p->is_var()))
	    graph_forward->add_edge((*it)->head(), r_p->rel());
	}
    }

  while (complete_forward());
}

/* --------------- Graph for the backward analysis : --------------- */

bool TRS::complete_backward( )
{
  Edge *edge;
  bool has_changed = false;
  list<Rule*>::iterator it;

  graph_backward->init();
  while (graph_backward->exists())
    {
      edge = graph_backward->next();
      for (it = rules.begin(); it != rules.end(); it++)
	if ( edge->end == (*it)->body(0)->rel() || (*it)->body(0)->is_var() )
	  has_changed = graph_backward->add_edge(edge->start, (*it)->head()->rel());
    }
  return has_changed;
}

void TRS::create_graph_backward( )
{
  graph_backward = new Graph;

  // We only add edges of the form t -> f where t -> f(...) is a
  // rule of R^-1 (we do not consider the strict subterms of f(...),
  // unlike the forward graph)
  list<Rule*>::iterator it;
  for (it = rules.begin(); it != rules.end(); it++)
    graph_backward->add_edge((*it)->body(0), (*it)->head()->rel());

  while (complete_backward());
}


/* --------------- Defined symbols: --------------- */

void TRS::create_defined_symbols( )
{
  int p = (rules.front())->head()->get_symbtab()->nb_symb();
  defined_symbols = new bool[p];
  for (int i = 0; i < p; i++) defined_symbols[i] = false;
  list<Rule*>::iterator it;
  for (it = rules.begin(); it != rules.end(); it++)
    if (!(*it)->head()->is_var())
      defined_symbols[(*it)->head()->rel()] = true;
}


/* --------------- Tree id: --------------- */

int id_rec( Tree* t )
{
  int n = t->is_var()?-1*t->rel():t->rel();
  for (int i = 0; i < t->arity(); i++)
    n += id_rec((*t)[i]);

  return n;
}

int id( Tree* t )
{
  int n = id_rec(t), s;
  while (n >= DIM)
    {
      // set n to the sum of its digits:
      s = 0;
      while (n > 0) { s += n % 10; n /= 10; }
      n = s;
    }
  return n;
}


/* --------------- Elimination functions: --------------- */

bool TRS::elim_R( Program& Result, RuleSet& H, int k, bool elim )
{
  Rule *R;
  Program X;
  int l, r;
  list<Rule*>::const_iterator it;
  for (it = rules.begin(); it != rules.end(); it++)
    {
      // apply elimination function to the rule;
      // if non-termination is proved, return true:
      if (elim_R(new UnfoldedRule((*it)->head()->copy(), (*it)->body(0)->copy(), elim),
		 X, k, elim))
	return true;
      // else add the resulting rules to Result;
      // we proceed as follows in order to delete multiple occurrences
      // of the same rule:
      while (X.size() > 0)
	{
	  R = X.pop_front();
	  l = id(R->head()); r = id(R->body(0));
	  if (H.member(l, r, R)) delete R;
	  else { nb_generated_rules++; Result.push_back(R); H.insert(l, r, R); }
	}
    }
  // if control goes here, then non-termination could not be proved:
  return false;
}

bool TRS::elim_R( Rule *R, Program& Result, int k, bool elim )
{
  Substitution *theta = NULL;
  Position p;
  // first, try the unification test:
  Tree *t = deep_unify_test(R->head(), R->body(0), theta, p);
  if (t)
    {
      proof << endl << "NO" << endl << endl
	    << "let R be the TRS under consideration" << endl << endl
	    << *R
	    << "let l be the left-hand side and r be the right-hand side of this rule" << endl
	    << "let p = " << p << endl
	    << "let theta = " << *theta << endl
	    << "let theta' = {}" << endl
	    << "we have r|p = " << *(R->body(0)->get(p)) << " and" << endl
	    << "theta'(theta(l)) = theta(r|p)" << endl
	    << "so, theta(l) = " << *t << " is non-terminating w.r.t. R"  << endl;
      nb_generated_rules++; // R counts
      delete R; delete theta; delete t;
      return true;
    }
  // unification test did not succeed, try match test:
  p.clear();
  t = deep_match_test(R->head(), R->body(0), theta, p);
  if (t)
    {
      proof << endl << "NO" << endl << endl
	    << "let R be the TRS under consideration" << endl << endl
	    << *R
	    << "let l be the left-hand side and r be the right-hand side of this rule" << endl
	    << "let p = " << p << endl
	    << "let theta = {}" << endl
	    << "let theta' = "  << *theta << endl
	    << "we have r|p = " << *(R->body(0)->get(p)) << " and" << endl
	    << "theta'(theta(l)) = theta(r|p)" << endl
	    << "so, theta(l) = " << *t << " is non-terminating w.r.t. R"  << endl;
      nb_generated_rules++; // R counts
      delete R; delete theta; delete t;
      return true;
    }
  // unification test and match test did not succeed
  // if elim is false, keep the rule R:
  if (!elim) Result.push_back(R);
  // else, apply the elimination function to rule R when depth(R) <= k:
  else if (R->head()->not_deeper_than(k) && R->body(0)->not_deeper_than(k))
    beta_R(R, Result, k);
  else { delete R; go_on = true; }
  // if control goes here, then non-termination could not be proved:
  return false;
}

void TRS::beta_R( Rule *R, Program& Result, int k )
{
  Tree *l = R->head(), *r = R->body(0);
  int m = r->arity();

  if (useful_R(l, r, k)) Result.push_back(R);
  else
    {
      for (int i = 0; i < m; i++)
	{
	  R->set_body(0, (*r)[i]);
	  beta_R(R->copy(), Result, k);
	}
      R->set_body(0, r);
      delete R;
    }
}

bool TRS::useful_R( Tree *l, Tree *r, int k ) const
{
  if (!r->is_var() && !defined_symbols[r->rel()]) return false;
  if (l->strict_subtree(r)) return false;

  DescendantSet *Delta_l = NULL;
  DescendantSet *Delta_r = NULL;
  bool res = true;
  if (forwards && backwards)
    {
      Delta_l = graph_backward->descendants(l, k);
      Delta_r = graph_forward->descendants(r, k);
      res = Delta_l->semi_unifies_with(*Delta_r);
    }
  else if (forwards)
    {
      Delta_r = graph_forward->descendants(r, k);
      res = Delta_r->semi_unifies_with(*l);
    }
  else if (backwards)
    {
      Delta_l = graph_backward->descendants(l, k);
      res = Delta_l->semi_unifies_with(*r);
    }

  if (Delta_l) delete Delta_l;
  if (Delta_r) delete Delta_r;
  return res;
}


/* --------------- Eliminating unfoldings: --------------- */

void TRS::add( Program& AbstractRules, Program& Unf, RuleSet& H, Rule *ruleX )
{
  Rule *R;
  int l, r;
  while (AbstractRules.size() > 0)
    {
      R = AbstractRules.pop_front();
      l = id(R->head()); r = id(R->body(0));
      if (H.member(l, r, R)) delete R;
      else
	{
	  nb_generated_rules++;
	  Unf.push_back(R);
	  H.insert(l, r, R);
	  if (garbage.size() == 0 || garbage.back() != ruleX)
	    garbage.push_back(ruleX);
	}
    }
}

bool TRS::unfold( Tree *t, Rule *ruleX, Program& Unf, RuleSet& H, bool unfolding_direction,
		  int i, int k, bool elim, bool var )
{
  Tree *t_p, *l, *r;
  Position p;
  Rule *ruleR_copy, *new_rule;
  Substitution *theta = NULL;
  list<Rule*>::iterator itR;
  int maxvar;
  Program AbstractRules;

  t->init();
  while (t->exists())
    {
      t_p = t->next(p);
      if (!var && t_p->is_var()) continue;
      for (itR = rules.begin(); itR != rules.end(); itR++)
	{
	  maxvar = ruleX->maxv();
	  ruleR_copy = (*itR)->copy()->rename(maxvar);

	  if (unfolding_direction) unify(t_p, ruleR_copy->head(), theta); // forwards unfoldings
	  else unify(t_p, ruleR_copy->body(0), theta); // backwards unfoldings

	  if (theta)
	    {
	      // create the new rule:
	      l = ruleX->head()->copy();
	      r = ruleX->body(0)->copy();
	      if (unfolding_direction)
		{ // forward unfoldings
		  r->set(p, ruleR_copy->body(0));
		  new_rule = new UnfoldedRule( (*theta)(l), (*theta)(r), i, p, theta,
					       ruleX, ruleR_copy, true, elim );
		}
	      else
		{ // backward unfoldings
		  l->set(p, ruleR_copy->head());
		  new_rule = new UnfoldedRule( (*theta)(l), (*theta)(r), i, p, theta,
					       ruleX, ruleR_copy, false, elim );
		}
	      // apply elimination function to the new rule;
	      // if non-termination is proved, return true
	      if (elim_R(new_rule, AbstractRules, k, elim))
		return true;
	      else
		// else add the resulting rules to Unf
		add(AbstractRules, Unf, H, ruleX);
	      // reset theta:
	      theta = NULL;
	    }
	  else delete ruleR_copy;
	}
    }

  // if control goes here, then non-termination could not be proved:
  return false;
}

bool TRS::EU_R( Program& X, Program& Unf, RuleSet& H, int i, int k, bool elim, bool var )
{
  Rule *ruleX;

  while (X.size() > 0)
    {
      ruleX = X.pop_front();

      // forward unfolding - if non-termination is proved, return true:
      if (forwards && unfold(ruleX->body(0), ruleX, Unf, H, true, i, k, elim, var))
	return true;
      // backward unfolding - if non-termination is proved, return true:
      if (backwards && unfold(ruleX->head(), ruleX, Unf, H, false, i, k, elim, var))
	return true;
      // ruleX is not the parent of a created rule:
      if (garbage.size() > 0 && garbage.back() != ruleX) delete ruleX;
    }

  // if control goes here, then non-termination could not be proved:
  return false;
}


/* --------------- Non-termination proof: --------------- */

void TRS::prove( void *data )
{
  if (rules.size() == 0)
    { cerr << "The rewrite system is empty!" << endl; exit(EXIT_SUCCESS); }

  // Read data (option line arguments):
  if (data == NULL) { cerr << "data is NULL!" << endl; exit(EXIT_FAILURE); }
  int direction = ((Option*)data)->direction;
  bool elim = ((Option*)data)->elim;
  bool var = ((Option*)data)->var;
  prune_depth = ((Option*)data)->prune_depth;
  delete (Option*)data;

  // Create the graphs of functional dependencies:
  if (graph_forward == NULL) create_graph_forward();
  if (graph_backward == NULL) create_graph_backward();
  // Create the set of defined symbols:
  if (defined_symbols == NULL) create_defined_symbols();

  // Prove:
  switch (direction)
    {
    case 0: // prove in parallel
      prove_parallel(elim, var);
      break;
    case 1: // prove forwards
      prove(true, false, elim, var);
      cout << proof.str();
      break;
    case 2: // prove backwards
      prove(false, true, elim, var);
      cout << proof.str();
      break;
    default: // prove forwards+backwards
      prove(true, true, elim, var);
      cout << proof.str();
    }
}

void TRS::prove_parallel( bool elim, bool var )
{
  // a pipe to transfer forward proof output to the main process:
  int forward_pipe[2];
  if (pipe(forward_pipe) != 0) { perror("pipe"); exit(EXIT_FAILURE); }
  pid_t forward_process = fork();
  if (forward_process < 0) { perror("fork"); exit(EXIT_FAILURE); }
  else if (forward_process)
    {
      // a pipe to transfer backward proof output to the main process:
      int backward_pipe[2];
      if (pipe(backward_pipe) != 0) { perror("pipe"); exit(EXIT_FAILURE); }
      pid_t backward_process = fork();
      if (backward_process < 0) { perror("fork"); exit(EXIT_FAILURE); }
      else if (backward_process)
	{
	  // a pipe to transfer forward+backward proof output to the main process:
	  int forward_backward_pipe[2];
	  if (pipe(forward_backward_pipe) != 0) { perror("pipe"); exit(EXIT_FAILURE); }
	  pid_t forward_backward_process = fork();
	  if (forward_backward_process < 0) { perror("fork"); exit(EXIT_FAILURE); }
	  else if (forward_backward_process)
	    {
	      // The father
	      close(forward_pipe[1]);
	      close(backward_pipe[1]);
	      close(forward_backward_pipe[1]);
	      int status;
	      pid_t pid;
	      while (true)
		{
		  // wait end of a proof:
		  if ((pid = wait(&status)) < 0) { cout << "DON'T KNOW" << endl; break; }
		  // if terminated proof suceeded, then terminate the other proofs:
		  if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
		    {
		      kill(forward_process, SIGINT);
		      kill(backward_process, SIGINT);
		      kill(forward_backward_process, SIGINT);
		      // wait for the end of each subprocess:
		      while (wait(NULL) > 0);
		      // print proof output:
		      char c;
		      if (pid == forward_process)
			while (read(forward_pipe[0], &c, 1) > 0) cout << c;
		      else if (pid == backward_process)
			while (read(backward_pipe[0], &c, 1) > 0) cout << c;
		      else if (pid == forward_backward_process)
			while (read(forward_backward_pipe[0], &c, 1) > 0) cout << c;
		      else { cerr << "Unknown son" << endl; exit(EXIT_FAILURE); }
		      break;
		    }
		}
	    }
	  else
	    {
	      // Prove forwards+backwards
	      close(forward_pipe[0]); close(forward_pipe[1]);
	      close(backward_pipe[0]); close(backward_pipe[1]);
	      close(forward_backward_pipe[0]);
	      if (prove(true,true,elim,var))
		if (write(forward_backward_pipe[1],
			  proof.str().c_str(),
			  proof.str().length()) != (int)proof.str().length())
		  { perror("write"); exit(EXIT_FAILURE); }
		else exit(EXIT_SUCCESS);
	      else exit(EXIT_FAILURE);
	    }
	}
      else
	{
	  // Prove backwards
	  close(forward_pipe[0]); close(forward_pipe[1]);
	  close(backward_pipe[0]);
	  if (prove(false,true,elim,var))
	    if (write(backward_pipe[1],
		      proof.str().c_str(),
		      proof.str().length()) != (int)proof.str().length())
	      { perror("write"); exit(EXIT_FAILURE); }
	    else exit(EXIT_SUCCESS);
	  else exit(EXIT_FAILURE);
	}
    }
  else
    {
      // Prove forwards:
      close(forward_pipe[0]);
      if (prove(true,false,elim,var))
	if (write(forward_pipe[1],
		  proof.str().c_str(),
		  proof.str().length()) != (int)proof.str().length())
	  { perror("write"); exit(EXIT_FAILURE); }
	else exit(EXIT_SUCCESS);
      else exit(EXIT_FAILURE);
    }
}

bool TRS::prove( bool forw, bool backw, bool elim, bool var )
{
  forwards  = forw;
  backwards = backw;

  bool proved = false;
  Program X, Unf;
  RuleSet H;
  int i, k;
  go_on = true;

  for (k = 0; go_on; k++)
    {
      //cout << "** k = " << k << endl;

      go_on = false;
      i = 0;
      nb_generated_rules = 0;
      proved = elim_R(X, H, k, elim);
      //cout << "   i = 0 -- " << endl << X << endl;
      //cout << "   i = 0 -- " << X.size() << " rule(s)" << endl;
      if (!proved && X.size() > 0)
	for (i = 1; true; i++)
	  {
	    proved = EU_R(X, Unf, H, i, k, elim, var);
	    //cout << "   i = " << i << endl << Unf << endl;
	    //cout << "   i = " << i << " -- " << Unf.size() << " rule(s)" << endl;
	    if (Unf.size() == 0 || proved) break;
	    X.merge(Unf);
	  }

      list<Rule*>::iterator it;
      for (it = garbage.begin(); it != garbage.end(); it++) delete *it;
      garbage.clear();
      H.clear();
      if (proved) break;
    }

  if (proved)
    {
      proof << endl << "Termination disproved by the ";
      if (forwards && backwards) proof << "forward+backward";
      else if (forwards) proof << "forward";
      else proof << "backward";
      proof << " process" << endl
	    << "proof stopped at iteration i=" << i
	    << ", depth k=" << k << endl
	    << nb_generated_rules << " rule(s) generated" << endl;
    }
  else
    proof << "DON'T KNOW" << endl
	  << nb_generated_rules << " rule(s) generated" << endl;

  return proved;
}



/* --------------- Input/Output: --------------- */

void TRS::display_if_killed( ostream& out ) const
{
  if (forwards && backwards)
    out << "forward+backward process killed -- "
	<< nb_generated_rules << " rule(s) generated" << endl;
  else if (forwards)
    out << "forward process killed -- "
	<< nb_generated_rules << " rule(s) generated" << endl;
  else if (backwards)
    out << "backward process killed -- "
	<< nb_generated_rules << " rule(s) generated" << endl;
  //else ERROR("void TRS::display_if_killed(ostream&) const","unknown direction");
}

void TRS::display_graph_forward( ostream& out, const Symbtab& symbtab ) const
{ graph_forward->display(out, symbtab); }

void TRS::display_graph_backward( ostream& out, const Symbtab& symbtab ) const
{ graph_backward->display(out, symbtab); }
