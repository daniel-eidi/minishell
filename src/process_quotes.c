/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:00:23 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/10 15:07:30 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	process_quotes(char *line)
{
	int	i;
	int	s;
	int	d;

	d = 0;
	s = 0;
	i = -1;
	while (line[++i])
	{
		if ((line[i] == '$') && !s)
			line[i] = -2;
		if ((line[i] == ' ') && (s || d))
			line[i] = -1;
		if ((line[i] == '|') && (s || d))
			line[i] = -3;
		if ((line[i] == 39) && !d)
			s = !s;
		if ((line[i] == 34) && !s)
			d = !d;
	}
}

void	process_quotes2(char *line)
{
	int	i;
	int	p;
	int	s;
	int	d;

	d = 0;
	s = 0;
	p = 0;
	i = -1;
	while (line[++i])
	{
		line[i - p] = line[i];
		p += ((!s && (line[i] == 34)) || (!d && (line[i] == 39)));
		if ((line[i] == 39) && !d)
			s = !s;
		if ((line[i] == 34) && !s)
			d = !d;
	}
	line[i - p] = line[i];
}
