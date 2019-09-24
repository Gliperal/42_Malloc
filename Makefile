ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif


CC=gcc
CFLAGS=-Wall -Wextra -Werror
OBJS=malloc.o
NAME=libft_malloc.so
NAME_HOST=libft_malloc_$(HOSTTYPE).so
RM=rm -rf

all: $(NAME)

$(NAME): $(NAME_HOST)
	ln -s $(NAME_HOST) $(NAME)

$(NAME_HOST): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -shared -o $(NAME_HOST)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -fPIC $< -o $@

# TODO libft

.PHONY: all clean fclean re

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(NAME_HOST)

re: fclean all
