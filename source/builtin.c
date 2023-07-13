# include "ast.h"

void echo(char **cmd_list, int outfile)
{
    int i;

    i = 1;
    while (cmd_list[i])
    {
        write(outfile, cmd_list[i], ft_strlen(cmd_list[i]));
        i += 1;
    }
    write(outfile, "\n", 1);
}