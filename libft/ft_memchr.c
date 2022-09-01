/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:20:50 by daeidi-h          #+#    #+#             */
/*   Updated: 2021/08/20 10:11:44 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief  scan the initial n bytes of S, stopping in the 
 * first match of value c. s and c are interpreted as unsigned char.
 * 
 * @param s source to start
 * @param c constant byte that will be scanned
 * @param n max bytes positions to run
 * @return void* pointer found char c in s or null
*/
void	*ft_memchr(const void *s, int c, size_t n)
{	
	size_t			i;
	unsigned char	*b;
	unsigned char	chr;

	b = (unsigned char *)s;
	chr = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (b[i] == chr)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}
