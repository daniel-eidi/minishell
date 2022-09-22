#include <minishell.h>

void	env_cmd()
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

int	indentifier_not_valid(char *arg)
{
	int	i;

	if (!ft_isalpha(arg[0]) && (arg[0] != '_'))
		return (1);
	i = 0;
	while ((arg[++i]) && (arg[i] != '='))
	{
		if (!ft_isalnum(arg[i]) && (arg[i] != '_'))
			return (1);
	}
	return (0);
}

void	export_cmd(char	*s)
{
	int	i;
	char	*arg;
	char	*new_key;
	char	*new_value;
	t_item	*item;

	arg = ft_strdup(s);
	if (indentifier_not_valid(arg))
	{
		ft_printf("export: `%s': not a valid indentifier\n", arg);
		return ;
	}
	i = 0;
	while ((arg[i]) && (arg[i] != '='))
		++i;
	if (arg[i] == '\0')
		return ;
	arg[i] = 0;
	new_value = ft_strdup(arg + i + 1);
	new_key = ft_strdup(arg);
	item = new_item(new_key, new_value);
	insert_item(item, g_data->hash_table);
	free(arg);
}

void	unset_cmd(char *var_name)
{
	t_list	*aux;

	aux = find_entry(var_name, g_data->hash_table);
	if (aux)
		delete_entry(var_name, g_data->hash_table);
}
