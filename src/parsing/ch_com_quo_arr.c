/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_com_quo_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:20:15 by subpark           #+#    #+#             */
/*   Updated: 2024/02/12 15:54:05 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	quote_loop(char *str, char **sstr, int *i, int *k)
{
	while (str[*i])
	{
		if (str[*i] == '\'' && str[*i + 1] != '\'')
		{
			(*sstr)[*k] = str[*i];
			(*k)++;
			(*i)++;
		}
		else if (str[*i] == '\"' && str[*i + 1] != '\"')
		{
			(*sstr)[*k] = str[*i];
			(*i)++;
			(*k)++;
		}
		else
			(*i) = (*i) + 2;
	}
}

int	quo_arrangement(char *str)
{
	int		i;
	int		k;
	char	*sstr;

	i = 0;
	k = 0;
	sstr = NULL;
	sstr = malloc(strlen(str) * sizeof(char));
	quote_loop(str, &sstr, &i, &k);
	sstr[k] = '\0';
	if (ft_strlen(sstr) > 3 && sstr[0] == sstr[2] && sstr[0] != '\0')
	{
		free(sstr);
		return (-1);
	}
	if (sstr[0] != '\0' && quo_arrangement(sstr) == -1)
		free(sstr);
	return (-1);
	free(sstr);
	return (0);
}
