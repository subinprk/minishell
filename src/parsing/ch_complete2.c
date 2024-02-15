/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_complete2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:19:12 by ftemori           #+#    #+#             */
/*   Updated: 2024/02/14 19:19:15 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	quo_num(char *tmp, t_data *data)
{
	int	i;
	int	s;
	int	d;

	i = 0;
	s = 0;
	d = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\'')
			s++;
		if (tmp[i] == '\"')
			d++;
		i++;
	}
	if ((s % 2 == 0 || s == 0) && (d % 2 == 0 || d == 0))
	{
		data->sqn = s;
		data->dqn = d;
		return (s);
	}
	return (-1);
}

int	if_sstr_zero(char *sstr)
{
	if (sstr[0] != '\0')
	{
		if (quo_arrangement(sstr, 0) == -1)
		{
			free(sstr);
			return (-1);
		}
	}
	return (0);
}

int	quo_arrangement(char *str, int i)
{
	int		k;
	char	*sstr;

	k = 0;
	sstr = malloc(f_strlen(str) * sizeof(char));
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] != '\'')
			sstr[k++] = str[i++];
		else if (str[i] == '\"' && str[i + 1] != '\"')
			sstr[k++] = str[i++];
		else
			i += 2;
	}
	sstr[k] = '\0';
	if (strlen(sstr) > 3 && sstr[0] == sstr[2] && sstr[0] != '\0')
	{
		free(sstr);
		return (-1);
	}
	if (if_sstr_zero(sstr) == -1)
		return (-1);
	free(sstr);
	return (0);
}

int	quo_order(char *tmp, t_data *data, int i, int k)
{
	char	*q_string;

	q_string = malloc((data->sqn + data->dqn + 1) * sizeof(char));
	while (tmp[i])
	{
		if (tmp[i] == '\'')
		{
			q_string[k] = '\'';
			k++;
		}
		if (tmp[i] == '\"')
		{
			q_string[k] = '\"';
			k++;
		}
		i++;
	}
	q_string[k] = '\0';
	if (quo_arrangement(q_string, 0) == -1)
	{
		free(q_string);
		return (-1);
	}
	free(q_string);
	return (0);
}

int	ft_strcpy(t_data *data, char *tmp, int len, int k)
{
	int	i;

	i = 0;
	data->array[k] = malloc((len + 1) * sizeof(char));
	if (!data->array[k])
		return (-1);
	while (i < len)
	{
		data->array[k][i] = tmp[i];
		i++;
	}
	data->array[k][i] = '\0';
	return (len);
}
