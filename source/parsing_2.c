#include "ast.h"

void	make_suffix(t_cmd *cmd, int idx, char **in)
{
	t_suff	*cur;

	cur = cmd->suffix;
	while (in[idx] && ft_strcmp("|", in[idx]))
	{
		if (in[idx][0] == '\'' || in[idx][0] == '\"')
			cur->next = suffix_in_quote(cmd, &in[idx]);
		else if (is_redirection(in[idx]))
		{
			cur->next = new_suff(REDI, NULL, in[idx], in[idx + 1]);
			cmd->r_size++;
			idx++;
		}
		else
		{
			cur->next = new_suff(WORD, in[idx], NULL, NULL);
			cmd->w_size++;
		}
		cur->next->prev = cur;
		cur = cur->next;
		idx++;
	}
}

int	is_redirection(char *s)
{
	if (ft_strcmp(s, "<") == 0)
		return (true);
	else if (ft_strcmp(s, "<<") == 0)
		return (true);
	else if (ft_strcmp(s, ">") == 0)
		return (true);
	else if (ft_strcmp(s, ">>") == 0)
		return (true);
	return (false);
}

t_suff	*suffix_in_quote(t_cmd *cmd, char **in)
{
	t_suff	*suff;
	char	flag;

	flag = (*in)[0];
	remove_quote(*in);
	change_escape(*in, 0, 0);
	if (flag == '\"')
		replace_env(in, 0, 0);
	suff = new_suff(WORD, *in, NULL, NULL);
	cmd->w_size++;
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
