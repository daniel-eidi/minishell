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
}

void	unset_cmd(char *var_name)
{
	t_list	*aux;

	aux = find_entry(var_name, g_data->hash_table);
	if (aux)
		delete_entry(var_name, g_data->hash_table);
}

void	builtin_unset(t_list *cmd)
{
	t_list	*aux;

	aux = cmd->next;
	while (aux)
	{
		unset_cmd(aux->content);
		aux = aux->next;
	}
}
