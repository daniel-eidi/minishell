/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 19:08:58 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/10 19:10:07 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_TABLE_H
# define HASH_TABLE_H

# ifndef P_PARAM
#  define P_PARAM 31
# endif

# ifndef M_PARAM
#  define M_PARAM 1000000007
# endif

# include <stddef.h>
# include <stdlib.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_item
{
	char	*key;
	char	*value;
}	t_item;

//------------list functions------------
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));
//----------hashtable functions----------
unsigned long	ft_pow(int base, int exp);
size_t			ft_strlen(const char *s);
int				get_ind(char *key, t_list **table);
t_list			**hash_table_init(int size);
void			insert_item(t_item *item, t_list **table);
t_item			*new_item(char *new_key, char *new_value);
t_list			*find_entry(char *searched_key, t_list **table);
int				ft_strcmp(char *s1, char *s2);
void			delete_entry(char *searched_key, t_list **table);
void			clear_table(t_list **table);

#endif
