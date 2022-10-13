/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:58:51 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/13 11:53:11 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	restore_spaces(char **exec_args)
{
	char	*str;

	while (*exec_args)
	{
		str = *exec_args;
		while (*str)
		{
			if (*str == -1)
				*str = ' ';
			str++;
		}
		exec_args++;
	}
}

void	clear_cmd_table(t_cmd *table)
{
	free_split((void **) table->cmd_and_args);
	free(table->cmd_and_args);
	free_split((void **) table->redirections);
	free(table->redirections);
	free(table);
}

t_cmd	*alloc_cmd(char **split)
{
	int		n_cmd;
	int		n_redir;
	int		i;
	t_cmd	*aux;

	n_cmd = 0;
	n_redir = 0;
	i = -1;
	while (split[++i])
	{
		if ((!ft_strcmp(split[i], ">")) || (!ft_strcmp(split[i], "<")) || \
			(!ft_strcmp(split[i], ">>")) || (!ft_strcmp(split[i], "<<")))
		{
			n_redir += 2;
			i++;
		}
		else
			n_cmd++;
	}
	aux = (t_cmd *) malloc(sizeof(t_cmd));
	aux->cmd_and_args = (char **) malloc((n_cmd + 1) * sizeof(char *));
	aux->cmd_and_args[n_cmd] = NULL;
	aux->redirections = (char **) malloc((n_redir + 1) * sizeof(char *));
	aux->redirections[n_redir] = NULL;
	return (aux);
}

void	fill_cmd_table(t_cmd *table, char **split)
{
	int	cmd_ind;
	int	redir_ind;
	int	i;

	cmd_ind = -1;
	redir_ind = -1;
	i = -1;
	while (split[++i])
	{
		if ((!ft_strcmp(split[i], ">")) || (!ft_strcmp(split[i], "<")) || \
			(!ft_strcmp(split[i], ">>")) || (!ft_strcmp(split[i], "<<")))
		{
			table->redirections[++redir_ind] = ft_strdup(split[i]);
			table->redirections[++redir_ind] = ft_strdup(split[++i]);
		}
		else
			table->cmd_and_args[++cmd_ind] = ft_strdup(split[i]);
	}
}

t_cmd	*make_cmd_table(char *line)
{
	char	**split;
	t_cmd	*cmd_table;
	int		i;

	split = ft_split(line, ' ');
	i = -1;
	while (split[++i])
		split[i] = exp_var(split[i], g_data->hash_table);
	restore_spaces(split);
	cmd_table = alloc_cmd(split);
	fill_cmd_table(cmd_table, split);
	free_split((void **) split);
	free(split);
	return (cmd_table);
}
