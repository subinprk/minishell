#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void	free_2d(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i ++]);
	free(arr);
}

int	array_length_2d(char **array)
{
	int	i;

	i = 0;
	if (array == NULL || *array == NULL)
	{
		printf("is it here?");
		return (0);
	}
	while (array[i] != NULL)
		i ++;
	return (i);
}

char	**cpy_full_2d_array(char **origin)
{
	int		i;
	int		origin_length;
	char	**array;

	if (origin == NULL)
		return (NULL);
	array = NULL;
	origin_length = array_length_2d(origin);
	array = (char **)malloc(sizeof(char *) * ((origin_length) + 1));
	if (!array)
		exit(errno);
	i = 0;
	while(i < origin_length)
	{
		array[i] = strdup(origin[i]);
		if (!array[i])
			exit(errno);
		i ++;
	}
	free_2d(origin);
	array[origin_length] = NULL;
	return (array);
}

char	**append_2d_array(char **origin, char *line)
{
	int		i;
	int		array_length;
	char	**tmp;

	array_length = array_length_2d(origin);
	tmp = (char **)malloc(sizeof(char *) * (array_length + 2));
	i = 0;
	while (origin != NULL && origin[i] != NULL)
	{
		tmp[i] = strdup(origin[i]);
		i ++;
	}
	tmp[i] = strdup(line);
	tmp[array_length + 1] = NULL;
	if (origin)
		free_2d(origin);
	return (tmp);
}

// void	append_2d_array(char ***origin, char *line)
// {
// 	int		i;
// 	int		array_length;
// 	char	**tmp;

// 	array_length = array_length_2d(*origin);
// 	printf("array length : %d", array_length);
// 	tmp = cpy_full_2d_array(*origin);
// 	if (*(origin) != NULL)
// 		free_2d(*(origin));
// 	*origin = (char **)malloc(sizeof(char *) * (array_length + 2));
// 	i = 0;
// 	while (i < array_length)
// 	{
// 		(*origin)[i] = strdup(tmp[i]);
// 		i ++;
// 	}
// 	(*origin)[array_length] = strdup(line);
// 	printf("copied origin: %s\n", (*origin)[array_length]);
// 	printf("array length: %d\n", array_length);
// 	if (tmp != NULL)
// 		free_2d(tmp);
// 	(*origin)[array_length + 1] = NULL;
// }


int main() {
    // Example usage
    char **myArray = NULL;
    myArray = append_2d_array(myArray, "Line 1");
    myArray = append_2d_array(myArray, "Line 2");

    // ... do something with myArray ...
	for (int i = 0; myArray[i] != NULL; i++)
	{
		printf("%s\n", myArray[i]);
	}

    // Don't forget to free the memory when done
    free_2d(myArray);

    return 0;
}