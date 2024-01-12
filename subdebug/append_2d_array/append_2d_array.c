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
		return (0);
	}
	while (array[i] != NULL)
		i ++;
	return (i);
}

char	**append_2d_array(char **origin, char *line)
{
	int		i;
	int		array_length;
	char	**tmp;

    if (origin == NULL)
    {
        origin = malloc(sizeof(char *));
        origin[0] == NULL;
    }
	array_length = array_length_2d(origin);
	tmp = (char **)malloc(sizeof(char *) * (array_length) + 2);
	i = 0;
	while (origin[i] != NULL)
	{
		tmp[i] = strdup(origin[i]);
		i ++;
	}
	tmp[i] = strdup(line);
	tmp[array_length + 1] = NULL;
	free_2d(origin);
	return (tmp);
}


int main() {
    char **myArray = NULL;

    // Testing array_length_2d with NULL array
    int length = array_length_2d(myArray);
    printf("Array length: %d\n", length);

    // Testing append_2d_array with NULL array
    myArray = append_2d_array(myArray, "Hello");
    printf("After appending, array length: %d\n", array_length_2d(myArray));

    // Appending more elements
    myArray = append_2d_array(myArray, "World");
    myArray = append_2d_array(myArray, "How");
    myArray = append_2d_array(myArray, "Are");
    myArray = append_2d_array(myArray, "You");

    // Displaying the final array
    printf("Final array:\n");
    for (int i = 0; myArray[i] != NULL; i++) {
        printf("%s\n", myArray[i]);
    }

    // Freeing the memory
    free_2d(myArray);

    return 0;
}