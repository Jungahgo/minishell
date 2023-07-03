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
    answer[cmd->w_size + 1] = NULL;
    i = 1;
    while (suffix == NULL)
    {
        if (suffix->type == 2)
        {
            word = (t_word *)suffix->now;
            answer[i] = word->text;
            i += 1;
        }
        suffix = suffix->next;
    }
    return (answer);
}

void cmd_exe(void *list, char **envp)
{
    t_cmd   *cmd;
    char    **command;
    char    **path_list;

    cmd = (t_cmd *)list;
    command = get_command_list(cmd);
    path_list = find_path(envp);
    if (execve(find_file(path_list, command[0]), command, envp) == -1)
         exit(1);
}

void exe(void *list, int type, char **envp)
{
    if (type == 0)
    {
        //cmd
        cmd_exe(list, envp);
    }
    else if (type == 1)
    {
        //pipeline
    }
}