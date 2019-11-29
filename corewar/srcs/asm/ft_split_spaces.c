/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 11:56:43 by djast             #+#    #+#             */
/*   Updated: 2019/10/19 15:28:05 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		word_count(char const *s)
{
	int	w;
	int	i;

	w = 0;
	i = 0;
	while (s[i])
	{
		if (!(is_whitespace(s[i])) && (is_whitespace(s[i + 1])
			|| s[i + 1] == '\0' || s[i + 1] == SEPARATOR_CHAR) &&
			s[i] != SEPARATOR_CHAR)
			w++;
		if (s[i] == SEPARATOR_CHAR)
			w++;
		i++;
	}
	return (w);
}

static int		word_size(const char *s)
{
	int i;

	i = 0;
	while (is_whitespace(*s) && *s != '\0')
		s++;
	if (*s == SEPARATOR_CHAR)
		return (1);
	while (!(is_whitespace(*s)) && *s != '\0')
	{
		if (*s == SEPARATOR_CHAR)
			break ;
		s++;
		i++;
	}
	return (i);
}

static char		*word_allocation(char **arr, char *word, int size)
{
	int i;

	i = 0;
	word = (char *)malloc(sizeof(char) * (size + 1));
	if (!word)
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		arr = NULL;
		return (NULL);
	}
	return (word);
}

int				ft_word_handling(char **res, char const **s, int *j)
{
	int i;

	i = 0;
	while (is_whitespace(**s) && **s != '\0')
		(*s)++;
	if (**s == SEPARATOR_CHAR)
	{
		(*res)[i++] = *(*s)++;
		(*res)[i] = '\0';
		(*j)++;
		return (0);
	}
	while (!(is_whitespace(**s)) && **s && *(*s - 1))
	{
		(*res)[i++] = *(*s)++;
		if (**s == SEPARATOR_CHAR)
			break ;
	}
	(*res)[i] = '\0';
	(*j)++;
	return (1);
}

char			**ft_split_argument(char const *s)
{
	char	**res;
	int		w_count;
	int		i;
	int		j;

	j = 0;
	if (!s)
		return (NULL);
	if (!(w_count = word_count(s)))
		return (NULL);
	if (!(res = (char **)malloc(sizeof(char *) * (w_count + 1))))
		return (NULL);
	while (j < w_count)
	{
		i = 0;
		if (!(res[j] = word_allocation(res, res[j], word_size(s))))
			return (NULL);
		if (!ft_word_handling(&(res[j]), &s, &j))
			continue;
	}
	res[j] = NULL;
	return (res);
}
