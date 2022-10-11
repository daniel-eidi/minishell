/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:56:49 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/11 18:50:22 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	return_and_free_arg(char *arg, int exit_code)
{
	g_data->exit_code = exit_code;
	free(arg);
	return (1);
}

int	export_cmd(char	*s)
{
	int		i;
	char	*arg;
	char	*new_key;
	char	*new_value;

	arg = ft_strdup(s);
	if (indentifier_not_valid(arg))
	{
		ft_printf("export: `%s': not a valid indentifier\n", arg);
		return (return_and_free_arg(arg, 1));
	}
	i = 0;
	while ((arg[i]) && (arg[i] != '='))
		++i;
	if (arg[i] == '\0')
		return (return_and_free_arg(arg, 0));
	arg[i] = 0;
	new_value = ft_strdup(arg + i + 1);
	new_key = ft_strdup(arg);
	free(arg);
	set_var(new_key, new_value);
	return (0);
}

void	builtin_export(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[++i])
		export_cmd(cmd[i]);
}
