CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
GDB_FLAGS= -g -ggdb3
GCC_CMD = $(CC) $(CFLAGS) $(GDB_FLAGS)
TASK0 = null.c 
EXERCISE = ls-exercise.c exercise.main.c

.DELETE_ON_ERROR:

.PHONY: all clean oclean fclean force

all:
	@echo "-------- specify a task# to compile --------"

task0: $(TASK0)
	$(CC) $(CFLAGS) $(TASK0) $(TASK0:%.c=test-0_%.c) -o task0.exec

exercise: $(EXERCISE)
	$(GCC_CMD) $(EXERCISE) -o ls-exer.exec

force: oclean all

fclean: clean oclean

clean:
	$(RM) *~ *.exec

oclean:
	$(RM) *.o
