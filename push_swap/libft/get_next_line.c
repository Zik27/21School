/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vurrigon <vurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 12:58:51 by vurrigon          #+#    #+#             */
/*   Updated: 2019/07/27 17:31:56 by vurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *src, int i)
{
	int		a;
	char	*result_string;

	a = 0;
	if (!(result_string = ft_strnew(i)))
		return (NULL);
	while (src[a] && a < i)
	{
		result_string[a] = src[a];
		a++;
	}
	return (result_string);
}

int			copy_line(char **line, char *content)
{
	int		a;

	a = 0;
	while (content[a] && content[a] != '\n')
		a++;
	if (!(*line = ft_strndup(content, a)))
		return (0);
	return (a);
}

int			read_fd(int fd, char **content)
{
	char	buf[BUFF_SIZE + 1];
	int		result;
	char	*temp;

	while ((result = read(fd, buf, BUFF_SIZE)))
	{
		buf[result] = '\0';
		temp = *content;
		if (!(*content = ft_strjoin(*content, buf)))
			return (-1);
		free(temp);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (result);
}

t_list		*search_fd(t_list **head, int fd)
{
	t_list	*tmp;

	if (!head)
		return (NULL);
	tmp = *head;
	while (tmp)
	{
		if ((int)tmp->content_size == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = ft_lstnew("", fd + 1);
	ft_lstadd(head, tmp);
	return (tmp);
}

int			get_next_line(const int fd, char **line)
{
	char			buf[BUFF_SIZE + 1];
	static t_list	*head;
	t_list			*lst;
	char			*temp;
	int				result_read;

	if (fd < 0 || line == NULL || (read(fd, buf, 0)) < 0 ||
		!(lst = search_fd(&head, fd)))
		return (-1);
	temp = lst->content;
	result_read = read_fd(fd, &temp);
	lst->content = temp;
	if (!result_read && !*temp)
		return (0);
	result_read = copy_line(line, lst->content);
	temp = lst->content;
	if (temp[result_read] != '\0')
	{
		lst->content = ft_strdup(&((lst->content)[result_read + 1]));
		free(temp);
	}
	else
		temp[0] = '\0';
	return (1);
}
