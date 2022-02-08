# Copyright 2008 Etienne Payet <etienne.payet@univ-reunion.fr>
#
# This file is part of NTI.
#
# NTI is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published
# by the Free Software Foundation, version 3 of the License or
# any later version.
#
# NTI is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with NTI. If not, see <http://www.gnu.org/licenses/>.

CC      = g++
CFLAGS  = -g -Wall
OBJ     = global.o symbtab.o tree.o substitution.o standard.o \
	rule.o program.o parser.o \
	ruleset.o parserXML.o parserTRS.o parserSRS.o unfoldedRule.o TRS.o \
	criteria.o descendantSet.o prologList.o parserLP.o \
	ruleLP.o programLP.o sop.o mode.o dict.o


nti: $(OBJ) main.o
	$(CC) $(CFLAGS) $(OBJ) main.o -o nti

main.o: cpp/main.cpp
	$(CC) $(CFLAGS) -c cpp/main.cpp

clean:
	rm *.o

## COMMON:
global.o: cpp/global.h cpp/global.cpp
	$(CC) $(CFLAGS) -c cpp/global.cpp
symbtab.o: cpp/symbtab.h cpp/symbtab.cpp
	$(CC) $(CFLAGS) -c cpp/symbtab.cpp
tree.o: cpp/tree.h cpp/tree.cpp
	$(CC) $(CFLAGS) -c cpp/tree.cpp
substitution.o: cpp/substitution.h cpp/substitution.cpp
	$(CC) $(CFLAGS) -c cpp/substitution.cpp
standard.o: cpp/standard.h cpp/standard.cpp
	$(CC) $(CFLAGS) -c cpp/standard.cpp
rule.o: cpp/rule.h cpp/rule.cpp
	$(CC) $(CFLAGS) -c cpp/rule.cpp
program.o: cpp/program.h cpp/program.cpp
	$(CC) $(CFLAGS) -c cpp/program.cpp
parser.o: cpp/parser.h cpp/parser.cpp
	$(CC) $(CFLAGS) -c cpp/parser.cpp

## TRS + SRS:
ruleset.o: cpp/TRS/ruleset.h cpp/TRS/ruleset.cpp
	$(CC) $(CFLAGS) -c cpp/TRS/ruleset.cpp
parserXML.o: cpp/TRS/parserXML.h cpp/TRS/parserXML.cpp
	$(CC) $(CFLAGS) -c cpp/TRS/parserXML.cpp
parserTRS.o: cpp/TRS/parserTRS.h cpp/TRS/parserTRS.cpp
	$(CC) $(CFLAGS) -c cpp/TRS/parserTRS.cpp
parserSRS.o: cpp/TRS/parserSRS.h cpp/TRS/parserSRS.cpp
	$(CC) $(CFLAGS) -c cpp/TRS/parserSRS.cpp
unfoldedRule.o: cpp/TRS/unfoldedRule.h cpp/TRS/unfoldedRule.cpp
	$(CC) $(CFLAGS) -c cpp/TRS/unfoldedRule.cpp
TRS.o: cpp/TRS/TRS.h cpp/TRS/TRS.cpp
	$(CC) $(CFLAGS) -c cpp/TRS/TRS.cpp
criteria.o: cpp/TRS/criteria.h cpp/TRS/criteria.cpp
	$(CC) $(CFLAGS) -c cpp/TRS/criteria.cpp
descendantSet.o: cpp/TRS/descendantSet.h cpp/TRS/descendantSet.cpp
	$(CC) $(CFLAGS) -c cpp/TRS/descendantSet.cpp

## LP:
prologList.o: cpp/LP/prologList.h cpp/LP/prologList.cpp
	$(CC) $(CFLAGS) -c cpp/LP/prologList.cpp
parserLP.o: cpp/LP/parserLP.h cpp/LP/parserLP.cpp
	$(CC) $(CFLAGS) -c cpp/LP/parserLP.cpp
ruleLP.o: cpp/LP/ruleLP.h cpp/LP/ruleLP.cpp
	$(CC) $(CFLAGS) -c cpp/LP/ruleLP.cpp
programLP.o: cpp/LP/programLP.h cpp/LP/programLP.cpp
	$(CC) $(CFLAGS) -c cpp/LP/programLP.cpp
sop.o: cpp/LP/sop.h cpp/LP/sop.cpp
	$(CC) $(CFLAGS) -c cpp/LP/sop.cpp
mode.o: cpp/LP/mode.h cpp/LP/mode.cpp
	$(CC) $(CFLAGS) -c cpp/LP/mode.cpp
dict.o: cpp/LP/dict.h cpp/LP/dict.cpp
	$(CC) $(CFLAGS) -c cpp/LP/dict.cpp
