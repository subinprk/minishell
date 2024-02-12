/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:52:41 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/12 13:12:37 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TOK_WORD 1
# define TOK_PIPE 2
# define TOK_REDIRET 3
# define TOK_S_QUOTE 4
# define TOK_D_QUOTE 5
# define TOK_NULL_HANDLE 0

# define NODE_PIPE 1
# define NODE_CMD 2
# define NODE_SIMPLE_CMD 3
# define NODE_FILE_PATH 4
# define NODE_ARGV 5
# define NODE_REDIRECTS 6
# define NODE_SIMPLE_REDIRECT 7
# define NODE_RED_TYPE 8
# define NODE_FILE_NAME 9
# define NODE_NULL_HANDLE 0

# define REL_TYPE_R 1
# define REL_TYPE_RR 2
# define REL_TYPE_L 3
# define REL_TYPE_LL 4

# define _XOPEN_SOURCE 700

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>

# include "../libft/libft.h"

typedef struct s_cmd
{
	struct s_cmd	*left_child;
	struct s_cmd	*right_child;
	char				**cmdstr;
	int					node_type;
	int					pipe_exist;
	int					pre_flag;
}	t_cmd;

typedef struct s_stdio
{
	int				re_type;
	char			*filename;
	struct s_stdio	*next_stdio;
}	t_stdio;

typedef struct s_envp
{
	char	**envp;
	char	*cd_hist;
}	t_envp;

extern char	**g_envp;
extern int	g_exit_status;

//builtins

//cd
void    change_directory(char **paths, t_envp *env);

//echo
void	our_echo(char **av);
int	f_strchr(char *s, char c);
int	f_strcmp(char *s1, char *s2);


//env
void    ft_env(t_envp *args);
int	f_strlen(char *s);

//exit
void    exit_err(void);
void    exit_command(char **av);
//void    exit_command(t_cmd *cmd, char **cmdline);

//export
void    print_export(char **env);
int     is_valid_export_key(char *key);
void	add_export_variable(char *str, char **new, int i);
int		update_or_add_export(char *str, char ***env);
void    export(char **builtin, t_envp *env);

//pwd
char    *our_pwd(char **av, int pflag);

//unset
int 	is_valid_env_variable_name (char *str);
int		check_env_variable(char *key, char *env);
int 	unset_enviroment_variable(char *key, char ***env);
void    ft_unset(char *v_name, t_envp *env);

//tools
void	free_2d(char **arr);
void	free_stdios(t_stdio *stdios);
int		array_length_2d(char **array);
char	**paths_array(char **envp);
void	exec(char **cmd, char **env, t_envp *envo);
int		*token_data(char **chopped_str);
int		find_pipe(int *token, int *i);
int		find_redirection(int *token, int *i);
void	find_rellocator(char *str, int *i, int *count);
void	find_spaces(char *str, int *i, int *count);
char	*strdup_rellocator(char *str, int *i);
char	*strdup_word(char *str, int *i);
int		composing_word(char c);
int		count_word_length(char *str, int start);
char	**cpy_full_2d_array(char **origin);
char	**append_2d_array(char **origin, char *line);
char	**text_array_part_cpy(char **line, int start, int end);
int		how_many_token_id(int *token, int token_identifier);
int		token_length(int *token);
void	free_tree(t_cmd	*tree);
void	write_every_array(int filefd, char **array);

int		ft_strcmp(char *s1, char *s2);

//forks
int		redirect_type(t_cmd *node);
char	*command_path(char **path_array, int i, char *command);
char	*path_pointer(char **envp, char *command);
void	search_tree(t_cmd *node, char **envp, t_envp *env);
void	pipe_stdins(int *pipefd, t_stdio *stdios);
void	pipe_stdouts(int *pipefd, t_stdio *stdios);
void	print_error_cmd(t_cmd *file_path, char **envp);
int		check_builtin(t_cmd *file_path);
void	builtin_action(t_cmd *builtin, char **cmdline, t_envp *env);
void	update_pipefd(int pipefd[2], int old_input, int pipe_exist);
void	update_redirfd(t_stdio *stdios);
t_stdio	*find_last_in(t_stdio *stdios);
t_stdio	*find_last_out(t_stdio *stdios);
void	connect_last_out(t_stdio *last_out);
void	connect_last_in(t_stdio *last_in);
void	write_pipefd(int pipefd[2],int *old_input, int pipe_exist);
void	wait_each_commands(t_cmd *tree);
void	pid_zero_exec(t_cmd *cmd, char **envp, t_envp *env);
void	pid_pid_builtin(t_cmd *cmd, t_envp *env);
void	pid_pid_waiting(t_stdio **stdios);
int		red_error_handle(t_cmd *type, pid_t pid);

//parsing
char	**chopping_str(char *str);
t_cmd	*extract_command(char *str, t_envp *env);
int		*token_data(char **chopped_str);
int		syntax_pipe(char **cmd_line, int *token, int *i, t_cmd **node);
int		syntax_cmds(char **cmd_line, int *token, int *i, t_cmd **node);
int		syntax_simple_cmd(char **cmd_line, int *token, int *i, t_cmd **node);
int		syntax_redirects(char **cmd_line, int *token, int *i, t_cmd **node);
int		syntax_simple_redirect(char **cmd_line, /*int *token,*/ int *i, t_cmd **node);
t_cmd	*generate_tree_node(int node_type, int pipe_e);
t_cmd	*generate_end_node(char **line, int node_type, int start, int end);
void	replace_exit_status(char ***argv);

// get_envpath.c
char	**paths_array(char **envp);

// generate_prompt.c
void	generate_prompt(void);
int		read_from_stdin(char **buf);
void	get_line(char **line);

// utils.c
char	*ft_strnew(size_t size);
char	*get_env_value(char *key, char **envs);
int 	print_error(char *token, char *message);
int 	print_error2(char *token, char *token2, char *message);
void	print_id_error(char *token, char *message);

//utils2.c
int		remove_char(char *str, char c);
int		double_char_len(char **str);
int		is_stringdigit(char *str);
int     is_whitespace(char *c);

int		find_pipe(int *token, int *i);
int		find_redirection(int *token, int *i);
int		find_next_redirection(int *token, int *i);


// handle_signal.c
//void	set_signals_interactive(void);
//void	set_signals_noninteractive(void);
void	signal_reset_prompt(int signal);
void	set_signals_interactive(pid_t pid);
char    *print_prompt(void);
void	signal_parent_handle(void);

// ch_complete.c (FERDAWS)
char	**input_validation(char *tmp, char **env);
int	var_finder(char **env, char *s);

#endif
