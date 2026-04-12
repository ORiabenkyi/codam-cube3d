#include "cube3d.h"

/*
** Checks that path ends with ".cub".
** Returns 0 on success, -1 on error.
*/
int	check_extension(char *path)
{
	int	len;

	len = (int)ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (ft_error(ERR_EXT));
	return (0);
}
