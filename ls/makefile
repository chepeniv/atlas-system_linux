CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
GDB_FLAGS= -g -ggdb3
GCC_CMD = $(CC) $(CFLAGS) $(GDB_FLAGS)
EXR = prototypes/ls-exr.c # prototypes/ls-exr.main.c

.DELETE_ON_ERROR:

.PHONY: all clean oclean fclean force

all:
	@echo "-------- specify a task# to compile --------"

hls: 
	$(GCC_CMD) *.c -o hls.exec

exr: $(EXR)
	$(GCC_CMD) $(EXR) -o exr-ls.exec

force: oclean all

fclean: clean oclean

clean:
	$(RM) *~ *.exec

oclean:
	$(RM) *.o
