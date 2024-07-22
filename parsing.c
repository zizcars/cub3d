#include <stdbool.h>
#include "../libft/libft.h"

bool check_filename(char *file_name)
{
    char *tmp;

    tmp = ft_strrchr(file_name, '.');
    if (ft_strcmp(file_name, tmp) == 0)
        return (true);
    return (false);
}
