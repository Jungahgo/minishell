#include "ast.h"
/*
size_t	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		r_idx;
	int		s_idx;

	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	r_idx = 0;
	s_idx = 0;
	while (s1 && s1[s_idx])
	{
		res[r_idx] = s1[s_idx];
		r_idx++;
		s_idx++;
	}
	s_idx = 0;
	while (s2 && s2[s_idx])
	{
		res[r_idx] = s2[s_idx];
		r_idx++;
		s_idx++;
	}
	res[r_idx] = 0;
	return (res);
}

char	*ft_strdup(const char *s1)
{
	char	*res;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	res_len;

	res_len = len;
	if (ft_strlen(s) < start)
		res_len = 0;
	else if (ft_strlen(s) - start <= len)
		res_len = ft_strlen(s) - start;
	res = (char *)malloc(sizeof(char) * (res_len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < res_len && s[start])
	{
		res[i] = s[start];
		i++;
		start++;
	}
	res[i] = 0;
	return (res);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (n == 0 || (!dst && !src))
		return (dst);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	if (i < n)
		d[i] = 0;
	return (dst);
}
