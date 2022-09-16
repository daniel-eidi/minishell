/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 16:30:00 by mgaldino          #+#    #+#             */
/*   Updated: 2022/04/26 00:23:57 by mgaldino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_word(int pos, int *word_l, char *s);
static	int	ft_word_num(char *s, char c);
static void	ft_set(int *i, int *j, int *word_l);

char	**ft_split(char const *s, char c)
{
	int		i;
	int		word_l;
	int		j;
	char	**p_return;

	p_return = (char **) malloc(ft_word_num((char *)s, c) * sizeof(char *));
	if (!p_return)
		return (NULL);
	ft_set(&i, &j, &word_l);
	while (s[++i])
	{
		if (s[i] != c)
		{
			word_l++;
			if ((s[i + 1] == c) || (s[i + 1] == '\0'))
			{
				p_return[++j] = ft_word(i, &word_l, (char *)s);
				if (p_return[j] == NULL)
					return (NULL);
			}
		}
	}
	p_return[j + 1] = NULL;
	return (p_return);
}

static void	ft_set(int *i, int *j, int *word_l)
{
	*i = -1;
	*j = -1;
	*word_l = 0;
}

static char	*ft_word(int pos, int *word_l, char *s)
{
	int		k;
	char	*aux;

	aux = (char *) malloc((*word_l + 1) * sizeof(char));
	if (aux != NULL)
	{
		k = 0;
		while (k < *word_l)
		{
			aux[k] = s[pos - *word_l + 1 + k];
			k++;
		}
		aux[k] = '\0';
	}
	*word_l = 0;
	return (aux);
}

static	int	ft_word_num(char *s, char c)
{
	int	wc;
	int	i;

	if (s == NULL)
		return (-1);
	wc = 0;
	i = 0;
	while (s[i])
	{
		if (((s[i + 1] == c) || (s[i + 1] == '\0')) && (s[i] != c))
			wc++;
		i++;
	}
	wc++;
	return (wc);
}
