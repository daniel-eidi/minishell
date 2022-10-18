/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_fork_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:48:08 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/18 11:21:03 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error(const char *s, int i)
{
	write(2, s, ft_strlen(s));
	g_data->exit_code = i;
	if (i)
		exit(i);
	exit(EXIT_SUCCESS);
}

void	error_fork(const char *s, int i)
{
	write(2, s, ft_strlen(s));
	if (i)
		exit(i);
	exit(EXIT_SUCCESS);
}

int	open_ok(char *file_str, int flag, int inout)
{
	int		fd;
	char	*file;

	fd = 0;
	file = find_absolute_path(file_str);
	(void)inout;
	if ((inout == 0) && (access(file, F_OK) == -1))
	{
		write(2, file_str, ft_strlen(file_str));
		error(": No such file or directory\n", 1);
	}
	else
	{
		fd = open(file, flag, 0644);
		if (fd == -1)
		{
			write(2, file_str, ft_strlen(file_str));
			error(": Permission denied\n", 1);
		}
	}
	free(file);
	return (fd);
}

int	open_ok_fork(char *file_str, int flag, int inout)
{
	int		fd;
	char	*file;

	fd = 0;
	file = find_absolute_path(file_str);
	if ((inout == 0) && (access(file, F_OK) == -1))
	{
		write(2, file_str, ft_strlen(file_str));
		free_data_after_exec_cmd(NULL);
		free(file);
		error_fork(": No such file or directory\n", 1);
	}
	else
	{
		fd = open(file, flag, 0644);
		if (fd == -1)
		{
			write(2, file_str, ft_strlen(file_str));
			free_data_after_exec_cmd(NULL);
			free(file);
			error_fork(": Permission denied\n", 1);
		}
	}
	free(file);
	return (fd);
}

char	*get_path(char **cmd, const char *path)
{
	char	*file;
	char	*dir;
	int		diff;

	while (*path)
	{
		diff = ft_strchr(path, ':') - path;
		if (diff < 0)
			diff = ft_strlen(path);
		dir = ft_substr(path, 0, diff);
		file = ft_strjoin(dir, "/");
		file = ft_strnjoin(file, cmd[0], ft_strlen(cmd[0]));
		free(dir);
		if (access(file, X_OK) == 0)
			return (file);
		free(file);
		path += diff;
		if (*path)
			path++;
	}
	return (NULL);
}
