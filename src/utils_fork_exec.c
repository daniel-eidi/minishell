/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fork_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:48:08 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/30 17:43:52 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error(const char *s, int i)
{
	//perror(s);
	write(2, s, ft_strlen(s));
	if (i)
		exit(i);
	exit(EXIT_SUCCESS);
}

int	open_ok(char *file, int flag, int inout)
{
	int	fd;

	fd = open(file, flag, 0644);
	if (fd == -1 && inout == 0)
		error("infile", 1);
	if (fd == -1 && inout == 1)
		error("outfile", 1);
	return (fd);
}

char	*get_path(char **cmd, const char *path)
{
	char	*file;
	char	*dir;
	int		diff;

	while (*path)
	{
		//dprintf(2,"path em getpath = %s\n", path);
		diff = ft_strchr(path, ':') - path;
		if (diff < 0)
			diff = ft_strlen(path);
		dir = ft_substr(path, 0, diff);
		file = ft_strjoin(dir, "/");
		file = ft_strjoin(file, cmd[0]);
		free(dir);
		if (access(file, X_OK) == 0)
			return (file);
		free(file);
		if (ft_strlen(path) < (size_t)diff)
			break ;
		path += diff;
		if (*path)
			path++;		
	}
	//error("command", 127);
	//write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, cmd[0], ft_strlen(cmd[0]));
	free(cmd);
	//dprintf(2,"cmd 0 = %s\n", cmd[0]);
	error(": command not found\n", 127);
	return (NULL);
}
