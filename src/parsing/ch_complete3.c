/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_complete3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:22:13 by ftemori           #+#    #+#             */
/*   Updated: 2024/02/14 19:22:14 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ifhelper(t_data *data, char *tmp, int i, int k)
{
	int	m;

	m = i;
	while (tmp[i] != '\'' && tmp[i] != '\0')
		i++;
	ft_strcpy(data, tmp + m - 1, i + 1, k);
	i++;
	tmp = tmp + i;
	return (tmp);
}

char	*elsehelper(t_data *data, char *tmp, int i, int k)
{
	int	m;

	m = i;
	while (tmp[i] != '\"' && tmp[i] != '\0')
		i++;
	ft_strcpy(data, tmp + m, i - 1, k);
	i++;
	tmp = tmp + i;
	return (tmp);
}

void	while_function(char *tmp, int *i)
{
	while (tmp[*i] != '\0' && tmp[*i] != ' ' && tmp[*i] != '='
		&& tmp[*i] != '\"' && tmp[*i] != '\''
		&& tmp[*i] != '<' && tmp[*i] != '>' && tmp[*i] != '|')
		*i += 1;
}
