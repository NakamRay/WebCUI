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


// the lhs is more general than the rhs
Tree* match_test ( Tree*, Tree*, Substitution*& );

// the lhs is more general than a subterm of the rhs
Tree* deep_match_test ( Tree*, Tree*, Substitution*&, Position& );

// the lhs unifies with the rhs
Tree* unify_test ( Tree*, Tree*, Substitution*& );

// the lhs unifies with a subterm of the rhs
Tree* deep_unify_test  ( Tree*, Tree*, Substitution*&, Position& );

// the lhs is more general than or unifies with the rhs
Tree* unify_or_match_test  ( Tree*, Tree*, Substitution*& );

// the lhs is more general than or unifies with a subterm of the rhs
Tree* deep_unify_or_match_test  ( Tree*, Tree*, Substitution*&, Position& );
