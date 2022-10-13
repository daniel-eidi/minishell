/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:43:02 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/13 16:10:03 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	cd_many_args_msg(void)
{
	printf("cd: too many arguments\n");
	g_data->exit_code = 1;
	return ;
}

int	get_absolute_path(char **cmd, int i, char **absolute_path)
{
	if (cmd[i] == NULL)
	{
		*absolute_path = get_var_value("HOME");
		if (!ft_strcmp(*absolute_path, ""))
		{
			write(2, "cd: HOME not set\n", 17);
			g_data->exit_code = 1;
			return (0);
		}
	}
	else if (!ft_strcmp(cmd[i], "-"))
		back_old_pwd(&*absolute_path);
	else if (cmd[i] && cmd[i + 1])
		cd_many_args_msg();
	else
		*absolute_path = find_absolute_path(cmd[i]);
	return (1);
}

void	set_absolute_path_with_home_value(char **absolute_path)
{
	char	*s;

	*absolute_path = get_var_value("HOME");
	if (!ft_strcmp(*absolute_path, ""))
	{
		s = get_var_value("USER");
		*absolute_path = ft_strjoin("/home/", s);
		free(s);
	}
}
