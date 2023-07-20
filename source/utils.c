#include "ast.h"

static int	ft_word_cnt(const char *str, char c)
{
	int	temp;
	int	answer;

	answer = 0;
	temp = 0;
	while (str[temp])
	{
		while (str[temp] && str[temp] == c)
			temp++;
		if (str[temp] != 0)
			answer += 1;
		while (str[temp] && str[temp] != c)
			temp++;
	}
	return (answer);
}

static char	*ft_word_check(const char **str, char c)
{
	char	*answer;
	int		index;
	int		cnt;

	index = 0;
	while (**str && **str == c)
		(*str)++;
	cnt = 0;
	while ((*str)[cnt] && (*str)[cnt] != c)
		cnt += 1;
	while (**str && **str != c)
	{
		if (index == 0)
		{
			answer = (char *)malloc(sizeof(char) * cnt + 1);
			if (answer == NULL)
				return (NULL);
		}
		answer[index] = **str;
		(*str)++;
		index++;
	}
	answer[index] = '\0';
	return (answer);
}

int		ft_listlen(char **list)
{
	int	i;
	
	i = 0;
	while (list[i])
		i += 1;
	return (i);
}

char	**ft_split(const char *str, char c)
{
	char	**answer;
	int		word_cnt;
	int		temp;
	int		temp2;

	word_cnt = ft_word_cnt(str, c);
	answer = (char **) malloc (sizeof (char *) * (word_cnt + 1));
	if (answer == NULL)
		return (NULL);
	temp = 0;
	while (temp < word_cnt)
	{
		answer[temp] = ft_word_check(&str, c);
		if (answer[temp] == NULL)
		{
			temp2 = -1;
			while (++temp2 <= temp)
				free(answer[temp2]);
			free(answer);
			return (NULL);
		}
		temp += 1;
	}
	answer[temp] = NULL;
	return (answer);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	s1len;
	size_t	s2len;
	size_t	temp;
	char	*answer;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	answer = (char *) malloc (sizeof(char) * (s1len + s2len + 1));
	if (answer == NULL)
		return (NULL);
	temp = 0;
	while (temp < s1len)
	{
		answer[temp] = s1[temp];
		temp += 1;
	}
	while (temp < s1len + s2len)
	{
		answer[temp] = s2[temp - s1len];
		temp += 1;
	}
	answer[temp] = '\0';
	return (answer);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	temp;
	size_t	temp2;
	char	*hay;

	hay = (char *)haystack;
	if (needle[0] == '\0')
		return (hay);
	temp = 0;
	while (temp < len && haystack[temp])
	{
		temp2 = 0;
		while (temp + temp2 < len && haystack[temp + temp2]
			&& haystack[temp + temp2] == needle[temp2])
		{
			temp2 += 1;
		}
		if (needle[temp2] == '\0')
			return (hay + temp);
		temp += 1;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	if (s == NULL)
		return (size);
	while (s[size])
	{
		size += 1;
	}
	return (size);
}

char	*ft_strdup_size(char *s1, int limit_size, int start)
{
	char	*answer;
	int		temp;

	answer = (char *) malloc (sizeof(char) * (limit_size + 1));
	if (answer == NULL)
		return (NULL);
	temp = 0;
	while (temp < limit_size)
	{
		answer[temp] = s1[start];
		start += 1;
		temp += 1;
	}
	answer[temp] = '\0';
	return (answer);
}

char	*ft_strdup(const char *s1)
{
	size_t	temp;
	char	*answer;

	temp = 0;
	while (s1[temp])
		temp += 1;
	answer = (char *) malloc (sizeof(char) * (temp + 1));
	if (answer == NULL)
		return (NULL);
	temp = 0;
	while (s1[temp])
	{
		answer[temp] = s1[temp];
		temp += 1;
	}
	answer[temp] = '\0';
	return (answer);
}

char **append_char_list(char **list, char *value)
{
    int     size;
    char    **new_list;
    int     i;

    size = ft_listlen(list) + 1;
    new_list = malloc(sizeof(char *) * size);
    i = 0;
    while (i < size - 1)
    {
        new_list[i] = ft_strdup(list[i]);
        i += 1;
    }
    new_list[i] = ft_strdup(value);
    free_char_list(list);
    return (new_list);
}

char **delete_char_list(char **list, char *value)
{
	int		size;
	char	**new_list;
	int		i;

	size = ft_listlen(list) - 1;
	new_list = malloc(sizeof(char *) * size);
	i = 0;
	while (i < size)
	{
		if (ft_strcmp(list[i], value) == 0)
			continue;
		new_list[i] = ft_strdup(list[i]);
		i += 1;
	}
	free_char_list(list);
	return (new_list);
}