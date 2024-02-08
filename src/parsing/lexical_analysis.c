/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analysis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 02:36:57 by siun              #+#    #+#             */
/*   Updated: 2024/02/08 17:19:23 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_it_rellocater(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (1);
	else if (!ft_strcmp(str, ">"))
		return (1);
	else if (!ft_strcmp(str, ">>"))
		return (1);
	else if (!ft_strcmp(str, "<<"))
		return (1);
	else
		return (0);
}

int	allocate_token(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (TOK_PIPE);
	else if (is_it_rellocater(str))
		return (TOK_REDIRET);
	else if (ft_strcmp(str, "\'") == 0)
		return (TOK_S_QUOTE);
	else if (ft_strcmp(str, "\"") == 0)
		return (TOK_D_QUOTE);
	else
		return (TOK_WORD);
}

int	*token_data(char **chopped_str)
{
	int	*token;
	int	token_num;
	int	i;

	token_num = array_length_2d(chopped_str);
	token = (int *)malloc(sizeof(int) * (token_num + 1));
	i = 0;
	while (i < token_num)
	{
		token[i] = allocate_token(chopped_str[i]);
		i ++;
	}
	token[token_num] = TOK_NULL_HANDLE;
	return (token);
}
