/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_syntax_redir.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:07:05 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/18 10:11:54 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_special_string(char *aux_i)
{
	char	**tokens;
	int		i;
	int		r;

	tokens = (char **) malloc(7 * sizeof(char *));
	tokens[0] = "<";
	tokens[1] = ">";
	tokens[2] = "<<";
	tokens[3] = ">>";
	tokens[4] = "|";
	tokens[5] = "||";
	tokens[6] = NULL;
	r = 0;
	i = -1;
	while (tokens[++i])
	{
		if (!ft_strcmp(aux_i, tokens[i]))
			r = 1;
	}
	free_ptr((void *)&tokens);
	return (r);
}

int	is_redirection_string(char *aux_i)
{
	char	**tokens;
	int		i;
	int		r;

	tokens = (char **) malloc(5 * sizeof(char *));
	tokens[0] = "<";
	tokens[1] = ">";
	tokens[2] = "<<";
	tokens[3] = ">>";
	tokens[4] = NULL;
	r = 0;
	i = -1;
	while (tokens[++i])
	{
		if (!ft_strcmp(aux_i, tokens[i]))
			r = 1;
	}
	free_ptr((void *)&tokens);
	return (r);
}

int	not_null(char *aux_i, int *r)
{
	if (!aux_i)
		return (0);
	if (is_special_string(aux_i))
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, aux_i, ft_strlen(aux_i));
		write(2, "'\n", 2);
		*r = 1;
	}
	return (1);
}

int	check_next_string(char **aux, int *i, int *r)
{
	if (!ft_strcmp(aux[0], "|"))
	{
		write(2, "syntax error near unexpected token `|'\n", 39);
		*r = 1;
		return (1);
	}
	if (not_null(aux[++*i], r))
		return (1);
	else
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		*r = 1;
		return (1);
	}
	return (0);
}

int	invalid_syntax_redir(char *str)
{
	int		i;
	char	**aux;
	int		r;

	aux = ft_split(str, ' ');
	r = 0;
	i = -1;
	while (aux[++i])
	{
		if (is_redirection_string(aux[i]))
		{
			if (check_next_string(aux, &i, &r))
				break ;
		}
	}
	free_split((void **)aux);
	free_ptr((void *)&aux);
	return (r);
}
