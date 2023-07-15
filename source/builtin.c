# include "ast.h"

void bi_echo(char **cmd_list, int outfile)
{
    int i;

    i = 1;
    //-n option 아직 생각안함
    while (cmd_list[i])
    {
        write(outfile, cmd_list[i], ft_strlen(cmd_list[i]));
        i += 1;
    }
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

void bi_export(char **envp, char **cmd_list, int outfile)
{
    
}

void bi_unset(char **cmd_list, int outfile)
{

}

void bi_env(char **cmd_list, int outfile)
{
    char *env;

    env = getenv(cmd_list[1]);
    if (env == NULL)
    {
        //환경변수 없는 경우
    }
    else
        //execve
        //write(outfile, env, ft_strlen(env));
}

void bi_exit(char **cmd_list, int outfile)
{

}