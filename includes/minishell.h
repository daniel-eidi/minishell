/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaldino <mgaldino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 22:32:00 by daeidi-h          #+#    #+#             */
/*   Updated: 2022/10/13 16:04:43 by mgaldino         ###   ########.fr       */
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

# include "../libft/libft.h"
# include <hash_table.h>

void	process_quotes(char *line);
void	process_quotes2(char *line);
char	**token_line(char *line);
char	*exp_var(char *s, t_list **table);

typedef struct s_pids_pipes
{
	int		**pipes;
	pid_t	*pids;
	int		total_cmd;
}	t_pids_pipes;

typedef struct s_cmd
{
	char	**cmd_and_args;
	char	**redirections;
}	t_cmd;

typedef struct s_data
{
	struct s_list	**hash_table;
	int				exit_code;
	t_pids_pipes	*aux;
	t_cmd			*global_table;
	char			**main_cmd;
}	t_data;
extern t_data	*g_data;
t_data	*init_data(void);

int		invalid_syntax_redir(char *str);
t_cmd	*make_cmd_table(char *line);
void	clear_cmd_table(t_cmd *table);
void	hash_envp(t_data *data, char **envp);
void	print_array(char **array);
void	clear_data(void);
void	exit_minishell(t_cmd *cmd_table, t_pids_pipes *aux);
void	free_pids_and_pipes(t_pids_pipes *aux);
void	free_and_exit(t_pids_pipes *aux);
char	*ft_get_next_line_lim(int fd, char *limiter);
char	*find_absolute_path(char *path);
int		get_absolute_path(char **cmd, int i, char **absolute_path);
void	set_absolute_path_with_home_value(char **absolute_path);
void	back_old_pwd(char **absolute_path);
void	cd_many_args_msg(void);
void	go_up_one_dir(char *path);
char	*go_down_to_dir(char *path, char *dir);
void	restore_char(char **exec_args, char find, char change);
char	*ft_get_next_line_lim(int fd, char *limiter);
void	free_ptr(void **ptr);
void	free_split(void **ptr);
char	*treat_line(char *cmd);
char	*ft_strnjoin(char *s1, char *s2, int x);
char	*get_var_value(char *key);
void	update_hashtable(char *key, void *new_value, t_list	**hash_table);

/// ----------------builtins-----

void	builtin_echo(char **cmd);
void	builtin_pwd(void);
void	builtin_cd(char **cmd);
void	builtin_env(void);
void	builtin_export(char **cmd);
void	builtin_unset(char **cmd);
int		is_builtin(char	**cmd);
void	run_builtin(t_cmd *cmd_table, t_pids_pipes *aux);
void	run_builtin_fork(t_cmd *cmd_table, t_pids_pipes *aux);

// ------ fork

void	before_fork(char **cmd, t_pids_pipes **pid_pipe);
void	fork_open_exec(char **cmd, int n_cmd, t_pids_pipes *pid_pipe);
void	after_fork(int n_cmd, int **pipes, pid_t *pid);
void	open_fds(char **redir, t_pids_pipes *aux, int n_cmd, int *have_file);
void	open_fdsfrk(char **redir, t_pids_pipes *aux, int n_cmd, int *have_file);
void	free_data_after_exec_cmd(char **environ);

// ---utils fork_exec

void	free_cmd_and_close_pipes(char **cmd, int n_cmd, t_pids_pipes *aux);
void	if_absolute_path(t_list *temp, char **environ, char **args, \
						char **cmd_path);
int		**create_pipes(int n_cmd);
void	close_pipes(int n_cmd, int **pipes, int i);
void	close_pipes_main(int n_cmd, int **pipes);
pid_t	*create_pids(int n_cmd);
char	*get_path(char **cmd, const char *path);
int		open_ok(char *file, int flag, int inout);
int		open_ok_fork(char *file_str, int flag, int inout);
void	error(const char *s, int i);
void	error_fork(const char *s, int i);

// --- signals

void	signal_for_child(void);
void	signal_for_main(void);
void	ctrlc_fork(int signal);

//--- teste heredoc
void	prepare_heredoc(char **cmds);

#endif
