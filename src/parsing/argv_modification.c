/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_modification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 05:53:16 by siun              #+#    #+#             */
/*   Updated: 2024/02/12 13:34:50 by ubuntu           ###   ########.fr       */
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

void	coppying(char **tmp, char *status)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((*tmp)[i])
		i++;
	while (status[j])
	{
		(*tmp)[i] = status[j];
		i++;
		j++;
	}
	(*tmp)[i] = 0;
	return ;
}

char	*f_strjoin(char **s1, char const *s2)
{
	char	*str;
	int		i1;
	int		i2;

	i1 = 0;
	i2 = 0;
	str = (char *) malloc((ft_strlen(*s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (*s1[i1])
	{
		str[i1] = *s1[i1];
		i1 ++;
	}
	while (s2[i2])
	{
		str[i1 + i2] = s2[i2];
		i2 ++;
	}
	str[i1 + i2] = '\0';
			printf("its here str: %s\n", str);
	if (*s1 && (*s1[0]))
		free(*s1);
	//free(*s1);
	(*s1) = str;
	return (str);
}

void	replace_exit_status(char ***argv)
{
	int		i;
	int		j;
	int		flag;
	char 	*tmp;
	char	*status;
	char	*c;

	i = 0;
	j = 0;
	flag = 0;
	c = malloc(3 * sizeof(char *));
	c[1] = '\0';
	status = ft_itoa(g_exit_status);
	if ((*argv) == NULL || (**argv) == NULL)
		return ;
	while ((*argv)[i])
	{
		tmp = "\0";
		while ((*argv)[i][j] && f_strchr((*argv)[i], '$') != -1)
		{
			if ((*argv)[i][j] && (*argv)[i][j] == '$' && (*argv)[i][j + 1] == '?')
			{
				tmp = ft_strjoin(tmp, status);
				flag = 1;
				j += 2;
			}
			else if ((*argv)[i][j] == '\0')
				break ;
			else
			{
				c[0] = (*argv)[i][j];
				tmp = ft_strjoin(tmp, c);
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
	return ;
}