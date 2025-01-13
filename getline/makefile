CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -ggdb3
TASK0 = laps.c 
TASK1 = _getline.c
TASK2 = _getline.c

.DELETE_ON_ERROR:

.PHONY: all clean oclean fclean force

all:
	@echo "-------- specify a task# to compile --------"

task0: $(TASK0)
	$(CC) $(CFLAGS) $(TASK0) $(TASK0:%.c=test-0_%.c) -o $(TASK0:.c=.exec)

task1: $(TASK1)
	$(CC) $(CFLAGS) $(TASK1) $(TASK1:%.c=test-1_%.c) -o $(TASK1:.c=.exec)

task2: $(TASK2)
	$(CC) $(CFLAGS) $(TASK2) $(TASK2:%.c=test-2_%.c) -o $(TASK2:.c=.exec)

force: oclean all

fclean: clean oclean

clean:
	$(RM) *~ *.exec

oclean:
	$(RM) *.o
