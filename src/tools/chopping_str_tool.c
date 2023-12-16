/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chopping_str_tool.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: subpark <subpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:02:21 by subpark           #+#    #+#             */
/*   Updated: 2023/12/07 17:06:18 by subpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	find_rellocator(char *str, int *i, int *count)
{
	if (str[*i] == '<')
	{
		if (str[(*i) + 1] == '<')
			(*i) ++;
		(*count) ++;
	}
	else if (str[*i] == '>')
	{
		if (str[(*i) + 1] == '>')
			(*i) ++;
		(*count) ++;
	}
}

/*void	find_spaces(char *str, int *i, int *count)
{
	if (str[*i] == ' ')
	while (str[*i] == ' ')
		(*i) ++;
	(*count) ++;
}*/

char	*strdup_rellocator(char *str, int *i)
{
	(*i) = (*i) + 1;
	if (str[(*i) - 1] == str[(*i)])
	{
		(*i) = (*i) + 1;
		if (str[(*i) - 1] == '<')
			return (ft_strdup("<<"));
		else
			return (ft_strdup(">>"));
	}
	else
	{
		if (str[(*i) - 1] == '<')
			return (ft_strdup("<"));
		else
			return (ft_strdup(">"));
	}
	return (NULL);
}

char	*strdup_word(char *str, int *i)
{
	char	*word;
	int		word_length;
	int		start;

	start = *i;
	word_length = count_word_length(str, *i);
	word = (char *)malloc(sizeof(char) * (word_length + 1));
	if (!word)
		return (NULL);
	while ((*i) < word_length + start)
	{
		word[(*i) - start] = str[(*i)];
		(*i) ++;
	}
	word[word_length] = 0;
	return (word);
}
