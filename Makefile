CC = cc
CPPFLAGS = -Wall -Wextra -Werror
NAME = minishell
HEADER = ../ast.h
MAKE = make
OBJS = $(SRCS:.c=.o)
SRCS = source/exe.c source/utils.c source/ast_utils.c source/parsing_util.c source/parsing.c \
		source/split.c source/main.c

all : $(NAME)

$(NAME) : $(OBJS) $(HEADER)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME) -lreadline

%.o : %.c
	$(CC) $(CPPFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PONY = all clean fclean re