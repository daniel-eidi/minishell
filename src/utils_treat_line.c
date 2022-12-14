/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_treat_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:46:30 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/29 16:29:26 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include<minishell.h>

char	*ft_strnjoin(char *s1, char *s2, int x)
{
	char			*new;
	int				i;
	int				j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(s1) + x + 1));
	while ((s1[i]) != '\0')
	{
		new[i] = ((char) s1[i]);
		i++;
	}
	while ((s2[j] != '\0') && (j < x))
	{
		new[i + j] = (char) s2[j];
		j++;
	}
	new[i + j] = '\0';
	free_ptr((void *)&s1);
	return (new);
}

void	restore_char(char **exec_args, char find, char change)
{
	char	*str;

	while (*exec_args)
	{
		str = *exec_args;
		while (*str)
		{
			if (*str == find)
				*str = change;
			str++;
		}
		exec_args++;
	}
	return ;
}
