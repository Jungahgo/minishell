#include "ast.h"

void	print_cmd(void *p);
void	print_pline(void *p);

int	main(int argc, char **argv, char **env)
{
	char	*temp;
	int		type;
	char	**input;
	void	*parsed;

	while (true)
	{
		temp = readline("jsh> ");
		input = split_input(temp);
		type = is_pipe_included(input);
		parsed = parsing_input(type, input, env);
		
		exe((void *)parsed, CMD, env);
///*
		if (type == CMD)
			print_cmd(parsed);
		else
			print_pline(parsed);
//*/
		
		free(temp);
		//free_(input)
	}
	return (EXIT_SUCCESS);
}

void	perror_n_exit(char *s, int status)
{
	perror(s);
	exit(status);
}

int	is_pipe_included(char **in)
{
	int	i;
	int	flag;

	flag = CMD;
	i = 0;
	while (in[i] && flag == CMD)
	{
		if (ft_strcmp(in[i], "|") == 0)
			flag = PLINE;
		i++;
	}
	return(flag);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1 || !s2)
		return (1);
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (us1[i] && us2[i])
	{
		if (us1[i] != us2[i])
			return (us1[i] - us2[i]);
		i++;
	}
	return (us1[i] - us2[i]);
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

void	print_pline(void *p)
{
	t_cmd	*cur;

	cur = ((t_pline *)p)->now;
	while (cur)
	{
		print_cmd((void *)cur);
		cur = cur->next;
	printf("###############%p\n", cur);
	}
}