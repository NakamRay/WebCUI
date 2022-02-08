#!/bin/sh
DIR=${0%/*}
PATH=$DIR:$PATH
xsltproc "$DIR/xtc2tpdb.xml" "$1" > $DIR/$1$$.trs
java -jar ./nti18.jar $1$$.trs 2> $DIR/stderr.txt
cat $DIR/stderr.txt
