/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ch_complete.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftemori <ftemori@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:53:32 by ftemori           #+#    #+#             */
/*   Updated: 2024/02/14 11:53:36 by ftemori          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	if_tmp_null(t_data *data, char *tmp, int i, int k)
{
	if (tmp[i] == '\0')
	{
		data->array[k] = NULL;
		return (-1);
	}
	return (0);
}

int	ft_chopper(t_data *data, char *tmp, int k)
{
	int	i;

	i = 0;
	if (tmp[0] == '\0')
		return (-1);
	while (tmp[i] == ' ')
		tmp++;
	if (if_tmp_null(data, tmp, i, k) == -1)
		return (0);
	while_function(tmp, &i);
	if (tmp[0] == '\'')
		tmp = ifhelper(data, tmp, i + 1, k);
	else if (tmp[0] == '\"')
		tmp = elsehelper(data, tmp, i + 1, k);
	else if (tmp[0] != '=' && tmp[0] != '\0' && tmp[0] != '<'
		&& tmp[0] != '>' && tmp[0] != '|')
		ft_strcpy(data, tmp, i, k);
	else if ((tmp[0] == '>' && tmp[1] == '>')
		|| (tmp[0] == '<' && tmp[1] == '<'))
		i = ft_strcpy(data, tmp, 2, k);
	else if (tmp[0] == '=' || tmp[0] == '<' || tmp[0] == '>' || tmp[0] == '|')
		i = ft_strcpy(data, tmp, 1, k);
	if (ft_chopper(data, tmp + i, ++k) == -1 || tmp[i] == '\0')
		data->array[k] = NULL;
	return (0);
}

void	else_if_str(int *inquotes, int *count, int *inword)
{
	if (*inquotes == 1)
	{
		*count += 1;
		*inword = 0;
		*inquotes = 0;
	}
	else
	{
		*inquotes = 1;
		*inword = 1;
	}
	return ;
}

int	word_counter(const char *str, int count, int inword, int inquotes)
{
	while (*str)
	{
		if (*str == ' ' && inquotes == 0)
			inword = 0;
		else if (*str == '=' || *str == '<' || *str == '>'
			|| *str == '|' || *str == '$')
		{
			count++;
			inword = 0;
		}
		else if (*str == '"' || *str == '\'')
			else_if_str(&inquotes, &count, &inword);
		else
		{
			if (inword == 0)
			{
				count++;
				inword = 1;
			}
		}
		str++;
	}
	return (count);
}

char	**input_validation(char *tmp, char **env)
{
	t_data	data;

	data.tmp = tmp;
	if (quo_num(tmp, &data) == -1)
		return (NULL);
	data.word_count = word_counter(data.tmp, 0, 0, 0);
	if (data.word_count == 0)
		return (NULL);
	if (data.sqn + data.dqn > 0)
		if (quo_order(tmp, &data, 0, 0) == -1)
			return (NULL);
	data.array = malloc((data.word_count + 1) * sizeof(char *));
	if (ft_chopper(&data, tmp, 0) == -1)
		return (NULL);
	if (expansion(&data, env, 0) == -1)
		return (NULL);
	return (data.array);
}

/*int	main(int ac, char **av, char **env)
{
	int	i = 0;
	char	*tmp;
	char	**array;
	if (ac && av)
	read_history("history_file");
	tmp = readline("promp> ");
	if ((array = input_validation(tmp, env)) == NULL)
	{
		printf("wrong input you goofy");
		return (0);
	}
	while (array[i] != NULL)
	{
		printf("<%s>\n", array[i]);
		free(array[i]);
		i++;
	}
	free(array);
	return (0);
}*/
