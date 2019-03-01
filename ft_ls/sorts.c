/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorts.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djast <djast@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 19:02:51 by djast             #+#    #+#             */
/*   Updated: 2019/03/01 19:05:15 by djast            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    list_sort_by_name(t_dir **begin_list)
{
    t_dir    *list_prev;
    t_dir    *list_cur;
    t_dir    *list_next;
    int        flag;

    list_cur = *begin_list;
    if (list_cur == 0)
        return ;
    while (1)
    {
        flag = 0;
        list_cur = *begin_list;
        list_prev = NULL;
        while (list_cur->next_file)
        {
            list_next = list_cur->next_file;
            if (ft_strcmp(list_cur->path_file, (list_next->path_file)) > 0)
            {
                flag = 1;
                list_cur->next_file = list_cur->next_file->next_file;
                if (list_prev)
                    list_prev->next_file = list_next;
                list_next->next_file = list_cur;
                if (list_cur == *begin_list)
                    *begin_list = list_next;
            }
            list_prev = list_cur;
            if (list_cur->next_file)
                list_cur = list_cur->next_file;
        }
        if (flag == 0)
            break ;
    }
}

void    list_sort_by_name_rev(t_dir **begin_list)
{
    t_dir    *list_prev;
    t_dir    *list_cur;
    t_dir    *list_next;
    int        flag;

    list_cur = *begin_list;
    if (list_cur == 0)
        return ;
    while (1)
    {
        flag = 0;
        list_cur = *begin_list;
        list_prev = NULL;
        while (list_cur->next_file)
        {
            list_next = list_cur->next_file;
            if (ft_strcmp(list_cur->path_file, (list_next->path_file)) < 0)
            {
                flag = 1;
                list_cur->next_file = list_cur->next_file->next_file;
                if (list_prev)
                    list_prev->next_file = list_next;
                list_next->next_file = list_cur;
                if (list_cur == *begin_list)
                    *begin_list = list_next;
            }
            list_prev = list_cur;
            if (list_cur->next_file)
                list_cur = list_cur->next_file;
        }
        if (flag == 0)
            break ;
    }
}

void    list_sort_by_time(t_dir **begin_list)
{
    t_dir    *list_prev;
    t_dir    *list_cur;
    t_dir    *list_next;
    struct stat buf;
    struct stat buf_2;
    int        flag;

    list_cur = *begin_list;
    if (list_cur == 0)
        return ;
    while (1)
    {
        flag = 0;
        list_cur = *begin_list;
        list_prev = NULL;
        while (list_cur->next_file)
        {
            list_next = list_cur->next_file;
            
            stat(list_cur->path_file, &buf);
            stat(list_next->path_file, &buf_2);
            if (buf.st_mtime < buf_2.st_mtime)
            {
                flag = 1;
                list_cur->next_file = list_cur->next_file->next_file;
                if (list_prev)
                    list_prev->next_file = list_next;
                list_next->next_file = list_cur;
                if (list_cur == *begin_list)
                    *begin_list = list_next;
            }
            list_prev = list_cur;
            if (list_cur->next_file)
                list_cur = list_cur->next_file;
        }
        if (flag == 0)
            break ;
    }
}
