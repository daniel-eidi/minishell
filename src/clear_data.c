#include <minishell.h>

void	clear_data()
{
	clear_table(g_data->hash_table);
	free(g_data);
	rl_clear_history();
}