#include <minishell.h>

void	clear_data()
{
	clear_table(g_data->hash_table);
	free(g_data);
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
		free(aux);
	}
	clear_data();
}
