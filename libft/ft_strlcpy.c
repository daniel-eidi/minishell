/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:20:50 by daeidi-h          #+#    #+#             */
/*   Updated: 2021/08/09 14:34:16 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief  function copies up to size - 1 characters from the 
 * NUL-terminated string src to dst, NUL-terminating the result
 * 
 * @param dst 
 * @param src 
 * @param size 
 * @return size_t 
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{	
	size_t	i;
	size_t	len;
	char	*cp;
	char	*ori;

	ori = (char *)src;
	cp = (char *)dst;
	len = ft_strlen(ori);
	i = 0;
	if (n == 0)
		return (len);
	while ((i + 1) < n && ori[i] != '\0')
	{
		cp[i] = ori[i];
		i++;
	}
	cp[i] = '\0';
	return (len);
}
