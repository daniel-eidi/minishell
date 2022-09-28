/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 16:20:44 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/28 16:46:04 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <pipex.h>

static void	free_ptr(char **str)
{
	free(*str);
	*str = NULL;
}

static char	*save_line(int r, char **last_line, \
char **currentline, char *limiter)
{
	char	*temp;

	if (r <= 0 && (!ft_strlen(*last_line) || *last_line == NULL))
	{
		free_ptr(last_line);
		return (NULL);
	}
	else if (!ft_strncmp(*last_line, limiter, ft_strlen(limiter)))
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

static int	check(int fd, char *buf)
{
	if (!buf)
		return (1);
	if (read(fd, buf, 0) < 0)
	{
		free_ptr(&buf);
		return (1);
	}
	return (0);
}

static char	*load(char **last_line, int fd, char **current_line, char *limiter)
{
	char	*temp;
	int		r;
	char	*buf;

	buf = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (check(fd, buf))
		return (NULL);
	r = 1;
	if (!*last_line)
		*last_line = ft_strdup("");
	while (!ft_strchr(*last_line, '\n') \
	&& (r > 0))
	{	
		r = read(fd, buf, BUFFER_SIZE);
		(buf)[r] = '\0';
		temp = *last_line;
		*last_line = ft_strjoin(temp, buf);
		free_ptr(&temp);
	}
	free_ptr(&buf);
	return (save_line(r, last_line, current_line, limiter));
}

char	*ft_get_next_line_lim(int fd, char *limiter)
{
	static char	*last_line = NULL;
	char		*current_line;

	current_line = load(&last_line, fd, &current_line, limiter);
	return (current_line);
}
