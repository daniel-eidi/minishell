/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:32:57 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/30 17:32:58 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_var_value(char *key)
{
	t_list	*temp;

	temp = find_entry(key, g_data->hash_table);
	if (temp == NULL)
		return ("");
	return (((t_item *)temp->content)->value);
}

static char	*get_init_dir_path(int count_under)
{
	char	*temp;
	char	*dir;
	int		dir_found;
	int		dir_pos;

	dir = NULL;
	dir_found = 0;
	temp = get_var_value("PWD");
	dir_pos = ft_strlen(temp);
	while (count_under > dir_found && dir_pos > 0)
	{
		if (temp[--dir_pos] == '/')
			dir_found++;
	}
	if (dir_pos == 0)
		dir = ft_strdup("/");
	else
		dir = ft_substr(temp, 0, dir_pos);
	return (dir);
}

char	*get_under_dir_path(char *path)
{
	char	*absolute_path;
	char	*dir;
	int		count_under;

	absolute_path = NULL;
	count_under = 0;
	while (ft_strncmp(path + (count_under * 3), "../", 3) == 0)
		count_under++;
	dir = get_init_dir_path(count_under);
	if (ft_strlen(path + (count_under * 3)))
		absolute_path = ft_strjoin(dir, path + (count_under * 3) - 1);
	else
		absolute_path = ft_strdup(dir);
	free_ptr((void *)&dir);
	return (absolute_path);
}

char	*find_absolute_path(char *path)
{
	char	*absolute_path;

	absolute_path = NULL;
	if (path[0] == '~' )
		absolute_path = ft_strjoin(get_var_value("HOME"), path + 1);
	else if (path[0] == '/')
		absolute_path = ft_strdup(path);
	else if (ft_strncmp(path, "./", 2) == 0)
		absolute_path = ft_strjoin(get_var_value("PWD"), path + 1);
	else if (ft_strcmp(path, "..") == 0)
		absolute_path = get_init_dir_path(1);
	else if (ft_strncmp(path, "../", 3) == 0)
		absolute_path = get_under_dir_path(path);
	else
	{
		absolute_path = ft_strjoin(get_var_value("PWD"), "/");
		absolute_path = ft_strnjoin(absolute_path, path, ft_strlen(path));
	}
	if (absolute_path[ft_strlen(absolute_path) - 1] == '/' \
	&& ft_strcmp(absolute_path, "/") != 0)
		absolute_path[ft_strlen(absolute_path) - 1] = '\0';
	return (absolute_path);
}

static bool is_dir(char *absolute_path)
{
	struct stat	status_buffer;
	
	if (chdir(absolute_path) < 0)
	{
		if (stat(absolute_path, &status_buffer) == 0)
			printf("cd: %s: Not a directory\n", absolute_path);
		// else
		// 	printf("cd: %s: No such file or directory\n", absolute_path);
		return (false);
	}
	return (true);
}

void	builtin_cd(char **cmd)
{
	char	*absolute_path;
	int		i;

	i = 1;
	g_data->exit_code = 0;
	absolute_path = NULL;
	if (cmd[i] == NULL)
		absolute_path = ft_strdup(get_var_value("HOME"));
	else if (cmd[i] && cmd[i + 1])
	{
		printf("cd: too many arguments\n");
		g_data->exit_code = 1;
		return ;
	}
	else
		absolute_path = find_absolute_path(cmd[i]);
	if (is_dir(absolute_path))
	{
		update_hashtable("OLDPWD", get_var_value("PWD"), g_data->hash_table);
		update_hashtable("PWD", absolute_path, g_data->hash_table);
	}
	free_ptr((void *)&absolute_path);
	dprintf(2, "path = %s\n", absolute_path);
}
