/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 06:03:03 by gcollett          #+#    #+#             */
/*   Updated: 2017/03/06 01:20:57 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include "get_next_line.h"

t_memory		*init_struct(t_memory *save, int fd)
{
	int					state;
	t_memory			*recup;
	int					cmp;

	recup = save;
	state = 0;
	cmp = 0;
	if (save)
		while (state != 2)
		{
			if (save->fd == fd || cmp == 10)
				break ;
			state = (!save->prev && state == 0) ? 1 : state;
			state = (!save->next && state == 1) ? 2 : state;
			if (state == 0)
				save = save->prev;
			else
				save = save->next;
			if (save)
				if (save->fd)
					printf("Save->fd = %d\n",save->fd);
		}
	if (!save || save->fd != fd)
	{
		save = NULL;
		save = malloc(sizeof(t_memory));
		save->fd = (int)fd;
		save->prev = recup;
		if (recup != save && recup)
			recup->next = save;
		save->next = NULL;
		save->pm = 1;
		ft_bzero(save->buf, BUFF_SIZE + 1);
	}
	return (save);
}

static int		ft_attrib(char **line, t_memory *save, int cmp, int p)
{
	while (p != -1)
	{
		while (save->buf[p] != '\n' && save->buf[p])
			line[0][cmp++] = save->buf[p++];
		line[0][cmp] = (save->buf[p] == '\n') ? '\0' : line[0][cmp];
		if (save->buf[p] != '\n')
			*line = ft_realloc(*line, cmp + 1, BUFF_SIZE, 1);
		p = (save->buf[p] == '\n') ? -1 : 0;
		if (p == 0 && (save->pm = read(save->fd, save->buf, BUFF_SIZE)) == 0)
		{
			p = -1;
			if (!save->buf[0])
			{
				if (save->prev)
					(save->prev)->next = save->next;
				if(save->next)
					(save->next)->prev = save->prev;
				free(save);
				return (0);
			}
		}
		save->buf[save->pm] = (p == 0) ? '\0' : save->buf[save->pm];
	}
	cmp = &(*ft_strchr(save->buf, '\n')) - &(*save->buf) + 1;
	while (cmp > 0 && p++ < save->pm - cmp)
		save->buf[p] = save->buf[cmp + p];
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static	t_memory	*save;

	if (fd < 0 || !BUFF_SIZE || !line)
		return (-1);
	save = init_struct(save, fd);
	if (save->pm < 1)
		return (save->pm);
	if (save->buf[0] == '\0')
		if ((save->pm = read(save->fd, save->buf, BUFF_SIZE)) < 1)
		{
			if (save->prev)
				(save->prev)->next = save->next;
			if(save->next)
				(save->next)->prev = save->prev;
			free(save);
			return (read(fd, "", BUFF_SIZE));
		}
	*line = ft_memalloc(BUFF_SIZE + 1);
	save->pm = (ft_strlen(save->buf) > 0) ? ft_strlen(save->buf) : 1;
	return (ft_attrib(line, save, 0, 0));
}
