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


#include "global.h"



/*****************
 * Substitution: *
 *****************/

/* --------------- Constructor/Destructor: --------------- */

Substitution::Substitution( )
{
  for (int i = 0; i < SUBS_SIZE; i++) range[i] = NULL;
  nb_maps = 0;
}

Substitution::Substitution( const Substitution& sigma )
{
  for (int i = 0; i < SUBS_SIZE; i++)
    if (sigma.range[i]) range[i] = sigma.range[i]->copy();
    else range[i] = NULL;
  nb_maps = sigma.nb_maps;
}

Substitution::~Substitution( )
{
  for (int i = 0; i < SUBS_SIZE; i++)
    if (range[i]) { delete range[i]; range[i] = NULL; }
  nb_maps = 0;
}


/* --------------- Get/Set: --------------- */

void Substitution::set( Tree *X, Tree *t )
{
  if (X == NULL)
    ERROR("void Substitution::set(Tree *X,Tree *t)","X is NULL");
  if (!X->is_var())
    ERROR("void Substitution::set(Tree *X,Tree *t)","X is not a variable");
  if (t == NULL)
    ERROR("void Substitution::set(Tree *X,Tree *t)","t is NULL");

  // BEWARE: *X == *t is allowed !!

  int i = -1*X->rel();

  if (i >= SUBS_SIZE)
    ERROR("void Substitution::set(Tree *X,Tree *t)","X >= SUBS_SIZE");

  if (range[i]) delete range[i];
  range[i] = t->copy();
  nb_maps++;
}

void Substitution::clean( )
{
  for (int i = 0; i < SUBS_SIZE; i++)
    if (range[i])
      if (-1*i == range[i]->rel())
	{ delete range[i]; range[i] = NULL; nb_maps--; }
}


/* --------------- Operators: --------------- */

Substitution& Substitution::operator = ( const Substitution& sigma )
{
  if (this != &sigma)
    for (int i = 0; i < SUBS_SIZE; i++) {
      if (sigma.range[i]) range[i] = sigma.range[i]->copy();
      else range[i] = NULL;
    }
  return *this;
}

bool Substitution::operator + ( Substitution *sigma )
{
  for (int i = 0; i < SUBS_SIZE; i++)
    {
      if (sigma->range[i] == NULL) continue;
      if (range[i] == NULL)
	{
	  range[i] = sigma->range[i];
	  sigma->range[i] = NULL;
	  continue;
	}
      if (*(range[i]) != *(sigma->range[i])) return false;
    }
  return true;
}

Substitution* Substitution::operator * ( Substitution *sigma )
{
  // Apply sigma to *this:
  for (int i = 0; i < SUBS_SIZE; i++)
    if (range[i])
      {
	(*sigma)(range[i]);
	if (range[i]->rel() == -1*i) { delete range[i]; range[i] = NULL; }
      }
  // Add sigma to *this:
  for (int i = 0; i < SUBS_SIZE; i++)
    if (sigma->range[i] && range[i] == NULL)
      range[i] = sigma->range[i]->copy();
  // Return this:
  return this;
}

Tree* Substitution::operator () ( Tree *&t ) const
//Tree* Substitution::operator () ( Tree *t ) const
{
  if (t->is_var())
    {
      int i = -1*t->rel();
      if (range[i]) //*t = *(range[i]);
	{ delete t; t = range[i]->copy(); }
    }
  else for (int i = 0; i < t->arity(); i++) (*this)((*t)[i]);

  return t;
}

Tree* Substitution::operator [] ( Tree *X ) const
{
  int i = -1*X->rel();

  if (i >= SUBS_SIZE)
    ERROR("void Substitution::operator [] (Tree *X) const","X >= SUBS_SIZE");

  return range[i];
}


/* --------------- Misc: --------------- */

Substitution* Substitution::copy( ) const
{
  Substitution *sigma = new Substitution;
  for (int i = 0; i < SUBS_SIZE; i++)
    if (range[i])
      sigma->range[i] = range[i]->copy();
  return sigma;
}


/* --------------- Output: --------------- */

ostream& operator << ( ostream& out, const Substitution& sigma )
{
  bool b = false;
  out << '{';
  for (int i = 0; i < SUBS_SIZE; i++)
    if (sigma.range[i])
      {
	if (i > 0 && b) out << ", ";
	out << "_" << i << '/';
	sigma.range[i]->display(out);
	b = true;
      }
  out << '}';

  return out;
}
