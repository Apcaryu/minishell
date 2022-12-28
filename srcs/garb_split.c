#include "../libft_42/includes_libft/libft.h"
#include "../libft_42/includes_libft/garbage.h"

static int	tot_len(const char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

int	ft_word_count(const char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
			count++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (count);
}

char	*ft_strddup(const char *s, char c, t_list *garb_lst)
{
	int		i;
	char	*str;

	i = 0;
	str = garbage_alloc(&garb_lst, sizeof(char) * tot_len(s, c) + 1);
//	str = ft_calloc(tot_len(s, c) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	**ft_free(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

char	**garb_split(char const *s, char c, t_list *garb_lst)
{
	size_t	i;
	char	**tab;

	i = 0;
	if (s == NULL)
		return (NULL);
	tab = garbage_alloc(&garb_lst, sizeof(char *) * ft_word_count(s, c));
//	tab = ft_calloc(ft_word_count(s, c) + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
	while (*s && ft_word_count(s, c))
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0' && *s != c)
		{
			tab[i] = ft_strddup(s, c, garb_lst);
			if (tab[i] == NULL)
				return (ft_free(tab, i));
			i++;
		}
		while (*s != '\0' && *s != c)
			s++;
	}
	return (tab);
}