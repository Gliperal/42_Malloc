ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


CC=gcc
CFLAGS=-Wall -Wextra -Werror
OBJS=malloc.o zone.o free_list.o show_alloc_mem.o globals.o
NAME=libft_malloc.so
NAME_HOST=libft_malloc_$(HOSTTYPE).so
RM=rm -rf

vpath libft.a libft

all: $(NAME)

$(NAME): $(NAME_HOST)
	$(RM) $(NAME)
	ln -s $(NAME_HOST) $(NAME)

$(NAME_HOST): $(OBJS) -lft
	$(CC) $(CFLAGS) $(OBJS) -L libft -lft -shared -o $(NAME_HOST)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

libft/libft.a:
	make -C libft

.PHONY: all clean fclean re

clean:
	make -C libft clean
	$(RM) $(OBJS)

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)
	$(RM) $(NAME_HOST)

re: fclean all
