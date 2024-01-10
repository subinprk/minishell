/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_tree_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:53:44 by subpark           #+#    #+#             */
/*   Updated: 2024/01/10 13:13:01 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	red_error_handle(t_cmd *type)
{
	if (type->cmdstr[0][0] == '<' || type->cmdstr[0][0] =='>')
	{
		g_exit_status = 0;
		exit (g_exit_status);
	}
	else
		return ;
}

void	execute_simple_cmd(t_cmd *cmd, t_stdio **stdios, char **envp)
{
	static int		pipefd[2] = {-1, -1};
	static int		new_pipe[2];
	int				old_pipe[2];
	pid_t			pid;

	if (pipefd[0] != -1) //for excepting the case of first time
	{
		old_pipe[0] = dup(new_pipe[0]);
		close(new_pipe[0]);
	}
	if (pipe(new_pipe) == -1)
		return (perror("Pipe: "));//exit with signals
	pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	else if (pid == 0)
	{
		update_pipefd(&pipefd, cmd->pipe_exist, old_pipe, new_pipe);
		update_redirfd(pipefd, *stdios);
		if (check_builtin(cmd->left_child))
		{
			builtin_action(cmd->right_child, cmd->right_child->cmdstr);
			//if builtin action return 0 meanin successful, if that case, g_exit status become 0
			//so have to modificate builtin action function to return int.
			exit(errno);
		}
		else
		{
			red_error_handle(cmd->left_child);
	 		print_error_cmd(cmd->left_child, envp);
			exec(cmd->right_child->cmdstr, envp);
		}
	}
	else
	{
		write_pipefd(&pipefd, cmd->pipe_exist, old_pipe, new_pipe);
		waitpid(-1, &g_exit_status, WNOHANG);
		free_stdios(*stdios);
		*stdios = NULL;
	}
}

void	execute_simple_redirect(t_cmd *node, t_stdio **stdios)
{
	t_stdio	*redirection;
	t_stdio *curr;

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

void	execute_tree(t_cmd *node, t_stdio **stdios, char **envp)
{
	if (node->node_type == NODE_CMD || node->node_type == NODE_REDIRECTS)
		return ;
	else if (node->node_type == NODE_PIPE)
		;
	else if (node->node_type == NODE_SIMPLE_CMD)
		execute_simple_cmd(node, stdios, envp);
	else if (node->node_type == NODE_SIMPLE_REDIRECT)
		execute_simple_redirect(node, stdios);
}

void	search_tree(t_cmd *node, char **envp)
{
	static t_stdio	*stdios;

	if (node == NULL)
		return ;
	execute_tree(node, &stdios, envp);
	if (node->left_child && (node->left_child->node_type != NODE_RED_TYPE ||
		node->left_child->node_type != NODE_FILE_PATH))
		search_tree(node->left_child, envp);
	if (node->right_child && (node->right_child->node_type != NODE_FILE_NAME ||
		node->right_child->node_type != NODE_ARGV))
		search_tree(node->right_child, envp);
}