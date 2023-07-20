CC = cc
CPPFLAGS = -Wall -Wextra -Werror -lreadline
NAME = minishell
HEADER = ast.h
MAKE = make
OBJS = $(SRCS:.c=.o)
SRCS = 

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