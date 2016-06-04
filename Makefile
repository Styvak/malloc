##
## Makefile for libmy in /home/gascon_n/rendu/Piscine_C_J11/lib/my
## 
## Made by Nicolas Gascon
## Login   <gascon_n@epitech.net>
## 
## Started on  Mon Oct 20 10:09:07 2014 Nicolas Gascon
## Last update Sun Feb 14 21:33:42 2016 Nicolas Gascon
##

SRC=	src/malloc.c \
	src/insert.c \
	src/block.c \
	src/show_alloc_mem.c \
	src/free.c \
	src/search.c \
	src/delete.c \
	src/delete_sequel.c \
	src/page.c

NAME=	libmy_malloc.so

OBJ=	$(SRC:.c=.o)

CFLAGS=	-W -Wall -Wextra -Werror -fPIC -lpthread -g

all:		$(NAME)

clean:
	rm -f $(OBJ)

$(NAME):	$(OBJ)
	g++ -o $(NAME)_$(HOSTTYPE) $(OBJ) -shared
	ln -fs $(NAME)_$(HOSTTYPE) $(NAME)

fclean:		clean
	rm -f $(NAME)
	rm -f $(NAME)_$(HOSTTYPE)

debug:	$(OBJ)
	g++ -o $(NAME)_$(HOSTTYPE) $(OBJ) -shared -ggdb
	ln -fs $(NAME)_$(HOSTTYPE) $(NAME)

re:	fclean all

redebug:	fclean debug
