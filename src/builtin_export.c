#include <minishell.h>

void	set_var(char *new_key, char *new_value)
{
	t_list	*aux;

	aux = find_entry(new_key, g_data->hash_table);
	if (aux)
	{
		free(((t_item *) aux->content)->value);
		((t_item *) aux->content)->value = new_value;
		free(new_key);
	}
	else
		insert_item(new_item(new_key, new_value), g_data->hash_table);
	//free(new_key);
	//free(new_value);
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

int	export_cmd(char	*s)
{
	int	i;
	char	*arg;
	char	*new_key;
	char	*new_value;

	arg = ft_strdup(s);
	if (indentifier_not_valid(arg))
	{
		ft_printf("export: `%s': not a valid indentifier\n", arg);
		return (1);
	}
	i = 0;
	while ((arg[i]) && (arg[i] != '='))
		++i;
	if (arg[i] == '\0')
		return (1);
	arg[i] = 0;
	new_value = ft_strdup(arg + i + 1);
	new_key = ft_strdup(arg);
	free(arg);
	set_var(new_key, new_value);
	return (0);
}

void	builtin_export(t_list *cmd)
{
	t_list	*aux;

	aux = cmd->next;
	while (aux)
	{
		export_cmd(aux->content);
		aux = aux->next;
	}
}
