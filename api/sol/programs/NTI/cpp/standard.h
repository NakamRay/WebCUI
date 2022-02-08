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


bool  more_general      ( Tree*, Tree*, Substitution*& );
bool  more_general      ( Tree*, Tree* );
bool  variant           ( Tree*, Tree* );
bool  tau_more_general  ( Tree*, Tree*, Sop*, Substitution*& );
bool  tau_more_general  ( Tree*, Tree*, Sop* );
bool  unify             ( Tree*, Tree*, Substitution*& );
bool  unify             ( Tree*, Tree* );
