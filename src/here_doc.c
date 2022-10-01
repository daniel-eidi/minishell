/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 17:25:02 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/08/25 23:15:44 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static void	reading_stdin(int fd, char *argv_limiter)
{
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(argv_limiter, "\n");
	line = ft_get_next_line_lim(STDIN_FILENO, limiter);
	while (line)
	{
		if (!ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
		{
			free_ptr(&limiter);
			free_ptr(&line);
			close(fd);
			exit(0);
		}
		write(fd, line, ft_strlen(line));
		free_ptr(&line);
		line = ft_get_next_line_lim(STDIN_FILENO, limiter);
	}
	close(fd);
	free_ptr(&line);
	free_ptr(&limiter);
	free(limiter);
}

void	create_heredoc(char *argv_limiter)
{
	int		fd_2[2];
	pid_t	pid;
	int		status;

	if (pipe(fd_2) < 0)
		error("pipe", 0);
	pid = fork();
	if (pid < 0)
		error("fork", 0);
	if (pid > 0)
	{
		close(fd_2[WRITE_END]);
		waitpid(pid, &status, 0);
		dup2(fd_2[READ_END], STDIN_FILENO);
		close(fd_2[READ_END]);
	}
	else
	{
		close(fd_2[READ_END]);
		reading_stdin(fd_2[WRITE_END], argv_limiter);
	}
}
