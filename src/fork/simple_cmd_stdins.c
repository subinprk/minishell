/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_stdins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 23:54:07 by siun              #+#    #+#             */
/*   Updated: 2024/01/12 16:31:32 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	heredoc_input(/*int filefd, */char *word)
{
	char	*line;
	char	**text;
	int		i;

	i = 0;
	text = NULL;
	line = readline("heredoc> ");
	if (!line)
		exit(1);
	while (ft_strcmp(line, word) != 0)
	{
		text = append_2d_array(text, line);
		free(line);
		line = readline("heredoc> ");
		printf("%s", text[i]);
		i ++;
	}
	free(line);
	//printf("before using that function: %s", text[0]);
	write_every_array(text);
	free_2d(text);
}

void	re_type_l_pipes(int filefd, int pipe_in)
{	
	int	fd_tmp;

	fd_tmp = dup2(filefd, 0);
	if (fd_tmp == -1)
	{
		close(filefd);
		close(pipe_in);
		exit(errno);
	}
}

void	connect_last_in(int pipe_in, t_stdio *last_in)
{
	int	filefd;

	filefd = -1;
	if (last_in->re_type == REL_TYPE_L)
	{
		filefd = open(last_in->filename, O_RDONLY);
		if (!filefd)
			exit(errno);
		re_type_l_pipes(filefd, pipe_in);
	}
	else if (last_in->re_type == REL_TYPE_LL)//have to make heredoc
	{
	//	filefd = open(".___tmp__4heredoc", O_CREAT | O_RDWR, 0666);//making tmp file
	//	if (!filefd)
	//		exit(errno);
		heredoc_input(/*&filefd,*/ last_in->filename);
	//	re_type_l_pipes(filefd, pipe_in);///have to remove tmp file, have to think about it later
		//unlink()
	}
	//if (filefd == -1)
	//	close(filefd);
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

// void	pipe_stdins(int *pipefd, t_stdio *stdios)
// {
// 	t_stdio	*last_in;
// 	t_stdio	*curr;

// 	last_in = NULL;
// 	curr = stdios;
// 	while (curr)
// 	{
// 		if (curr->re_type == REL_TYPE_L || curr->re_type == REL_TYPE_LL)
// 			last_in = curr;
// 		curr = curr->next_stdio;
// 	}
// 	if (last_in != NULL)
// 		connect_stdins(last_in, pipefd);
// 	else
// 		return ;//useless, but afraid to remove pipefd parameter...
// }
