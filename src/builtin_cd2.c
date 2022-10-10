/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:16:16 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/10 17:08:20 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_var_value(char *key)
{
	t_list	*temp;

	temp = find_entry(key, g_data->hash_table);
	if (temp == NULL)
		return ("");
	return (ft_strdup(((t_item *)temp->content)->value));
}

char	*free_args_and_return(char **args, char *absolute_path)
{
	free_split((void **)args);
	free_ptr((void *) &args);
	return (absolute_path);
}

char	*find_absolute_path(char *path)
{
	char	*absolute_path;
	char	**args;
	int		i;

	if (path[0] == '/')
		return (ft_strdup(path));
	args = ft_split(path, '/');
	i = -1;
	if (!ft_strcmp(args[0], "~"))
	{
		absolute_path = get_var_value("HOME");
		i++;
	}
	else
		absolute_path = get_var_value("PWD");
	while (args[++i])
	{
		if (!ft_strcmp(args[i], ".."))
			go_up_one_dir(absolute_path);
		else if (!ft_strcmp(args[i], "."))
			continue ;
		else
			absolute_path = go_down_to_dir(absolute_path, args[i]);
	}
	return (free_args_and_return(args, absolute_path));
}

void	go_up_one_dir(char *path)
{
	int	i;

	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	if (i != 0)
		path[i] = '\0';
	else
		path[i + 1] = '\0';
}

char	*go_down_to_dir(char *path, char *dir)
{
	char	*s;

	if (path[ft_strlen(path) - 1] != '/')
	{
		s = ft_strjoin(path, "/");
		free(path);
	}
	path = ft_strjoin(s, dir);
	free(s);
	return (path);
}
