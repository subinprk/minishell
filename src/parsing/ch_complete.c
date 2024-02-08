#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "../../include/minishell.h"

typedef struct	s_data
{
	int	word_count;
	int	sqn;
	int	dqn;
	char	**array;
	char	*tmp;
}	t_data;

int	quo_num(char *tmp, t_data *data)
{
	int	i = 0, s = 0, d = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\'')
			s++;
		if (tmp[i] == '\"')
			d++;
		i++;
	}
	if ((s % 2 == 0 || s == 0) && (d % 2 == 0 || d == 0))
	{
		data->sqn = s;
		data->dqn = d;
		return (s);
	}
	return (-1);
}

int	quo_arrangement(char *str)
{
	int	i = 0, k = 0;
	char	*sstr = malloc(strlen(str) * sizeof(char));
	while (str[i])
	{
		if (str[i] == '\'' && str[i + 1] != '\'')
		{
			sstr[k] = str[i];
			k++;
			i++;
		}
		else if (str[i] == '\"' && str[i + 1] != '\"')
		{
			sstr[k] = str[i];
			i++;
			k++;
		}
		else
			i += 2;
	}
	sstr[k] = '\0';
	if (strlen(sstr) > 3 && sstr[0] == sstr[2] && sstr[0] != '\0')
	{
		free(sstr);
		return (-1);
	}
	if (sstr[0] != '\0')
		if (quo_arrangement(sstr) == -1)
		{
			free(sstr);
			return (-1);
		}
	free(sstr);
	return (0);
}

int	quo_order(char *tmp, t_data *data)
{
	int	i = 0, k = 0;
	char	*q_string;
	q_string = malloc((data->sqn + data->dqn + 1) * sizeof(char));
	while (tmp[i])
	{
		if (tmp[i] == '\'')
		{
			q_string[k] = '\'';
			k++;
		}
		if (tmp[i] == '\"')
		{
			q_string[k] = '\"';
			k++;
		}
		i++;
	}
	q_string[k] = '\0';
	if (quo_arrangement(q_string) == -1)
	{
		free(q_string);
		return (-1);
	}
	free(q_string);
	return (0);
}

int	ft_strcpy(t_data *data, char *tmp, int len, int k)
{
	int	i = 0;
	data->array[k] = malloc((len + 1) * sizeof(char));
	if (!data->array[k])
		return (-1);
	while (i < len)
	{
		data->array[k][i] = tmp[i];
		i++;
	}
	data->array[k][i] = '\0';
	return (len);
}

char	*ifhelper(t_data *data, char *tmp, int i, int k)
{
	int	m;

	m = i;
	while (tmp[i] != '\'' && tmp[i] != '\0')
		i++;
	ft_strcpy(data, tmp + m - 1, i + 1, k);
	i++;
	tmp = tmp + i;
	return (tmp);
}

char	*elsehelper(t_data *data, char *tmp, int i, int k)
{
	int	m;

	m = i;
	while (tmp[i] != '\"' && tmp[i] != '\0')
		i++;
	ft_strcpy(data, tmp + m, i - 1, k);
	i++;
	tmp = tmp + i;
	return (tmp);
}

int	ft_chopper(t_data *data, char *tmp, int k)
{
	int	i;

	i = 0;
	if (tmp[0] == '\0')
		return (-1);
	while (tmp[i] == ' ')
		tmp++;
	if (tmp[i] == '\0')
	{
		data->array[k] = NULL;
		return (0);
	}
	while (tmp[i] != '\0' && tmp[i] != ' ' && tmp[i] != '=' && tmp[i] != '\"' && tmp[i] != '\'' && tmp[i] != '<' && tmp[i] != '>' && tmp[i] != '|')
		i++;
	if (tmp[0] == '\'')
		tmp = ifhelper(data, tmp, i + 1, k);
	else if (tmp[0] == '\"')
		tmp = elsehelper(data, tmp, i + 1, k);
	else if (tmp[0] != '=' && tmp[0] != '\0' && tmp[0] != '<' && tmp[0] != '>' && tmp[0] != '|')
		ft_strcpy(data, tmp, i, k);
	else if ((tmp[0] == '>' && tmp[1] == '>') || (tmp[0] == '<' && tmp[1] == '<'))
		i = ft_strcpy(data, tmp, 2, k);
	else if (tmp[0] == '=' || tmp[0] == '<' || tmp[0] == '>' || tmp[0]  == '|')
		i = ft_strcpy(data, tmp, 1, k);
	if (ft_chopper(data, tmp + i, ++k) == -1 || tmp[i] == '\0')
		data->array[k] = NULL;
	return (0);
}

int	word_counter(const char* str) {
	int count = 0;
	bool inWord = false;
	bool inQuotes = false;

	while (*str) {
		if (*str == ' ' && !inQuotes) {
			inWord = false;
		} else if (*str == '=' || *str == '<' || *str == '>' || *str == '|' || *str == ',') {
			count++;
			inWord = false;
		} else if (*str == '"' || *str == '\'') {
			if (inQuotes) {
				count++;
				inWord = false;
				inQuotes = false;
			} else {
				inQuotes = true;
				inWord = true;
			}
		} else {
			if (!inWord) {
				count++;
				inWord = true;
			}
		}
		str++;
	}
	return count;
}

 /* int	f_strchr(char *s, char c)
{
	int	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (-1);
	return (i);
}

int	f_strcmp(char *s1, char *s2)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	return (0);
} */

int	var_finder(char **env, char *s)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (f_strcmp(env[i], s) != -1)
			return (i); 
		i++;
	}
	return (-1);
}

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

int	expansion(t_data *data, char **env)
{
	int	i;
	int	d;
	int	v;

	i = 0;
	while (data->array[i] != NULL)
	{
		d = f_strchr(data->array[i], '$');
		if (d != -1 && (f_strchr(data->array[i], '\'') == -1) && data->array[i][d + 1] != '?')
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
		{
			data->array[i] = str_quo_modifier(data->array[i]);
			if (data->array[i] == NULL)
				return (-1);
		}
		i++;
	}
	return (0);
}

char	**input_validation(char *tmp, char **env)
{
	t_data	data;
	data.tmp = tmp;
	if (quo_num(tmp, &data) == -1)
		return (NULL);
	data.word_count = word_counter(data.tmp);
	if (data.word_count == 0)
		return (NULL);
	if (data.sqn + data.dqn > 0)
		if (quo_order(tmp, &data) == -1)
			return (NULL);
	data.array = malloc((data.word_count + 1) * sizeof(char *));
	if (ft_chopper(&data, tmp, 0) == -1)
		return (NULL);
	if (expansion(&data, env) == -1)
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