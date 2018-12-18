/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 14:04:57 by vurrigon          #+#    #+#             */
/*   Updated: 2018/12/07 14:29:11 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		begin;
	int		len;
	char	*fresh;

	if (!s)
		return (NULL);
	begin = 0;
	len = ft_strlen(s) - 1;
	while (s[begin] == ' ' || s[begin] == '\t' || s[begin] == '\n')
		begin++;
	if (s[begin] == '\0')
		return (ft_strdup(s + begin));
	while ((s[len] == ' ' || s[len] == '\t' || s[len] == '\n') && len > 0)
		len--;
	fresh = ft_strsub(s, begin, len - begin + 1);
	if (!fresh)
		return (NULL);
	return (fresh);
}
