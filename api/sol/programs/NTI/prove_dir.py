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


##################################################
## A Python script to run NTI on a full directory.
## TRS and SRS files only are considered.
## Python >= 2.4 needed
##################################################

import time
import os
import sys
import subprocess              # available from Python 2.4
from   string import digits

def print_usage():
    print "Usage : prove_dir <directory> <time limit> [direction] [elim] [var]"
    print "  Non-termination analysis of the TRS's and SRS's in <directory>"
    print "  trying, in parallel, forward unfoldings only, backward unfoldings only"
    print "  and forward+backward unfoldings together."
    print "  Result is sent to standard output."
    print "  <time limit> = maximal CPU time in seconds allowed to give an answer."
    print "  [direction] (optional) can be:"
    print "  -forward : prove with forward unfoldings only"
    print "  -backward : prove with backward unfoldings only"
    print "  -both : prove with forward+backward unfoldings together"
    print "  [elim] (optional) can be:"
    print "  -noelim : do not eliminate useless unfolded rules"
    print "  [var] (optional) can be:"
    print "  -novar : do not unfold variable positions"


def nb_generated(line):
    n = ""
    for i in range(len(line)):
        if line[i] in digits: n += line[i]
        else: break
    return int(n)

def nb_generated_ctrl_C(lines, args):
    forward = backward = False
    for i in range(len(args)):
        if args[i] == "-forward":
            forward = True
            backward = False
        if args[i] == "-backward":
            forward = False
            backward = True
        if args[i] == "-both":
            forward = False
            backward = False

    for i in range(len(lines)):
        if forward and lines[i][:15] == "forward process":
            return nb_generated(lines[i][26:])
        if backward and lines[i][:16] == "backward process":
            return nb_generated(lines[i][27:])
        if lines[i][:16] == "forward+backward":
            return nb_generated(lines[i][35:])
    return 0

def iteration(line):
    n = ""
    for i in range(len(line)):
        if line[i] in digits: n += line[i]
        elif line[i] == ',': break
    return int(n)

def prove(target, args, L, L_files):
    for f in os.listdir(os.path.normpath(target)):
        ff = os.path.normpath(str(target) + r"/" + f)
        ## processing a directory:
        if (os.path.isdir(ff)):
            prove(ff, args, L, L_files)
        ## Analysing a file:
        else:
            ## if the file is a trs or srs, analyse it:
            if len(f) >= 4 and f[0] != '.' and (f[-4:] == ".xml" or f[-4:] == ".trs" or f[-4:] == ".srs"):
                L[0] += 1
                print "***", ff
                try:
                    start = time.time()
                    p = subprocess.Popen(["./nti"] + [ff] + args, stdout = subprocess.PIPE)
                    n = p.wait()
                    d = time.time() - start
                    lines = p.stdout.readlines()
                    sys.stdout.writelines(lines)
                    if n == 0:
                        L[2] += 1
                        L[3] += nb_generated(lines[len(lines)-1])
                        ite = iteration(lines[len(lines)-2])
                        L[4] += ite
                        if L[5] < 0 or L[5] > ite: L[5] = ite
                        if L[6] < ite: L[6] = ite
                    else:
                        L_files.append(ff)
                except KeyboardInterrupt:
                    #sys.stdout.write("TIME OUT\n")
                    d = time.time() - start
                    lines = p.stdout.readlines()
                    sys.stdout.writelines(lines)
                    L[3] += nb_generated_ctrl_C(lines, args)
                    L_files.append(ff)
                except:
                    d = time.time() - start
                    L_files.append(ff)
                L[1] += d
                print "*** proof time: %.2f second(s)" % d
                print

def direction(args):
    s = ""
    for i in range(len(args)):
        if args[i] == "-both":
            s = "- forward+backward unfoldings together"
        elif args[i] == "-forward":
            s = "- forward unfoldings only"
        elif args[i] == "-backward":
            s = "- backward unfoldings only"
    if s == "":
        print "- forward+backward unfoldings, forward unfoldings only,"
        print "  backward unfoldings only, all in parallel"
    else:
        print s

def elim(args):
    for i in range(len(args)):
        if args[i] == "-noelim":
            print "- useless rule elimination OFF"
            return
    print "- useless rule elimination ON"

def var_unfold(args):
    for i in range(len(args)):
        if args[i] == "-novar":
            print "- unfolding at variable positions OFF"
            return
    print "- unfolding at variable positions ON"


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print_usage()
    else:
        print "***********************************************************"
        print "Non-termination analysis of directory", sys.argv[1]
        print "- time limit = ", sys.argv[2], "second(s)"
        direction(sys.argv[3:])
        elim(sys.argv[3:])
        var_unfold(sys.argv[3:])
        print "***********************************************************"
        print
        print "[SEE BOTTOM LINES FOR OVERALL RESULTS]"
        print
        print
        target = sys.argv[1]
        L = [0,0.0,0,0,0,-1,-1]
        L_files = []
        prove(target, sys.argv[2:], L, L_files)
        print
        print
        print "***********************************************************"
        print "-- total time: %.2f second(s)" % L[1]
        print "-- %d files analysed" % L[0]
        print "-- %d successful proofs" % L[2]
        print "-- %d rules generated" % L[3]
        if L[2] > 0:
            print "-- iterations (successful proofs):",
            print "average=%d," % (L[4]/L[2]),
            print "min=%d," % L[5],
            print "max=%d" % L[6]
        if len(L_files) != 0:
            print  "-- non-termination of the following file(s) could not be proved:"
            for name in L_files: print name
        print "***********************************************************"
        print
