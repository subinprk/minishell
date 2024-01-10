/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 21:07:25 by subpark           #+#    #+#             */
/*   Updated: 2024/01/10 18:30:48 by subpark          ###   ########.fr       */
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
	}
	if (pipe_exist == -1) // if there is no further pipe
	{
		close(new_pipe[0]);
		(*pipefd)[0] = -1;
		(*pipefd)[1] = -1;
	}
	else
		(*pipefd)[1] = new_pipe[1];
	close(new_pipe[1]);
}

void	update_pipefd(int (*pipefd)[2], int pipe_exist, int old_pipe[2], int new_pipe[2])
{
	close(new_pipe[0]);// anyway newpipe read is no useful after forked
	if ((*pipefd)[0] == -1) //if there is no previous pipe
		(*pipefd)[0] = 0;
	else
		(*pipefd)[0] = dup2(old_pipe[0], 0);
	if (pipe_exist == -1) //if there is no further pipe
		close(new_pipe[1]);
	else
		(*pipefd)[1] = dup2(new_pipe[1], 1);
}

void	update_redirfd(int *pipefd, t_stdio *stdios)
{
	t_stdio	*last_in;
	t_stdio *last_out;

	if (stdios == NULL)
		return ;
	last_in = find_last_in(stdios);
	last_out = find_last_out(stdios);
	if (last_in != NULL)
		connect_last_in(pipefd[0], last_in);
	if (last_out != NULL)
		connect_last_out(pipefd[1], last_out);
}
