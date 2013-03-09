#!/bin/bash

EXECFILE=../kry
TESTINPUTS=inputs/*.txt
DEBUG=time #valgrind
DEBUGOPTS=-p

	for i in $TESTINPUTS; do
			echo "=== $i ===";
			$DEBUG $DEBUGOPTS $EXECFILE < $i;
			echo;
	done
