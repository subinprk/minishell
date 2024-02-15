/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_com_expan.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:42:43 by subpark           #+#    #+#             */
/*   Updated: 2024/02/12 15:57:11 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*str_modifier(char *str, char *var, int d)
{
	int		eq;
	int		i;
	char	*tmp;

	i = 0;
	eq = f_strchr(var, '=') + 1;
	tmp = malloc((f_strlen(var + eq) + d + 1) * sizeof(char));
	while (i < d)
	{
		tmp[i] = str[i];
		i++;
	}
	while (var[eq] != '\0')
	{
		tmp[i] = var[eq];
		i++;
		eq++;
	}
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

int	var_finder(char **env, char *s)
{
	int	i;

	i = 0;
	if (!*s)
		return (-1);
	while (env[i] != NULL)
	{
		if (f_strcmp(env[i], s) != -1)
			return (i); 
		i++;
	}
	return (-1);
}

char	*str_quo_modifier(char *str)
{
	int		k;
	int		i;
	char	*tmp;

	i = 0;
	k = f_strlen(str);
	tmp = malloc((k - 1) * sizeof(char));
	str[k - 1] = '\0';
	while (str[i] != '\0')
	{
		tmp[i] = str[i + 1];
		i++;
	}
	free(str);
	return (tmp);
}

void	single_quote_case(t_data *data, int i)
{
	data->array[i] = str_quo_modifier(data->array[i]);
	if (data->array[i] == NULL)
		return ;
}

int	expansion(t_data *data, char **env, int i)
{
	int	d;
	int	v;

	while (data->array[i] != NULL)
	{
		d = f_strchr(data->array[i], '$');
		if (d != -1 && (f_strchr(data->array[i], '\'') == -1)
			&& data->array[i][d + 1] != '?'
			&& ft_strchr(data->array[i] + 1, '$') == NULL)
		{
			v = var_finder(env, data->array[i] + d + 1);
			if (v == -1)
			{
				data->array[i] = str_modifier(data->array[i], "\n", d);
				return (0);
			}
			data->array[i] = str_modifier(data->array[i], env[v], d);
			if (data->array[i] == NULL)
				return (-1);
		}
		else if (data->array[i][0] == '\'')
			single_quote_case(data, i);
		i++;
	}
	return (0);
}
