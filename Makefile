CC = CC
CPPFLAGS = -Wall -Wextra -Werror
NAME = minishell
HEADER = ast.h

OBJS = $(SRCS:.c=.o)
SRCS = exe.c utils.c

.PONY = all
all : $(NAME)

$(NAME) : $(OBJS)

.PONY = clean
clean :
	rm -f $(OBJS)

.PONY = fclean
fclean : clean
	rm -f $(NAME)

.PONY = re
re :
	$(MAKE) fclean
	$(MAKE) all