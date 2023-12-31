#include "ast.h"

char **find_path(char **envp)
{
    int     i;
    char    *envp_line;
    char    **answer;

    i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) != NULL)
		{
			envp_line = ft_strdup_size(envp[i], ft_strlen(envp[i]) - 5, 5);
			answer = ft_split(envp_line, ':');
			free(envp_line);
			return (answer);
		}
		i++;
	}
	return (NULL);
}

char *find_file(char **path_list, char *command)
{
    int     i;
    char    *temp;
    char    *path;
    
    i = 0;
    while (path_list[i])
    {
        temp = ft_strjoin(path_list[i], "/");
        path = ft_strjoin(temp, command);
        free(temp);
        if (access(path, X_OK) == 0)
            return (path);
        free(path);
        i++;
    }
    //error message
    exit(1);
}

char **get_command_list(t_cmd *cmd)
{
    t_suff  *suffix;
    t_word  *word;
    char    **answer;
    int     i;

    suffix = cmd->suffix;
    answer = (char **)malloc(sizeof(char *) * (cmd->w_size + 2));
    answer[0] = cmd->name->text;
    i = 1;
    while (suffix != NULL)
    {
        if (suffix->type == 2)
        {
            word = suffix->word;
            answer[i] = word->text;
            i += 1;
        }
        suffix = suffix->next;
    }
    answer[i] = NULL;
    return (answer);
}

void redirect_exe()
{

}

void	free_char_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
    free(list);
}

void	print_char_list(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		printf("%s\n",list[i]);
		i++;
	}
	free(list);
}

pid_t cmd_exe(void *list, char **envp)
{
    t_cmd   *cmd;
    pid_t   pid;
    char    **cmd_list;
    char    **path_list;
    int     outfile;

    outfile = 1; //임시
    cmd = (t_cmd *)list;
    cmd_list = get_command_list(cmd);
    path_list = find_path(envp);
    pid = NULL;
    printf("cmd: %s\n", cmd_list[0]);
    if (ft_strcmp(cmd_list[0], "echo") == 0)
        bi_echo(cmd_list, outfile);
    else if (ft_strcmp(cmd_list[0], "cd") == 0)
        bi_cd(cmd_list, outfile);
    else if (ft_strcmp(cmd_list[0], "pwd") == 0)
        bi_pwd(cmd_list, outfile);
    else if (ft_strcmp(cmd_list[0], "export") == 0)
        bi_export(envp, cmd_list, outfile);
    else if (ft_strcmp(cmd_list[0], "unset") == 0)
        bi_unset(envp, cmd_list, outfile);
    else if (ft_strcmp(cmd_list[0], "env") == 0)
        bi_env(envp, cmd_list, outfile);
    else
    {    
        pid = fork();
        if (pid < 0)
            exit(1);
        if (pid == 0)
        {
            if (execve(find_file(path_list, cmd_list[0]), cmd_list, envp) == -1)
                exit(1);
        }
    }
    free_char_list(cmd_list);
    free_char_list(path_list);
    return (pid);
}

void exe(void *list, int type, char **envp)
{
    int     status;
    pid_t      pid;

    if (type == 0)
    {
        //cmd
        pid = cmd_exe(list, envp);
        if (pid != NULL)
            waitpid(pid, &status, 0);
    }
    else if (type == 1)
    {
        //pipeline
    }
}

/*
int	main(int argc, char **argv, char **envp)
{
	char	*temp;
	t_cmd	*parsed;
    
    argc = 1;
    argv = NULL;
	parsed = (t_cmd *)malloc(sizeof(t_cmd));
	parsed->w_size = 1;
	parsed->r_size = 0;
	parsed->name = (t_word *)malloc(sizeof(t_word));
	parsed->name->text = "echo";
	parsed->suffix = (t_suff *)malloc(sizeof(t_suff));
	parsed->suffix->type = WORD;
	parsed->suffix->prev = NULL;
    parsed->suffix->redi = NULL;
	parsed->suffix->word = (t_word *)malloc(sizeof(t_word));
	parsed->suffix->word->text = "hello";
	parsed->suffix->next = NULL;

	while (true)
	{
		temp = readline("jsh> ");
		exe((void *)parsed, CMD, envp);
		//free(temp);
	}
	return (EXIT_SUCCESS);
}
*/