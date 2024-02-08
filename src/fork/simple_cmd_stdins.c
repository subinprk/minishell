/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_stdins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:54:07 by siun              #+#    #+#             */
/*   Updated: 2024/02/08 17:04:32 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_input(int filefd, char *word)
{
	char	*line;
	int		i;

	i = 0;
	line = ft_calloc(1,1);
	while (ft_strcmp(line, word) != 0)
	{
		free(line);
		line = readline("heredoc> ");
		if (!line)
			exit(1);
		if (ft_strcmp(line, word) != 0)
		{
			write(filefd, line, ft_strlen(line));
			write(filefd, "\n", 1);
		}
		i ++;
	}
	free(line);
}

void	re_type_l_pipes(int filefd)
{	
	int	fd_tmp;

	fd_tmp = dup2(filefd, 0);
	if (fd_tmp == -1)
	{
		close(filefd);
		exit(errno);
	}
}

void	connect_last_in(t_stdio *last_in)
{
	int	filefd;

	filefd = -1;
	if (last_in->re_type == REL_TYPE_L)
	{
		filefd = open(last_in->filename, O_RDONLY);
		if (!filefd)
			exit(errno);
		re_type_l_pipes(filefd);
	}
	else if (last_in->re_type == REL_TYPE_LL)
	{
		filefd = open(".___tmp__4heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (!filefd)
			exit(errno);
		heredoc_input(filefd, last_in->filename);
		close(filefd);
		filefd = open(".___tmp__4heredoc", O_RDONLY);
		re_type_l_pipes(filefd);
		//unlink()
	}
}

t_stdio	*find_last_in(t_stdio *stdios)
{
	t_stdio	*last_in;
	t_stdio	*curr;

	last_in = NULL;
	curr = stdios;
	while (curr)
	{
		if (curr->re_type == REL_TYPE_L || curr->re_type == REL_TYPE_LL)
			last_in = curr;
		curr = curr->next_stdio;
	}
	return (last_in);
}
