#! /usr/bin/bash

# INSTRUCTIONS
# write a 'sh' script that sends the 'SIGQUIT' signal to a process given by
# its PID
#
# usage: './signal_send.sh <pid>'
# '<pid>' will not be '0'
#
# if an incorrect number of arguments is given, print 'Usage: %s <pid>\n'
#     where '%s' is given by 'argv[0]'
#     exit with '1'

if [ $# != 1 ];
	then printf "Usage: %s <pid>\n" $0;
	exit 1;
else
	# echo "SIGQUIT"
	kill -3 $1
fi
