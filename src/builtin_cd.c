/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:32:57 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/11 18:31:37 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static bool	is_dir(char *absolute_path, char *cmd)
{
	if (chdir(absolute_path) < 0)
	{
		write(2, "cd: ", 4);
		write(2, cmd, ft_strlen(cmd));
		if (!access(absolute_path, F_OK))
			write(2, ": Not a directory\n", 18);
		else
			write(2, ": No such file or directory\n", 28);
		return (false);
	}
	return (true);
}

static void	back_old_pwd(char **absolute_path)
{
	char	*s;
	char	*str;

	s = *absolute_path;
	str = get_var_value("OLDPWD");
	*absolute_path = ft_strdup(str);
	free(s);
	free(str);
	write(1, *absolute_path, ft_strlen(*absolute_path));
	write(1, "\n", 1);
}

void	builtin_cd(char **cmd)
{
	char	*absolute_path;
	char	*actual_pwd;
	int		i;

	i = 1;
	g_data->exit_code = 0;
	absolute_path = NULL;
	if (cmd[i] == NULL)
		absolute_path = get_var_value("HOME");
	else if (!ft_strcmp(cmd[i], "-"))
		back_old_pwd(&absolute_path);
	else if (cmd[i] && cmd[i + 1])
		cd_many_args_msg();
	else
		absolute_path = find_absolute_path(cmd[i]);
	if (is_dir(absolute_path, cmd[i]))
	{
		actual_pwd = get_var_value("PWD");
		update_hashtable("OLDPWD", actual_pwd, g_data->hash_table);
		update_hashtable("PWD", absolute_path, g_data->hash_table);
		free_ptr((void *) &actual_pwd);
	}
	else
		g_data->exit_code = 1;
	free_ptr((void *)&absolute_path);
}
