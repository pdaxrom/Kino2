#!/bin/sh

TOP=`pwd`

DIRS=". libid3tag libmad"

rm -f ltconfig 

for i in ${DIRS}; do 
	cd ${i};
	rm -f acinclude.m4;
	aclocal;
 	libtoolize --force --copy;
	autoheader;
	automake --foreign --copy;
	autoconf;
	cd ${TOP};
done
