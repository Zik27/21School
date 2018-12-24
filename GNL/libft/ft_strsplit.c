/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:56:13 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/07 14:31:14 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_words(char const *s, char c)
{
	int	count;

	count = 0;
	if (*s != '\0' && *s != c)
		count++;
	while (*s)
	{
		if (*s == c && *(s + 1) != c && *(s + 1) != '\0')
			count++;
		s++;
	}
	return (count);
}

static void		check_delimiter(char *s, char c, int *j)
{
	while (s[*j] && s[*j] == c)
		(*j)++;
}

static char		*ft_word(char *s, char c, int *j)
{
	char	*tmp;
	int		len_word;
	int		i;
	int		tmp_j;

	len_word = 0;
	tmp = s;
	tmp_j = *j;
	while (tmp[tmp_j] != c && tmp[tmp_j])
	{
		len_word++;
		tmp_j++;
	}
	tmp = (char *)malloc(sizeof(tmp) * len_word + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len_word)
		tmp[i++] = s[(*j)++];
	tmp[i] = '\0';
	return (tmp);
}

char			**ft_strsplit(char const *s, char c)
{
	int		count;
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	count = count_words(s, c);
	result = (char **)malloc(sizeof(*result) * count + 1);
	if (!result)
		return (NULL);
	while (i < count && s[i])
	{
		check_delimiter((char *)s, c, &j);
		result[i++] = ft_word((char *)s, c, &j);
	}
	result[i] = NULL;
	return (result);
}
