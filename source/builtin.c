# include "ast.h"

void bi_echo(char **cmd_list, int outfile)
{
    int i;
    int newline;

    i = 1;
    if (cmd_list[i] == "n")
    {
        i += 1;
        newline = 0;
    }
    else
        new_line = 1;
    //-n option 아직 생각안함
    while (cmd_list[i] != NULL)
    {
        write(outfile, cmd_list[i], ft_strlen(cmd_list[i]));
        i += 1;
    }
    if (newline == 1)
        write(outfile, "\n", 1);
}

void bi_cd(char **cmd_list, int outfile)
{
    DIR *dir;

    dir = opendir(cmd_list[1]);
    if (dir == NULL)
    {
        //[error] 존재하지 않는 디렉토리
        exit(-1);
    }
    if (chdir(cmd_list[1]))
    {
        //[error] 디렉토리 변경 에러
        exit(-1);
    }
}

void bi_pwd(char **cmd_list, int outfile)
{
    char buf[BUFFER_SIZE];
    
    getcwd(buf, BUFFER_SIZE);
    write(outfile, buf, BUFFER_SIZE);
}

char **bi_export(char **envp, char **cmd_list, int outfile)
{
    int     i;

    if (cmd_list[1] == NULL)
        print_char_list(envp);
    else
    {
        i = 1;
        while (cmd_list[i])
        {
            envp = append_char_list(envp, cmd_list[i]);
            i += 1;
        }
    }
    return (envp);
}

char **bi_unset(char **envp, char **cmd_list, int outfile)
{
    int i;

    i = 1;
    while (cmd_list[i])
    {
        envp = delete_char_list(envp, cmd_list[i]);
        i += 1;
    }
    return (envp);
}

void bi_env(char **cmd_list, int outfile)
{
    char *env;

    env = getenv(cmd_list[1]);
    // if (env == NULL)
    // {
    //     //환경변수 없는 경우
    // }
    // else
    //     //execve
    //     //write(outfile, env, ft_strlen(env));
}

void bi_exit(char **cmd_list, int outfile)
{

}