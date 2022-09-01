/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:20:44 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/04/02 22:44:00 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_ptr(char **str)
{
	free (*str);
	*str = NULL;
}

static char	*save_line(int r, char **last_line, char **currentline)
{
	char	*temp;

	if (r <= 0 && (!ft_strlen(*last_line) || *last_line == NULL))
	{
		free_ptr(last_line);
		return (NULL);
	}
	else if (!ft_strchr(*last_line, '\n') && !last_line)
	{
		*currentline = ft_strdup(*last_line);
		free_ptr(last_line);
	}
	else
	{
		temp = *last_line;
		*currentline = ft_substr(temp, 0, (ft_strchr(temp, '\n') \
		+ 1 - *last_line));
		*last_line = ft_substr(temp, (ft_strchr(temp, '\n') \
		+ 1 - temp), ft_strlen(temp));
		free_ptr(&temp);
	}
	return (*currentline);
}

static char	*load(char **last_line, char **buf, int fd, char **current_line)
{
	char	*temp;
	int		r;

	r = 1;
	if (!*last_line)
		*last_line = ft_strdup("");
	while (!ft_strchr(*last_line, '\n') \
	&& (r > 0))
	{	
		r = read(fd, *buf, BUFFER_SIZE);
		(*buf)[r] = '\0';
		temp = *last_line;
		*last_line = ft_strjoin(temp, *buf);
		free_ptr(&temp);
	}
	free_ptr(buf);
	return (save_line(r, last_line, current_line));
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*last_line = NULL;
	char		*current_line;

	buf = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	if (read(fd, buf, 0) < 0)
	{
		free_ptr(&buf);
		return (NULL);
	}
	current_line = load(&last_line, &buf, fd, &current_line);
	return (current_line);
}
