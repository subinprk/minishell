/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:07:25 by subpark           #+#    #+#             */
/*   Updated: 2024/01/08 16:54:09 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	write_pipefd(int (*pipefd)[2], int pipe_exist, int old_pipe[2], int new_pipe[2])
{
	if ((*pipefd)[0] == -1) //if there is no previous pipe
		(*pipefd)[0] = 0;
	else
	{
		(*pipefd)[0] = old_pipe[0];
		close(old_pipe[0]);
		close(old_pipe[1]);
	}
	if (pipe_exist == -1) // if there is no further pipe
	{
		(*pipefd)[1] = 1;
		close(new_pipe[0]);
		close(new_pipe[1]);
		(*pipefd)[0] = -1;
		(*pipefd)[1] = -1;
	}
	else
		(*pipefd)[1] = new_pipe[1];
}

void	update_pipefd(int (*pipefd)[2], int pipe_exist, int old_pipe[2], int new_pipe[2])
{
	close(new_pipe[0]);// anyway newpipe read is no useful after forked
	if ((*pipefd)[0] == -1) //if there is no previous pipe
		(*pipefd)[0] = 0;
	else
	{
		(*pipefd)[0] = dup2(old_pipe[0], 0);
		close(old_pipe[1]);
	}
	if (pipe_exist == -1) //if there is no further pipe
		close(new_pipe[1]);
	else
		(*pipefd)[1] = dup2(new_pipe[1], 1);
}

void	update_redirfd(int *pipefd, t_stdio *stdios)
{
	t_stdio	*last_in;
	t_stdio *last_out;
	int		pipe_tmp[2];

	if (stdios == NULL)
		return ;
	pipe_tmp[0] = pipefd[0];
	pipe_tmp[1] = pipefd[1];
	last_in = find_last_in(stdios);
	last_out = find_last_out(stdios);
	if (last_in != NULL)
	{
		connect_last_in(pipefd[0], last_in);
		close(pipe_tmp[0]);
	}
	if (last_out != NULL)
	{
		connect_last_out(pipefd[1], last_out);
		close(pipe_tmp[1]);
	}
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