/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_tree_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:53:44 by subpark           #+#    #+#             */
/*   Updated: 2024/02/12 14:30:46 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	red_error_handle(t_cmd *type, pid_t pid)
{
	if (type->cmdstr[0][0] == '<' || type->cmdstr[0][0] == '>')
	{
		g_exit_status = 0;
		if (pid == 0)
			exit (g_exit_status);
		else
			return (1);
	}
	else
		return (0);
}

void	execute_simple_cmd(t_cmd *cmd, t_stdio **stdios, char **envp
		, t_envp *env)
{
	int				pipefd[2];
	static int		old_input = -1;
	pid_t			pid;

	if (pipe(pipefd) == -1)
		return (perror("Pipe: "));
	pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	else if (pid == 0)
	{
		set_signals_interactive(pid);
		update_redirfd(*stdios);
		update_pipefd(pipefd, old_input, cmd->pipe_exist);
		pid_zero_exec(cmd, envp, env);
	}
	else
	{
		pid_pid_builtin_n_set(cmd, env);
		write_pipefd(pipefd, &old_input, cmd->pipe_exist);
		pid_pid_waiting(stdios);
	}
}

void	execute_simple_redirect(t_cmd *node, t_stdio **stdios)
{
	t_stdio	*redirection;
	t_stdio	*curr;

	redirection = (t_stdio *)malloc(sizeof(t_stdio));
	if (*stdios == NULL)
	{
		redirection->filename = node->right_child->cmdstr[0];
		redirection->re_type = redirect_type(node->left_child);
		redirection->next_stdio = NULL;
		*stdios = redirection;
	}
	else
	{
		redirection->filename = node->right_child->cmdstr[0];
		redirection->re_type = redirect_type(node->left_child);
		redirection->next_stdio = NULL;
		curr = *stdios;
		while (curr->next_stdio)
			curr = curr->next_stdio;
		curr->next_stdio = redirection;
	}
}

void	execute_tree(t_cmd *node, t_stdio **stdios, char **envp, t_envp *envs)
{
	if (node->node_type == NODE_CMD || node->node_type == NODE_REDIRECTS)
		return ;
	else if (node->node_type == NODE_PIPE)
		;
	else if (node->node_type == NODE_SIMPLE_CMD)
		execute_simple_cmd(node, stdios, envp, envs);
	else if (node->node_type == NODE_SIMPLE_REDIRECT)
		execute_simple_redirect(node, stdios);
}

void	search_tree(t_cmd *node, char **envp, t_envp *env)
{
	static t_stdio	*stdios;

	if (node == NULL)
		return ;
	execute_tree(node, &stdios, envp, env);
	if (node->left_child && (node->left_child->node_type != NODE_RED_TYPE
			|| node->left_child->node_type != NODE_FILE_PATH))
		search_tree(node->left_child, envp, env);
	if (node->right_child && (node->right_child->node_type != NODE_FILE_NAME
			|| node->right_child->node_type != NODE_ARGV))
		search_tree(node->right_child, envp, env);
}
