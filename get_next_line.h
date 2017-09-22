/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 06:04:25 by gcollett          #+#    #+#             */
/*   Updated: 2017/03/22 10:35:55 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 10000000

typedef	struct		s_memory
{
	int				fd;
	int				pm;
	char			*buf;
	struct s_memory	*next;
	struct s_memory	*prev;
}					t_memory;

int					get_next_line(const int fd, char**line);

#endif
