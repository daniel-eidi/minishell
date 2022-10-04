/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 08:09:33 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/04 09:27:06 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>



static void	process_heredoc(char *redir, t_pids_pipes *aux, int n_cmd, int *fd)
{
	char	*s;
	char	*n_cmd_str;
	char	*name;
(void)aux;

	if (fd[0])
		close(fd[0]);
	n_cmd_str = ft_itoa(n_cmd);
	name = ft_strjoin("/tmp/inputfile", n_cmd_str);
	free(n_cmd_str);
	fd[0] = open_ok(name, O_WRONLY | O_CREAT | O_TRUNC, 0);
	//limiter = ft_strjoin(redir, "\n");
	//write(1, "> ", 2);
	s = readline("> ");
	printf("entrei e limiter = %s\n", redir);
	while (!s || ft_strcmp(s, redir))
	{
		printf("entrei \n");
		write(fd[0], s, ft_strlen(s));
		write(fd[0], "\n", 1);
		//free(s);
		//write(1, "> ", 2);
		s = readline("> ");
	}
	close(fd[0]);
}

static void	open_heredoc(char **redir, t_pids_pipes *aux, int n_cmd)
{
	int	fd[2];
	int	i;
	
	fd[0] = 0;
	fd[1] = 0;
	i = -1;
	while (redir[++i])
	{
		if (ft_strcmp (redir[i], "<<") == 0)
			//create_heredoc(redir[++i], aux->pipes[n_cmd][0]);
			process_heredoc(redir[++i], aux, n_cmd, fd);
	}
}

void prepare_heredoc(char **cmds, t_pids_pipes *aux)
{
		int	i;
		t_cmd *cmd_table;

		i = -1;
		while (cmds[++i])
		{
			cmd_table = make_cmd_table(cmds[i]);
			open_heredoc(cmd_table->redirections, aux, i);
			clear_cmd_table (cmd_table);
		}
}