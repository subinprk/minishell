/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_modification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 05:53:16 by siun              #+#    #+#             */
/*   Updated: 2024/02/12 20:31:08 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*f_strjoin(char *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((f_strlen(s) + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i ++;
	}
	str[i] = c;
	str[i + 1] = 0;
	return (str);
}

char	*strrjoin(char *s1, char *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (!s1)
		return (s2);
	else
	{
		while (s2 && s2[i])
		{
			str = f_strjoin(s1 + f_strlen(s1), s2[i]);
			i++;
		}
	}
	return (str);
}

void	if_tmp(int *flag, char *tmp, char **argv)
{
	if (*flag == 1)
	{
		*flag = 0;
		free((*argv));
		(*argv) = ft_strdup(tmp);
		//free(tmp);
	}
	return ;
}

void	if_dollar_qu(char **tmp, char *status, int *flag, int *j)
{
	if (ft_strcmp(status, "13") == 0)
		*tmp = strrjoin(*tmp, "0");
	else
		*tmp = strrjoin(*tmp, status);
	*flag = 1;
	*j += 2;
}

void	replace_exit_status(char ***argv, int i, int flag, int j)
{
	char	*tmp;
	char	*status;

	status = status_ret();
	if ((*argv) == NULL || (**argv) == NULL)
		return ;
	while ((*argv)[i])
	{
		tmp = NULL;
		while ((*argv)[i][j] && f_strchr((*argv)[i], '$') != -1)
		{
			if ((*argv)[i][j] && (*argv)[i][j] == '$'
			&& (*argv)[i][j + 1] == '?')
				if_dollar_qu(&tmp, status, &flag, &j);
			else if ((*argv)[i][j] == '\0')
				break ;
			else
				tmp = f_strjoin(tmp, (*argv)[i][j++]);
		}
		if_tmp(&flag, tmp, &(*argv)[i++]);
		j = 0;
	}
	free(status);
	return ;
}
