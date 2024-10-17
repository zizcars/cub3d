#include "../includes/utiles.h"

// calculate the length of an array (it stops in the NULL or '\n')
int array_length(char **array)
{
	int len;

	len = 0;
	while (array && array[len])
	{
		if (ft_strcmp(array[len], "\n") == 0) // I add array[len] == '\n' because in some cases the array is being like this [..., "\n", NULL];
			break;
		len++;
	}
	return (len);
}

//free an array and set it to NULL
void free_array(char ***array)
{
	int len;

	len = 0;
	while ((*array) && (*array)[len])
	{
		free((*array)[len++]);
	}
	free(*array);
	*array = NULL;
}

// calculate the length of an array
int array_size(char **array)
{
	int size;

	size = 0;
	while (array && array[size])
		size++;
	return (size);
}

// append arg to end of old_array and free old_array
char **append_array(char **old_array, char *arg)
{
	int size;
	char **new_array;

	if (arg == NULL)
		return (old_array);
	size = array_size(old_array);
	new_array = malloc(sizeof(char *) * (size + 2));
	if (new_array == NULL)
		return (NULL);
	if (old_array == NULL)
	{
		new_array[0] = ft_strdup(arg);
		new_array[1] = NULL;
		return (new_array);
	}
	size = 0;
	while (old_array[size])
	{
		new_array[size] = ft_strdup(old_array[size]);
		size++;
	}
	free_array(&old_array);
	new_array[size++] = ft_strdup(arg);
	new_array[size] = NULL;
	return (new_array);
}
