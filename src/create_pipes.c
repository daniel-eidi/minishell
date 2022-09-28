/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:41:18 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/28 23:20:32 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

int	**create_pipes(int n_cmd)
{
	int	i;
	int	**my_pipes;

	i = 0;
	my_pipes = malloc((n_cmd + 1)* (sizeof (int*)));
	while (n_cmd >= i)
	{
		//dprintf(2, "entrei\n");
		my_pipes[i] = (int *)malloc((sizeof(int))*2);
		if (pipe(my_pipes[i]) == -1)
			printf("Error creating pipes\n");
		//printf("pipes [%d][0] = %d\n", i, my_pipes[i][0]);
		//printf("pipes [%d][1] = %d\n", i, my_pipes[i][1]);
		i++;
	}
	return (my_pipes);
}

void	close_pipes(int n_cmd, int **pipes, int i)
{
	int j;

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
	int j;

	j = 0;
	while (j <= n_cmd)
	{
		if (j != n_cmd)
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
		j++;
	}
}
