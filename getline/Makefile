CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
NAME = c.exec

.DELETE_ON_ERROR:

.PHONY: all clean oclean fclean re

all: $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(SRC): %.c: %.h

re: oclean all

fclean: clean oclean

clean:
	$(RM) *~ $(NAME)

oclean:
	$(RM) $(OBJ)
