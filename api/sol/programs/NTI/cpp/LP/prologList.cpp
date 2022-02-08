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


/**************
 * Class List *
 **************/


/* --------------- Constructors/Destructor: --------------- */

List::List( ): Tree()
{ root = LISTSYMB; }

List::List( int var ): Tree(var,0)
{
  if (var >= 0)
    ERROR("List::List(int var)", "var is >= 0");
}


/* --------------- Operators: --------------- */

List& List::operator = ( const List& l )
{
  if (this != &l)
    {
      root    = l.root;
      nb_args = l.nb_args;
      if (args) delete [] args;
      if (nb_args == 0) args = NULL;
      else
	{
	  args = new Tree*[2];
	  args[0] = new Tree();
	  *(args[0]) = *(l.args[0]);
	  args[1] = new List();
	  *(args[1]) = *(l.args[1]);
	}
    }
  return *this;
}


/* --------------- Get/Set: --------------- */

void List::push_front( Tree* first )
{
  Tree **new_args = new Tree*[2];
  new_args[0] = first;
  if (is_var()) new_args[1] = new List(root);
  else
    {
      List *l = new List();
      l->nb_args = nb_args;
      l->args = args;
      new_args[1] = l;
   }

  root = LISTSYMB;
  nb_args = 2;
  args = new_args;
}


/* --------------- Misc: --------------- */

Tree* List::copy( ) const
{
  if (is_var()) return new List(root);

  List *l = new List();
  l->nb_args = nb_args;
  if (args)
    {
      l->args = new Tree*[nb_args];
      for (int i = 0; i < nb_args; i++)
	if (args[i] == NULL) (l->args)[i] = NULL;
	else (l->args)[i] = (args[i])->copy();
    }

  return l;
}


/* --------------- Input/Output: --------------- */

void List::display_args( ostream& out ) const
{
  if (args)
    {
      if (args[0]) args[0]->display(out);
      else out << "NULL";

      if (args[1])
	{
	  if (args[1]->is_var()) { out << '|'; args[1]->display(out); }
	  else
	    {
	      if (args[1]->arity() > 0) out << ',';
	      args[1]->display_args(out);
	    }
	}
      else out << "NULL";
    }
}

void List::display( ostream& out ) const
{
  if (is_var()) Tree::display(out);
  else
    {
      out << '[';
      display_args(out);
      out << ']';
    }
}
