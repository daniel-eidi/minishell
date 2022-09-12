/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:32:00 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/01 13:21:46 by daeidi-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// -----------------	ALLOWED LIBS	----------------
# include <stdio.h>				// printf()
# include <readline/readline.h>	// readline(), etc.
# include <readline/history.h>	// add_history()
# include <unistd.h>			// write(), close(), access(), fork(), pipe()
# include <stdlib.h>			// free()
# include <stdbool.h>			// C99+ standard <bool> typedef
# include <fcntl.h>				// open()
# include <dirent.h>			// opendir(), closedir(), readdir()
# include <sys/stat.h>			// stat(), fstat(), lstat()
# include <sys/types.h>			// stat(), fstat(), lstat()
# include <sys/types.h>			// <pid_t> typedef
# include <sys/wait.h>			// wait()
# include <signal.h>			// sigaction()

//----------------- command table (moacir) -----------------

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_cmd
{
	t_list	*cmd;
	t_list	*infiles;
	t_list	*outfiles;
	char	*errfile;
}	t_cmd;

t_list	**make_cmd_table(char **words);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstclear(t_list **lst, void (*del)(void *));
int	ft_strcmp(char *s1, char *s2);
void	clear_cmd(t_cmd *cmd_deleted);
void	clear_cmd_table(t_list **cmd_table);

/*
** My own libft library, completed with previously implemented functions such as
** get_next_line
*/
# include "../libft/libft.h"
void	error(void);
char	*ft_get_next_line_lim(int fd, char *limiter);
void	free_ptr(char **str);
char	*treat_line(char *cmd);
char	*space_arg(char *cmd, char *c);

#endif
