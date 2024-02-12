/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_pid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:44:33 by subpark           #+#    #+#             */
/*   Updated: 2024/02/12 13:12:30 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	pid_zero_setting(t_cmd *cmd, int pipefd[2], int old_input, char **g_envp
// 		, t_envp *env)
// {

// }

void	pid_zero_exec(t_cmd *cmd, char **envp, t_envp *env)
{
	if (check_builtin(cmd->left_child))
			builtin_action(cmd->right_child, cmd->right_child->cmdstr, env);
	else
	{
		red_error_handle(cmd->left_child, 0);
		print_error_cmd(cmd->left_child, envp);
		exec(cmd->right_child->cmdstr, envp, env);
	}
}

void	pid_pid_builtin(t_cmd *cmd, t_envp *env)
{
	if (!ft_strcmp(cmd->right_child->cmdstr[0], "exit"))
		exit_command(cmd->right_child->cmdstr);
	else if (!ft_strcmp(cmd->right_child->cmdstr[0], "unset"))
		ft_unset(cmd->right_child->cmdstr[1], env);
	else if (!ft_strcmp(cmd->right_child->cmdstr[0], "export"))
		export(cmd->right_child->cmdstr + 1, env);
	else if (!ft_strcmp(cmd->right_child->cmdstr[0], "cd"))
		change_directory(cmd->right_child->cmdstr, env);
}

void	pid_pid_waiting(t_stdio **stdios)
{
	waitpid(-1, &g_exit_status, WNOHANG);
	if (find_last_in(*(stdios))!= NULL && find_last_in(*(stdios))->re_type == REL_TYPE_LL)
		waitpid(-1, &g_exit_status, 0);
	else
		free_stdios(*stdios);
}