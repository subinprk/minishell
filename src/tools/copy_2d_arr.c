/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_2d_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:32:20 by siun              #+#    #+#             */
/*   Updated: 2024/02/04 00:27:39 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**cpy_full_2d_array(char **origin)
{
	int		i;
	int		origin_length;
	char	**array;

	if (origin == NULL)
		return (NULL);
	array = NULL;
	origin_length = array_length_2d(origin);
	array = (char **)malloc(sizeof(char *) * ((origin_length) + 1));
	if (!array)
		exit(errno);
	i = 0;
	while(i < origin_length)
	{
		array[i] = ft_strdup(origin[i]);
		if (!array[i])
			exit(errno);
		i ++;
	}
	free_2d(origin);
	array[origin_length] = NULL;
	return (array);
}

char	**append_2d_array(char **origin, char *line)
{
	int		i;
	int		array_length;
	char	**tmp;

	array_length = array_length_2d(origin);
	tmp = (char **)malloc(sizeof(char *) * (array_length + 2));
	i = 0;
	while (origin != NULL && origin[i] != NULL)
	{
		tmp[i] = strdup(origin[i]);
		i ++;
	}
	tmp[i] = strdup(line);
	tmp[array_length + 1] = NULL;
	if (origin)
		free_2d(origin);
	return (tmp);
}

char	**text_array_part_cpy(char **line, int start, int end)
{
	int		i;
	char	**part;

	part = (char **)malloc((sizeof(char *)) * (end - start + 1));
	if (!part)
		exit(errno);
	i = 0;
	while (i < end - start)
	{
		part[i] = ft_strdup(line[start + i]);
		if (!part[i])
			exit(errno);
		i ++;
	}
	part[i] = NULL;
	return (part);
}

void	write_every_array(int filefd, char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		write(filefd, array[i], ft_strlen(array[i]));
		write(filefd, "\n", 1);
		i ++;
	}
}