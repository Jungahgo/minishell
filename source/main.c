#include "ast.h"

void	print_cmd(void *p);

int	main(int argc, char **argv, char **env)
{
	char	*temp;
	int		type;
	char	**input;
	void	*parsed;

	while (true)
	{
		temp = readline("jsh> ");
		type = CMD;
		//type = is_pipe_included(temp);
		input = split_input(temp);
		parsed = parsing_input(type, input, env);
		
		//run(TYPE, parsed);

		print_cmd(parsed);
		
		free(temp);
		//free_(input)
	}
	return (EXIT_SUCCESS);
}

void	perror_n_exit(char *s, int status)
{
	perror("s");
	exit(status);
}

int	is_pipe_included(char *in)
{
	int	i;
	int	flag;

	flag = CMD;
	i = 0;
	while (in[i] && flag != CMD)
	{
		if (in[i] == '|')
			flag = PLINE;
		i++;
	}
	return(flag);
}

void	print_cmd(void *p)
{
	t_suff	*cur;

	printf("cmd w_size : %d\n", ((t_cmd *)p)->w_size);
	printf("cmd r_size : %d\n", ((t_cmd *)p)->r_size);
	printf("cmd name : %s\n", ((t_cmd *)p)->name->text);
	printf("cmd suffix : %p\n", ((t_cmd *)p)->suffix);
	cur = ((t_cmd *)p)->suffix;
	while (cur)
	{
		printf("cmd suffix type : %d\n", cur->type);
		if (cur->type == WORD)
			printf("cmd suffix word : %s\n", cur->word->text);
		else
		{
			printf("cmd suffix redi op : %s\n", cur->redi->op);
			printf("cmd suffix redi file : %s\n", cur->redi->file);
		}
		printf("cmd suffix prev : %p\n", cur->prev);
		printf("cmd suffix next : %p\n", cur->next);
		cur =cur->next;
	}
}