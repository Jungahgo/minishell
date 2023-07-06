#include "../ast.h"

void	*parsing_input(int type, char **in, char **env)
{
	void	*res;

	if (type == CMD)
		res = (void *)make_cmd(in, env);
	//else
	//	res = (void *)make_pline(in, env);
	return (res);
}

t_cmd	*make_cmd(char **in, char **env)
{
	t_cmd	*res;
	int		idx;

	res = new_cmd();
	res->name = new_word(in[0]);
	idx = 1;
	if (in[1])
	{
		if (in[1][0] == '\'' || in[1][0] == '\"')
			res->suffix = suffix_in_quote(res, in[1]);
		else if (in[1][0] == '<' || in[1][0] == '>')
		{
			res->suffix = new_suff(REDI, NULL, in[idx], in[idx + 1]);
			idx++;
		}
		else
			res->suffix = new_suff(WORD, in[idx], NULL, NULL);
		if (in[idx] && in[++idx])
			make_suffix(res, idx, in);
	}
	return (res);
}

void	make_suffix(t_cmd *cmd, int idx, char **in)
{
	t_suff	*cur;

	cur = cmd->suffix;
	while (in[idx])
	{
		if (in[idx][0] == '\'' || in[idx][0] == '\"')
			cur->next = suffix_in_quote(cmd, in[idx]);
		else if (in[idx][0] == '<' || in[idx][0] == '>')
		{
			cur->next = new_suff(REDI, NULL, in[idx], in[idx + 1]);
			idx++;
		}
		else
			cur->next = new_suff(WORD, in[idx], NULL, NULL);
		cur->next->prev = cur;
		cur = cur->next;
		idx++;
	}
}
