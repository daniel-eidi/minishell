/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ind.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 15:10:04 by mgaldino          #+#    #+#             */
/*   Updated: 2022/10/10 15:10:29 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <hash_table.h>

unsigned long	get_hash(char *s)
{
	unsigned long	hash;
	int				i;
	int				len;

	len = ft_strlen(s);
	hash = 0;
	i = -1;
	while (++i < len)
	{
		hash += (s[i] + 1) * ft_pow(P_PARAM, i);
	}
	return (hash % M_PARAM);
}

int	get_ind(char *key, t_list **table)
{
	int	ind;
	int	size;

	size = 0;
	while (table[size])
		++size;
	ind = get_hash(key) % size;
	return (ind);
}
