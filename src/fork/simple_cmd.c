/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:07:25 by subpark           #+#    #+#             */
/*   Updated: 2024/02/08 13:41:26 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pipefd(int pipefd[2],int old_input, int pipe_exist)
{
	close(pipefd[0]);
	if (old_input != -1) //if there is previous pipe
		(dup2(old_input, 0));
	if (pipe_exist == -1) // if there is no further pipe
	{
		close(pipefd[1]);
		close(old_input);
	}
	else
		dup2(pipefd[1], 1);
}

void	write_pipefd(int pipefd[2], int *old_input, int pipe_exist)
{
	close(pipefd[1]);
	if (*old_input != -1)
		close(*old_input);
	if (pipe_exist == -1)
	{
		close(pipefd[0]);
		*old_input = -1;
	}
	else
		*old_input = pipefd[0];
}

void	update_redirfd(t_stdio *stdios)
{
	t_stdio	*last_in;
	t_stdio *last_out;

	if (stdios == NULL)
		return ;
	last_in = find_last_in(stdios);
	last_out = find_last_out(stdios);
	if (last_in != NULL)
		connect_last_in(last_in);
	if (last_out != NULL)
		connect_last_out(last_out);
}

// void	simple_cmd_action(t_cmd *cmd, int *pipefd, char **envp)
// {
// 	int	builtin;

// 	builtin = check_builtin(cmd->left_child);
// 	if (builtin)
// 		builtin_action(cmd->right_child, cmd->right_child->cmdstr);
// 	else
// 		exec(cmd->right_child->cmdstr, envp);
// }

// void	pipe_pipe(t_cmd *cmd, int *pipefd, t_stdio *stdios, char **envp)
// {
// 	pid_t	pid;

// 	// if (pipe(pipefd) == -1)
// 	// 	return (perror("Pipe: "));
// 	pid = fork();
// 	if (pid < 0)
// 		return (perror("Fork: "));
// 	else if (pid == 0)
// 	{
// 		//close(pipefd[0]);
// 		dup2(pipefd[1], 1);
// 		simple_cmd_action(cmd, pipefd, stdios, envp);
// 	}
// 	else
// 	{
// 		//close(pipefd[1]);
// 		dup2(pipefd[0], 0);
// 		waitpid(pid, NULL, WNOHANG);
// 	}
// }

// void	pipe_end(t_cmd *cmd, int *pipefd, t_stdio *stdios, char **envp)
// {
// 	pid_t	pid;

// 	// if (pipe(pipefd) == -1)
// 	// 	return (perror("Pipe: "));
// 	pid = fork();
// 	if (pid < 0)
// 		return (perror("Fork: "));
// 	else if (pid == 0)
// 	{
// 		//close(pipefd[0]);
// 		//close(pipefd[1]);
// 		simple_cmd_action(cmd, pipefd, stdios, envp);
// 	}
// 	else
// 	{
// 		close(pipefd[1]);
// 		dup2(pipefd[0], 0);
// 		waitpid(pid, NULL, WNOHANG);
// 	}
// }