#include "ast.h"

void	*parsing_input(int type, char **in, char **env)
{
	void	*res;
	int		idx;

	idx = 0;
	while (in[idx])
		replace_env(&(in[idx++]), 0, 0);
	if (type == CMD)
		res = (void *)make_cmd(in, env, 0);
	else
		res = (void *)make_pline(in, env);
	return (res);
}

t_cmd	*make_cmd(char **in, char **env, int num)
{
	t_cmd	*res;
	int		idx;

	res = new_cmd();
	res->name = new_word(in[num]);
	idx = num + 1;
	if (in[idx] && ft_strcmp("|", in[idx]))
	{
		if (in[idx][0] == '\'' || in[idx][0] == '\"')
			res->suffix = suffix_in_quote(res, &in[idx]);
		else if (is_redirection(in[idx]))
		{
			res->suffix = new_suff(REDI, NULL, in[idx], in[idx + 1]);
			res->r_size++;
			idx++;
		}
		else
		{
			res->suffix = new_suff(WORD, in[idx], NULL, NULL);
			res->w_size++;
		}
		if (in[idx] && in[++idx] && ft_strcmp("|", in[idx]))
			make_suffix(res, idx, in);
	}
	return (res);
}

t_pline	*make_pline(char **in, char **env)
{
	t_pline	*res;
	t_cmd	*cur;
	int		idx;

	res = (t_pline *)malloc(sizeof(t_pline));
	res->size = 0;
	res->now = NULL;
	idx = 0;
	res->now = make_cmd(in, env, idx++);
	cur = res->now;
	while (in[idx])
	{
		while (in[idx] && in[idx + 1] && ft_strcmp("|", in[idx]))
			idx++;
		idx++;
		if (!in[idx])
			break ;
		cur->next = make_cmd(in, env, idx++);
		cur = cur->next;
	}
	return (res);
}