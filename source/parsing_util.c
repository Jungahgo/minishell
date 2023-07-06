#include "ast.h"

t_suff	*suffix_in_quote(t_cmd *cmd, char *in)
{
	t_suff	*suff;
	char	*temp;

	if (in[0] == '\'')
	{
		remove_quote(in);
		suff = new_suff(WORD, in, NULL, NULL);
		cmd->w_size++;
	}
	else if (in[0] == '\"')
	{
		remove_quote(in);
		temp = in;
		in = getenv(&temp[1]);
		free(temp);
		suff = new_suff(WORD, in, NULL, NULL);
	}
	return (suff);
}

void	remove_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		s[i] = s[i + 1];
		i++;
	}
	if (i != 0 && !s[i])
		s[i - 2] = s[i];
}
