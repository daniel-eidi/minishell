/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:13:29 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/15 02:13:31 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include<minishell.h>

void	free_ptr(void **ptr)
{
	if (*ptr)
	{
		*ptr = NULL;
		free(*ptr);
	}
}

void	free_split(void **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free_ptr((void *) &ptr[i++]);
}
