/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv_modification.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 05:53:16 by siun              #+#    #+#             */
/*   Updated: 2024/01/14 06:10:34 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	replace_exit_status(char ***argv)
{
	int	i;
	char *tmp;

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
