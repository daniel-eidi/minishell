/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 18:08:08 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/17 10:41:03 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clear_data(void)
{
	clear_table(g_data->hash_table);
	free_ptr((void *) &g_data);
	rl_clear_history();
}

void	free_pids_and_pipes(t_pids_pipes *aux)
{
	if (aux)
	{
		free_ptr((void *) &aux->pids);
		free_split((void **)aux->pipes);
		free(aux->pipes);
		free(aux);
	}
	clear_cmd_table(g_data->global_table);
}

void	free_and_exit(t_pids_pipes *aux)
{
	if (aux)
	{
		free_ptr((void *) &aux->pids);
		free_split((void **)aux->pipes);
		free(aux->pipes);
	}
	free_ptr((void *)&g_data->aux);
	clear_data();
}
