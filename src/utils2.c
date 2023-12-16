/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irivero- <irivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:14:48 by irivero-          #+#    #+#             */
/*   Updated: 2023/12/05 09:34:50 by irivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	remove_char(char *str, char c)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] != c)
            str[j++] = str[i];
        i++;
    }
    str[j] = 0;
    return (1);
}

int	double_char_len(char **str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

int	is_stringdigit(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}

/* determine if a given string, consistes of whitespace characters*/
int        is_whitespace(char *c)
{
    int        i;
    int        space;

    space = 0;
    i = 0;
    if(c[0] == 0)
        return (1);
    while (c[i])
    {
        if (c[i] == '\r' || c[i] == '\v' || c[i] == '\t' || c[i] == '\f')
            return (1);
        else if (c[i] == ' ')
            space++;
        i++;
    }
    if (space == (int)ft_strlen(c))
        return (1);
    return (0);
}
