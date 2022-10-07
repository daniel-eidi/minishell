#include <minishell.h>

void	builtin_env()
{
	t_list	*aux;
	int	i;

	i = -1;
	while (g_data->hash_table[++i])
	{
		aux = (g_data->hash_table[i]);
		while (aux)
		{
			ft_printf("%s=%s\n",((t_item *) aux->content)->key, \
					((t_item *) aux->content)->value);
			aux = aux->next;
		}
	}
	g_data->exit_code = 0;
}

void	unset_cmd(char *var_name)
{
	t_list	*aux;

	aux = find_entry(var_name, g_data->hash_table);
	if (aux)
		delete_entry(var_name, g_data->hash_table);
}

void	builtin_unset(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
		unset_cmd(cmd[i]);
}
