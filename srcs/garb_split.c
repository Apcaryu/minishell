#include "../libft_42/includes_libft/libft.h"
#include "../libft_42/includes_libft/garbage.h"

static int	tot_len(const char *s, char c)
{
	int	len;
	char quote;

	len = 0;
	quote = s[len];
	if (quote == '\'' || quote == '\"')
		len++;
	else
		quote = '\0';
	if (quote != '\0')
	{
		while (s[len] != '\0' && s[len] != quote)
			len++;
		len++;
	}
	else
	{
		while (s[len] != '\0' && s[len] != c)
			len++;
	}
	return (len);
//	while (s[len] != '\0' && (s[len] != c || s[len] != quote))
//		len++;
//	return (len);
}

int	ft_word_count(const char *s, char c)
{
	int	i;
	int	count;
	char quote;

	count = 0;
	i = 0;
//	printf("s = %s\n", s); // TODO remove
	while (s[i] != '\0')
	{
//		printf("s[i] = %c\n", s[i]); // TODO remove
//		sleep(1);
		while (s[i] != '\0' && s[i] == c)
			i++;
		quote = s[i];
		if (quote == '\'' || quote == '\"')
		{
			if (s[i] != '\0')
				count++;
			while (s[i] != '\0' && s[i] != quote)
				i++;
			i++;
		}
		else
		{
			if (s[i] != '\0' && s[i] != c)
				count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (count);
}

char	*ft_strddup(const char *s, char c, t_list *garb_lst)
{
	int		i;
	int		sub_i;
	char	*str;
	char	quote;

	i = 0;
	str = garbage_alloc(&garb_lst, sizeof(char) * tot_len(s, c) + 1);
//	str = ft_calloc(tot_len(s, c) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
//	printf("s = %s\n", s); // TODO remove
	quote = s[i];
	if (quote == '\'' || quote == '\"')
	{
		i++;
		sub_i = 0;
		while (s[i] != 0 && s[i] != quote)
		{
//			printf("s[%d] = %c\n", i, s[i]); // TODO remove
			str[sub_i] = s[i];
//			printf("str = %s\n", str); // TODO remove
			sub_i++;
			i++;
		}
//		printf("str = %s\n", str); // TODO remove
		i++;
	}
	else
	{
		while (s[i] != '\0' && s[i] != c)
		{
			str[i] = s[i];
			i++;
		}
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
	int	i;
	char	**tab;

	i = 0;
	if (s == NULL)
		return (NULL);
	tab = garbage_alloc(&garb_lst, sizeof(char *) * ft_word_count(s, c) + 1);
//	tab = ft_calloc(ft_word_count(s, c) + 1, sizeof(char *));
	if (tab == NULL)
		return (NULL);
//	printf("coucou\n"); // TODO remove
	while (*s && ft_word_count(s, c))
	{
//		printf("1.s = %s\n", s); // TODO remove
		while (*s != '\0' && *s == c)
			s++;
//		printf("2.s = %s\n", s); // TODO remove
		if (*s != '\0' && *s != c)
		{
			tab[i] = ft_strddup(s, c, garb_lst);
//			printf("tab[%d] = %s\n", i, tab[i]); // TODO remove
			if (tab[i] == NULL)
				return (ft_free(tab, i));
			i++;
		}
//		printf("3.s = %s\n", s); // TODO remove
		if (*s == '\'' || *s == '\"')
		{
			s++;
			while (*s != '\0' && *s != '\'' && *s != '\"')
				s++;
			s++;
		}
		else
			while (*s != '\0' && *s != c)
				s++;
//		printf("4.s = %s\n", s); // TODO remove
	}
	return (tab);
}