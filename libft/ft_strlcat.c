/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:20:50 by daeidi-h          #+#    #+#             */
/*   Updated: 2021/08/09 15:00:48 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief  function appends the NUL-terminated string src to the end of dst.
 * It will append at most size - strlen(dst) - 1 bytes, NUL-terminating the
 * result.
 * 
 * @param dst 
 * @param src 
 * @param size 
 * @return size_t 
 */
size_t	ft_strlcat(char *dst, const char *src, size_t n)
{	
	size_t	i;
	size_t	j;
	size_t	len;
	char	*cat;
	char	*s;

	s = (char *)src;
	cat = (char *)dst;
	len = ft_strlen(s);
	i = 0;
	j = 0;
	if (n == 0)
		return (len);
	while (i < n && cat[i] != '\0')
		i++;
	while ((j + i) < (n - 1) && s[j] != '\0')
	{
		cat[i + j] = s[j];
		j++;
	}
	if (i < n)
		cat[i + j] = '\0';
	return (len + i);
}
