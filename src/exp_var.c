/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:52:40 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/18 11:03:13 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_var_ind(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == -2)
		{
			if (ft_isalnum(s[i + 1]) || (s[i + 1] == '_') || s[i + 1] == '?')
				return (i);
			else
				s[i] = '$';
		}
	}
	return (-1);
}

char	*get_line_with_var_expanded(char *s, int ind, int end, t_list **table)
{
	char	*s2;
	char	*p;
	t_list	*aux;

	if (s[end] == '?')
	{
		p = ft_itoa(g_data->exit_code);
		s2 = ft_strjoin(p, s + end + 1);
		free_ptr((void *) &p);
	}
	else
	{
		s2 = ft_substr(s, ind + 1, end - ind);
		aux = find_entry(s2, table);
		free_ptr((void *) &s2);
		if (aux == NULL)
			s2 = ft_strjoin("", s + end + 1);
		else
			s2 = ft_strjoin(((t_item *)aux->content)->value, s + end + 1);
	}
	s[ind] = '\0';
	p = ft_strjoin(s, s2);
	free_ptr((void *) &s);
	free_ptr((void *) &s2);
	return (p);
}

char	*exp_var(char *line, t_list **table)
{
	int		ind;
	int		end;
	char	*new_line;

	ind = get_var_ind(line);
	if (ind == -1)
	{
		new_line = ft_strdup(line);
		free_ptr((void *)&line);
		return (new_line);
	}
	while (ind > -1)
	{
		end = ind + 1;
		if (ft_isalpha(line[end]) || (line[end] == '_'))
		{
			while (ft_isalnum(line[end + 1]) || (line[end + 1] == '_'))
				end++;
		}
		line = get_line_with_var_expanded(line, ind, end, table);
		ind = get_var_ind(line);
	}
	return (line);
}
