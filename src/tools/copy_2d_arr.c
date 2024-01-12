/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_2d_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 17:32:20 by siun              #+#    #+#             */
/*   Updated: 2024/01/12 18:11:51 by subpark          ###   ########.fr       */
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
	printf("array length : %d\n", array_length);
	tmp = (char **)malloc(sizeof(char *) * (array_length) + 2);
	i = 0;
	while (origin[i] != NULL)
	{
		tmp[i] = ft_strdup(origin[i]);
		printf("%d times happening inside\n", i);
		i ++;
	}
	tmp[i] = ft_strdup(line);
	tmp[array_length + 1] = NULL;
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

void	write_every_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("%s", array[i]);
		i ++;
	}
}