# CUNIT     := $(shell pkg-config -cflags -libs cunit)
# CRITERION := $(shell pkg-config -cflags -libs criterion)
# I_FLAGS   := $(shell pkg-config --cflags gtk4)
# L_FLAGS   := $(shell pkg-config --libs gtk4)

CC       := gcc
GDB      := cgdb

CFLAGS   := -Wall -Werror -Wextra -pedantic
DB_FLAGS := -ggdb3
CCMD     := ${CC} ${CFLAGS} ${I_FLAGS} ${L_FLAGS} ${DB_FLAGS}

BINDIR   := build
TESTDIR  := tests
DEFDIR   := defs
HEADIR   := headers
# DEFS     := $(shell find ${DEFDIR}/*.c)

MEMTEST  := valgrind -s --track-origins=yes --leak-check=full --show-leak-kinds=all

.DELETE_ON_ERROR:

.PHONY: clean clean-obj defs

all: hnm

test: 
	@./hnm targets/* 
	@./hnm targets/no_symbols/* 

memtest: 
	${MEMTEST} ./hnm targets/elf-Haiku-GCC2-ls

hnm: clean
	${CCMD} *.c -o hnm

betty: 
	echo "running Betty coding style checks..."
	@betty-style *.c *.h
	echo "running Betty documentation checks..."
	@betty-doc *.c *.h

defs:

######## UTILITY 

clean:
	@$(RM) -v *~ *.exec *.o *.out *.x  hnm

clean-obj:
	@$(RM) -v *~ *.o 
