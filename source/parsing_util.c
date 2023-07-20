#include "ast.h"

void	change_escape(char *s, int i, int j)
{
	i = 0;
	while (s[i])
	{
		if (s[i] == '\\')
		{
			if (change_escape_util(s[i + 1], &s[i]))
			{
				i++;
				j = i;
				while (s[j])
				{
					s[j] = s[j + 1];
					j++;
				}
				i--;
			}
		}
		i++;
	}
}

int	change_escape_util(char src, char *idx)
{
	char	ori;

	ori = *idx;
	if (src == '\\')
		*idx = '\\';
	else if (src == 't')
		*idx = '\t';
	else if (src == 'n')
		*idx = '\n';
	else if (src == '0')
		*idx = '\0';
	else if (src == '"')
		*idx = '\"';
	else if (src == '\'')
		*idx = '\'';
	return (!(ori == *idx));
}

int	is_possible_to_env(char c)
{
	if ('A' <= c && 'Z' >= c)
		return (true);
	if ('a' <= c && 'z' >= c)
		return (true);
	if ('0' <= c && '9' >= c)
		return (true);
	if ('_' == c)
		return (true);
	return (false);
}

void	replace_env(char **in, int ii, int len)
{
	char	*join;
	char	*sub;
	char	*temp;
	char	flag;

	join = ft_strdup("");
	while ((*in)[ii])
	{
		len = 0;
		flag = (*in)[ii];
		count_cut_point(flag, in, &ii, &len);
		sub = ft_substr(*in, ii, len);
		temp = sub;
		if (flag == '$' && is_possible_to_env((*in)[ii + 1]))
			sub = getenv(temp);
		join = ft_strjoin(join, sub);
		ii = ii + len - 1;
		if ((*in)[ii])
			ii++;
	}
	*in = join;
}

void	count_cut_point(char flag, char **in, int *ii, int *len)
{
	if (flag == '$' && (*in)[*ii + 1] && is_possible_to_env((*in)[*ii + 1]))
	{
		*ii = *ii + 1;
		while ((*in)[*ii + *len] && is_possible_to_env((*in)[*ii + *len]))
			*len = *len + 1;
	}
	else
	{
		if (flag == '$' && (*in)[*ii + *len])
			*len = *len + 1;
		while ((*in)[*ii + *len] && (*in)[*ii + *len] != '$')
			*len = *len + 1;
	}
}