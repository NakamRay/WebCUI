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


// Constants:
#define EOS            '\0'    // End Of String
#define NONE           -10000  // General purpose
#define MAX_VAR        100     // Max index of a variable


// Standard includes:
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <list>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
using namespace std;


// A function that is used everywhere:
void ERROR( string func_name, string message );


// The main classes of the program:
class Symbtab;          // symbtab.h + symbtab.cpp
class Lexan;            // parser.h + parser.cpp
class Parser;           // parser.h + parser.cpp
class Tree;             // tree.h + tree.cpp
class Substitution;     // substitution.h + substitution.cpp
class Rule;             // rule.h + rule.cpp
class Program;          // program.h + program.cpp

class List;             // LP/prologList.h + LP/prologList.cpp
class LexanLP;          // LP/parserLP.h + LP/parserLP.cpp
class ParserLP;         // LP/parserLP.h + LP/parserLP.cpp
class RuleLP;           // LP/ruleLP.h + LP/ruleLP.cpp
class ProgramLP;        // LP/programLP.h + LP/programLP.cpp
class Sop;              // LP/sop.h + LP/sop.cpp
class Loop_pair;        // LP/dict.h + LP/dict.cpp
class Dict;             // LP/dict.h + LP/dict.cpp
class Mode;             // LP/mode.h + LP/mode.cpp
class MultiMode;        // LP/mode.h + LP/mode.cpp

class LexanXML;         // TRS/parserXML.h + TRS/parserXML.cpp
class ParserXML;        // TRS/parserXML.h + TRS/parserXML.cpp
class LexanTRS;         // TRS/parserTRS.h + TRS/parserTRS.cpp
class ParserTRS;        // TRS/parserTRS.h + TRS/parserTRS.cpp
class LexanSRS;         // TRS/parserSRS.h + TRS/parserSRS.cpp
class ParserSRS;        // TRS/parserSRS.h + TRS/parserSRS.cpp
class UnfoldedRule;     // TRS/unfoldedRule.h + TRS/unfoldedRule.cpp
class TRS;              // TRS/TRS.h + TRS/TRS.cpp
class Graph;            // TRS/TRS.h + TRS/TRS.cpp
class Option;           // TRS/TRS.h + TRS/TRS.cpp
class DescendantSet;    // TRS/descendantSet.h + TRS/descendantSet.cpp
class RuleSet;          // TRS/ruleset.h + TRS/ruleset.cpp

// Include headers for these classes:
#include "symbtab.h"
#include "parser.h"
#include "tree.h"
#include "substitution.h"
#include "standard.h"
#include "rule.h"
#include "program.h"

#include "LP/prologList.h"
#include "LP/parserLP.h"
#include "LP/sop.h"
#include "LP/mode.h"
#include "LP/ruleLP.h"
#include "LP/programLP.h"
#include "LP/dict.h"

#include "TRS/ruleset.h"
#include "TRS/parserXML.h"
#include "TRS/parserTRS.h"
#include "TRS/parserSRS.h"
#include "TRS/unfoldedRule.h"
#include "TRS/TRS.h"
#include "TRS/criteria.h"
#include "TRS/descendantSet.h"
