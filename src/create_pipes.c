/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:41:18 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/06 12:43:18 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	**create_pipes(int n_cmd)
{
	int	i;
	int	**my_pipes;

	i = 0;
	my_pipes = malloc((n_cmd + 2) * (sizeof(int *)));
	my_pipes[n_cmd + 1] = NULL;
	while (n_cmd >= i)
	{
		my_pipes[i] = (int *)malloc((sizeof(int)) * 2);
		if (pipe(my_pipes[i]) == -1)
			printf("Error creating pipes\n");
		i++;
	}
	return (my_pipes);
}

void	close_pipes(int n_cmd, int **pipes, int i)
{
	int	j;

	j = 0;
	while (j <= n_cmd)
	{
		if (j != i)
			close(pipes[j][0]);
		if (i + 1 != j)
			close(pipes[j][1]);
		j++;
	}
}

void	close_pipes_main(int n_cmd, int **pipes)
{
	int	j;

	j = 0;
	while (j <= n_cmd)
	{
		if ((j != n_cmd) && (pipes[j]))
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
		j++;
	}
}
