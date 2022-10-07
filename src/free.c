/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:13:29 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/07 11:43:08 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include<minishell.h>

void	free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void free_split(void **ptr)
{
	int i;

	i = 0;
	while(ptr[i])
		free_ptr((void *) &ptr[i++]);
}
