#!/usr/bin/bash

INFECHO_PID="$(pidof inf_echo.x)";
SEARCH_STR="hello, world!";
REPLACE_STR="bye, friends!";

if [[ -v INFECHO_PID ]];
then
	echo pid found: $INFECHO_PID;
	./read_write_heap.py $INFECHO_PID "$SEARCH_STR" "$REPLACE_STR" 2>1;
else
	echo no such process currently running;
fi

