/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_modification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 05:53:16 by siun              #+#    #+#             */
/*   Updated: 2024/02/10 17:26:42 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	replace_exit_status(char ***argv)
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
}

/* void	replace_exit_code(char ***argv)
{
	int		i;
	int		j;
	char 	*tmp;
	char	*exitval;

	i = 0;
	j = 0;
	if ((*argv) == NULL || (**argv) == NULL)
		return ;
	while ((*argv)[i])
	{
		while ((*argv)[i][j] && f_strchr((*argv)[i], '$') != -1)
		{
			if ((*argv)[i][j] == '$' && (*argv)[i][j + 1] == '?')
			{
				free((*argv)[i]);
				(*argv)[i] = ft_itoa(g_exit_status);
				j += 2;
			}
			tmp[j] = (*argv)[i][j];
			j++;
		}
		j = 0;
		i++;
	}
} */