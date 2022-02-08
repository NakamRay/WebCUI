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


/*********************
 *  Logic Programs:  *
 *********************/
class ProgramLP: public Program
{
 private:
  Tree* query; // The mode whose non-termination is to be proved.
  void  rec_add_bot  ( Rule*, int, int, const Substitution&,
		       Program&, Program& ) const;

 public:
   // Constructors/Destructor:
  ProgramLP          ( ) { query = NULL; };
  ~ProgramLP         ( ) { if (query) delete query; };
  // Get/Set:
  Tree* get_query    ( ) { return query; };
  void  set_query    ( Tree *t ) { query = t; };
  // Bottom-up unfoldings:
  void  T_P_beta     ( Program& X, Program& new_X ) const;
  // Non-termination inference:
  void  prove        ( void* );
};
