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

/* void	replace_exit_status(char ***argv)
{
	int		i;
	char 	*tmp;

	if ((*argv) == NULL || (**argv) == NULL)
		return ;
	i = 0;
	while ((*argv)[i])
	{
		if (!ft_strcmp((*argv)[i], "$?"))
		{
			free((*argv)[i]);
			tmp = ft_itoa(g_exit_status);
			(*argv)[i] = ft_strdup(tmp);
			free(tmp);
		}
		i ++;
	}
} */

char	*f_strjoin(char *s, char c)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((ft_strlen(s) + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i ++;
	}
	str[i] = c;
	str[i + 1] = 0;
	if (i > 0)
		free(s);
	return (str);
}

char	*strrjoin(char *s1, char *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (!s1)
		return(s2);
	else
		while (s2 && s2[i])
		{
			str = f_strjoin(s1, s2[i]);
			i++;
		}
	return (str);
}

void	replace_exit_status(char ***argv)
{
	int		i;
	int		j;
	int		flag;
	char 	*tmp;
	char	*status;

	i = 0;
	j = 0;
	flag = 0;
	status = ft_itoa(g_exit_status);
	if ((*argv) == NULL || (**argv) == NULL)
		return ;
	while ((*argv)[i])
	{
		tmp = "\0";
		while ((*argv)[i][j] && f_strchr((*argv)[i] + j, '$') != -1)
		{
			if ((*argv)[i][j] && (*argv)[i][j] == '$' && (*argv)[i][j + 1] == '?')
			{
				tmp = strrjoin(tmp, status);
				flag = 1;
				j += 2;
			}
			else if ((*argv)[i][j] == '\0')
				break ;
			else
			{
				tmp = f_strjoin(tmp, (*argv)[i][j]);
				j++;
			}
		}
		if (flag == 1)
		{
			flag = 0;
			free((*argv)[i]);
			(*argv)[i] = ft_strdup(tmp);
			free(tmp);
		}
		j = 0;
		i++;
	}
	free(status);
	return ;
}