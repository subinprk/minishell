/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:52:41 by irivero-          #+#    #+#             */
/*   Updated: 2024/02/12 15:11:42 by subpark          ###   ########.fr       */
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
	struct s_cmd		*left_child;
	struct s_cmd		*right_child;
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

typedef struct s_data
{
	int		word_count;
	int		sqn;
	int		dqn;
	char	**array;
	char	*tmp;
}	t_data;

extern int	g_exit_status;

//builtins

//cd
void	change_directory(char **paths, t_envp *env);

//echo
void	our_echo(char **av);
int		f_strchr(char *s, char c);
int		f_strcmp(char *s1, char *s2);

//env
void	ft_env(t_envp *args);
int		f_strlen(char *s);

//exit
void	exit_command(char **av);

//export
void	export(char **builtin, t_envp *env);

//pwd
char	*our_pwd(char **av, int pflag);

//unset
void	ft_unset(char *v_name, t_envp *env);

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
void	print_error_cmd(t_cmd *file_path, char **envp);
int		check_builtin(t_cmd *file_path);
void	builtin_action(t_cmd *builtin, char **cmdline, t_envp *env);
void	update_pipefd(int pipefd[2], int old_input, int pipe_exist);
void	update_redirfd(t_stdio *stdios);
t_stdio	*find_last_in(t_stdio *stdios);
t_stdio	*find_last_out(t_stdio *stdios);
void	connect_last_out(t_stdio *last_out);
void	connect_last_in(t_stdio *last_in);
void	write_pipefd(int pipefd[2], int *old_input, int pipe_exist);
void	wait_each_commands(t_cmd *tree);
void	pid_zero_exec(t_cmd *cmd, char **envp, t_envp *env);
void	pid_pid_builtin_n_set(t_cmd *cmd, t_envp *env);
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
int		syntax_simple_redirect(char **cmd_line, int *i, t_cmd **node);
t_cmd	*generate_tree_node(int node_type, int pipe_e);
t_cmd	*generate_end_node(char **line, int node_type, int start, int end);
void	replace_exit_status(char ***argv, int i, int flag, int j);
void	syntax_pipe_error_print(void);
void	syntax_pipe_i_update(int *i, int pipe_index, int tmp);

// get_envpath.c
char	**paths_array(char **envp);

int		find_pipe(int *token, int *i);
int		find_redirection(int *token, int *i);
int		find_next_redirection(int *token, int *i);

void	signal_reset_prompt(int signal);
void	set_signals_interactive(pid_t pid);
char	*print_prompt(void);
void	signal_parent_handle(void);

// ch_complete.c
int		if_tmp_null(t_data *data, char *tmp, int i, int k);
int		ft_chopper(t_data *data, char *tmp, int k);
void	else_if_str(int *inquotes, int *count, int *inword);
int		word_counter(const char *str, int count, int inword, int inquotes);
char	**input_validation(char *tmp, char **env);

// ch_com_expan
int		expansion(t_data *data, char **env, int i);
void	single_quote_case(t_data *data, int i);
char	*str_quo_modifier(char *str);
int		var_finder(char **env, char *s);
char	*str_modifier(char *str, char *var, int d);

// ch_complete2.c
int		quo_num(char *tmp, t_data *data);
int		if_sstr_zero(char *sstr);
int		quo_arrangement(char *str, int i);
int		quo_order(char *tmp, t_data *data, int i, int k);
int		ft_strcpy(t_data *data, char *tmp, int len, int k);

// ch_complete3.c
char	*ifhelper(t_data *data, char *tmp, int i, int k);
char	*elsehelper(t_data *data, char *tmp, int i, int k);
void	while_function(char *tmp, int *i);
char	*status_ret(void);

#endif
