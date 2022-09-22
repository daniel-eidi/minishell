/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeidi-h <daeidi-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:32:00 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/09/21 22:30:57 by daeidi-h         ###   ########.fr       */
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


# include <hash_table.h>


void	process_quotes(char *line);
void	process_quotes2(char *line);
char	**token_line(char *line);
char	*exp_var(char *s, t_list **table);


typedef struct s_data
{
    struct s_list    **hash_table;
	int				exit_code;
}    t_data;
extern t_data	*g_data;
t_data *init_data(void);

typedef struct s_cmd
{
	t_list	*cmd;
	t_list	*infiles;
	t_list	*outfiles;
	char	*errfile;
}	t_cmd;
t_list	**make_cmd_table(char **words);
void	clear_cmd_table(t_list **cmd_table);

void	hash_envp(t_data *data, char **envp);


/*
** My own libft library, completed with previously implemented functions such as
** get_next_line
*/
# include "../libft/libft.h"
void	error(void);
char	*ft_get_next_line_lim(int fd, char *limiter);
void	free_ptr(void **ptr);
void	free_split(void **ptr);
char	*treat_line(char *cmd);
char	*ft_strnjoin(char *s1, char *s2, int x);

/// ----------------builtins-----

void	builtin_echo(t_list *cmd);
void	builtin_pwd(void);
void	update_hashtable(char *key, void *new_value, t_list	**hash_table);
void	builtin_cd(t_list *cmd);
void	builtin_env(t_data *data);


#endif
