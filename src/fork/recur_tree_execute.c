/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recur_tree_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:53:44 by subpark           #+#    #+#             */
/*   Updated: 2024/02/08 16:20:40 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	red_error_handle(t_cmd *type, pid_t pid)
{
	if (type->cmdstr[0][0] == '<' || type->cmdstr[0][0] =='>')
	{
		g_exit_status = 0;
		if (pid == 0)
			exit (g_exit_status);
		else
			return (1);
	}
	else
		return(0);
}

void	execute_simple_cmd(t_cmd *cmd, t_stdio **stdios, char **envp, t_envp *env)
{
	// static int		pipefd[2] = {-1, -1};
	// static int		new_pipe[2];
	// int				old_pipe[2];
	int				pipefd[2];
	static int		old_input = -1;
	pid_t			pid;

	// if (pipefd[0] != -1) //for excepting the case of first time
	// {
	// 	old_pipe[0] = dup(new_pipe[0]);
	// 	close(new_pipe[0]);
	// }
	if (pipe(pipefd) == -1)
		return (perror("Pipe: "));//exit with signals
	pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	else if (pid == 0)
	{
		set_signals_interactive(pid);
		update_redirfd(*stdios);
		update_pipefd(pipefd, old_input, cmd->pipe_exist);
		if (check_builtin(cmd->left_child))
		{
			builtin_action(cmd->right_child, cmd->right_child->cmdstr, env);
			//if builtin action return 0 meanin successful, if that case, g_exit status become 0
			//so have to modificate builtin action function to return int.
			exit(errno);
		}
		else
		{
			red_error_handle(cmd->left_child, pid);
	 		print_error_cmd(cmd->left_child, envp);
			exec(cmd->right_child->cmdstr, envp);
		}
	}
	else
	{
		set_signals_interactive(pid);
		if (red_error_handle(cmd->left_child, pid))
			return ;
		if (!ft_strcmp(cmd->right_child->cmdstr[0], "exit"))
			exit_command(cmd->right_child->cmdstr);
		else if (!ft_strcmp(cmd->right_child->cmdstr[0], "unset"))
			ft_unset(cmd->right_child->cmdstr[1], env);
		else if (!ft_strcmp(cmd->right_child->cmdstr[0], "export"))
			export(cmd->right_child->cmdstr + 1, env);
		else if (!ft_strcmp(cmd->right_child->cmdstr[0], "cd"))
			change_directory(cmd->right_child->cmdstr, env);
		write_pipefd(pipefd, &old_input, cmd->pipe_exist);
		waitpid(-1, &g_exit_status, WNOHANG);
		if (find_last_in(*(stdios))!= NULL && find_last_in(*(stdios))->re_type == REL_TYPE_LL)
			waitpid(-1, &g_exit_status, 0);
		else
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
	if (node->left_child && (node->left_child->node_type != NODE_RED_TYPE ||
		node->left_child->node_type != NODE_FILE_PATH))
		search_tree(node->left_child, envp, env);
	if (node->right_child && (node->right_child->node_type != NODE_FILE_NAME ||
		node->right_child->node_type != NODE_ARGV))
		search_tree(node->right_child, envp, env);
}