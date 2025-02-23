#!/usr/bin/bash

INFECHO_PID="$(pidof inf_echo)";
SEARCH_STR="hello, world!";
REPLACE_STR="goodbye, friend!";

if [[ -v INFECHO_PID ]];
then
	echo found $INFECHO_PID;
	#./read_write_heap.py $INFECHO_PID $SEARCH_STR $REPLACE_STR
else
	echo no such process currently running;
fi

