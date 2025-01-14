CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
GDB_FLAGS= -g -ggdb3
GCC_CMD = $(CC) $(CFLAGS) $(GDB_FLAGS)
TASK0 = laps.c 
TASK1 = _getline.c
TASK2 = _getline.c

.DELETE_ON_ERROR:

.PHONY: all clean oclean fclean force

all:
	@echo "-------- specify a task# to compile --------"

task0: $(TASK0)
	$(CC) $(CFLAGS) $(TASK0) $(TASK0:%.c=test-0_%.c) -o task0.exec

task1: $(TASK1)
	$(GCC_CMD) $(TASK1) $(TASK1:%.c=test-1_%.c) -o task1.exec

task2: $(TASK2)
	$(GCC_CMD) $(TASK2) $(TASK2:%.c=test-2_%.c) -o task2.exec

force: oclean all

fclean: clean oclean

clean:
	$(RM) *~ *.exec

oclean:
	$(RM) *.o
