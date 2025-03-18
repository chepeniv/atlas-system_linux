#!/usr/bin/bash

# INSTRUCTIONS:
#
# write a shell script that sets a handler for the  signals 'SIGABRT', 'SIGIO',
# and 'SIGTERM'
#
# print 'Nope\n' each time  'SIGABRT', 'SIGIO', and 'SIGTERM' is caught
# no more than two lines in the script
# no more than one instruction per line

trap "echo Nope" abrt io term

while (true);
	do echo hello; sleep 1;
done
