#include "ast.h"

int	is_sep(char n)
{
	if (n == '\"')
		return (3);
	if (n == '\'')
		return (2);
	if (n == ' ' || n == '\0')
		return (1);
	return (0);
}

int	count_word(char *s)
{
	int	i;
	int	cnt;
	int	val;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		val = is_sep(s[i]);
		if (val >= 2)
		{
			i++;
			while (s[i] && is_sep(s[i]) != val)
				i++;
		}
		if (!s[i] || (s[i] && is_sep(s[i]) != 1 && is_sep(s[i + 1]) == 1))
			cnt++;
		if (!s[i])
			break ;
		i++;
	}
	return (cnt);
}

int	get_word_len(char *s, int *idx)
{
	int	val;
	int	i;

	i = *idx;
	val = is_sep(s[i]);
	if (val >= 2)
	{
		i++;
		while (s[i + 1] && is_sep(s[i]) != val)
			i++;
		i++;
	}
	else
	{
		while (is_sep(s[i]) != 1)
			i++;
	}
	return (i - *idx);
}

char	*init_word(char *s, int *idx)
{
	char	*res;
	int		i;
	int		val;

	while (s[*idx] && is_sep(s[*idx]) == 1)
		*idx = *idx + 1;
	res = (char *)malloc(sizeof(char) * (get_word_len(s, idx) + 1));
	if (!res)
		perror_n_exit("malloc()", EXIT_FAILURE);
	i = 0;
	val = is_sep(s[*idx]);
	while ((!val && is_sep(s[*idx]) != 1) || val)
	{
		res[i] = s[*idx];
		*idx = *idx + 1;
		i++;
		if (val && i > 1 && is_sep(s[*idx - 1]) == val)
			break;
	}
	res[i] = 0;
	return (res);
}

char	**split_input(char *s)
{
	char	**res;
	int		word;
	int		idx;
	int		cnt;

	word = count_word(s);
	res = (char **) malloc(sizeof(char *) * (word + 1));
	if (!res)
		perror_n_exit("malloc()", EXIT_FAILURE);
	idx = 0;
	cnt = 0;
	while (cnt < word)
	{
		res[cnt] = init_word(s, &idx);
		cnt++;
	}
	res[cnt] = NULL;
	return (res);
}