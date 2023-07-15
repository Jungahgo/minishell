#include "../ast.h"

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
		// 파싱 끝 명령어 시작
		
		exe((void *)parsed, CMD, env);

		print_cmd(parsed);
		
		free(temp);
		free(input);
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
