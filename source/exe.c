#include "../ast.h"

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
    if (command == NULL)
		return (NULL);
	if (access(command, X_OK) == 0)
		return (command);
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
    while (suffix)
    {
        if (suffix->type == WORD)
        {
            word = suffix->word;
            answer[i] = word->text;
            i += 1;
        }
        suffix = suffix->next;
    }
    return (answer);
}

pid_t cmd_exe(void *list, char **envp)
{
    t_cmd   *cmd;
    char    **cmd_list;
    char    **path_list;
    pid_t   pid;

    cmd = (t_cmd *)list;
    cmd_list = get_command_list(cmd);
    path_list = find_path(envp);
    pid = fork();
    if (pid < 0)
        // error message
        exit(1);
    if (pid == 0)
    {
        printf("pid == 0\n");
        if (execve(find_file(path_list, cmd_list[0]), cmd_list, envp) == -1)
            exit(1);
    }
    free_char_list(cmd_list);
    free_char_list(path_list);
    return (pid);
}

void	close_all_pipe(int fd[][2])
{
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
}

pid_t	pipe_exe(void *tree, char **envp, int fd[][2], int size)
{
	t_cmd	*now;
	char	**path_list;
	char	**cmd_list;
	pid_t	pid;

	now = (t_cmd *)tree;
	path_list = find_path(envp);
	cmd_list = get_command_list(now);
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		if (now -> index == 0)
		{
			close(fd[0][0]);
			close(fd[1][0]);
			close(fd[1][1]);
			dup2(fd[0][1], STDOUT_FILENO);
		}
		else if (now -> index == size - 1)
		{
			close(fd[0][0]);
			close(fd[0][1]);
			close(fd[1][1]);
			dup2(fd[1][0], STDIN_FILENO);
		}
		else
		{
			close(fd[0][1]);
			close(fd[1][0]);
			dup2(fd[0][0], STDIN_FILENO);
			dup2(fd[1][1], STDOUT_FILENO);
		}
		if (execve(find_file(path_list, cmd_list[0]), cmd_list, envp) == -1)
            exit(1);
	}
	close_all_pipe(fd);
	return pid;
}

void exe(void *tree, int type, char **envp)
{
    pid_t   *pid;
    int     status;
	int		fd[2][2];
	int		i;

    if (type == 0)
    {
        //cmd
        *pid = cmd_exe(tree, envp);
        waitpid(*pid, &status, 0);
    }
    else if (type == 1)
    {
		pid = malloc(sizeof(pid_t) * (((t_pline *)tree) -> size));
		i = -1;
        // pipeline
		pipe(fd[0]);
		pipe(fd[1]);
		// pid 받아서 명령어 실행하기
		while (++i < ((t_pline *)tree) -> size)
		{
			pid[i] = pipe_exe(((t_pline *)tree) -> now, envp, fd, ((t_pline *)tree) -> size);
			((t_pline *)tree) -> now = ((t_pline *)tree) -> now -> next;
		}
		// waitpid 하기
		i = -1;
		while (++i < ((t_pline *)tree) -> size)
			waitpid(pid[i], &status, 0);
		free(pid);
    }
}

int main(int ac, char *argv[], char *envp[])
{
	//파싱부가 어느정도 파이프에 대해 완료되면 진행
	exe(tree, PLINE, envp);
}
