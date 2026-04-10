#include "cube3d.h"

/*
** Returns the character at grid[y][x], or ' ' if out of bounds.
** Used so the closed-wall check treats the outside as "open space".
*/
static char	safe_cell(char **grid, int rows, int y, int x)
{
	int	len;

	if (y < 0 || y >= rows || x < 0)
		return (' ');
	len = (int)ft_strlen(grid[y]);
	if (x >= len)
		return (' ');
	return (grid[y][x]);
}

/*
** For every traversable cell (0 or player spawn), checks that all four
** cardinal neighbours exist and are not space / out-of-bounds.
** Returns 0 if closed, -1 with error message if not.
*/
static int	check_closed(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (map->grid[y][x])
		{
			c = map->grid[y][x];
			if (c == '0' || ft_strchr("NSEW", c))
			{
				if (safe_cell(map->grid, map->rows, y - 1, x) == ' '
					|| safe_cell(map->grid, map->rows, y + 1, x) == ' '
					|| safe_cell(map->grid, map->rows, y, x - 1) == ' '
					|| safe_cell(map->grid, map->rows, y, x + 1) == ' ')
					return (ft_error(ERR_CLOSED));
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*
** Iterates every cell in the grid:
**   - Rejects characters outside the valid set.
**   - Counts player spawn markers (N/S/E/W).
** Stores the player position and direction in map on success.
** Returns 0 on success, -1 on error.
*/
static int	check_chars_and_player(t_map *map)
{
	int		player_count;
	int		y;
	int		x;
	char	c;

	player_count = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (map->grid[y][x])
		{
			c = map->grid[y][x];
			if (!ft_strchr("01DNSEW ", c))
				return (ft_error(ERR_CHAR));
			if (ft_strchr("NSEW", c))
			{
				map->player_x = x;
				map->player_y = y;
				map->player_dir = c;
				player_count++;
			}
			x++;
		}
		y++;
	}
	if (player_count == 0 || player_count > 1)
		return (ft_error(ERR_PLAYER));
	return (0);
}

/*
** Builds map->grid from the array of raw map lines.
** Each line is duplicated so the grid owns its memory.
** Returns 0 on success, -1 on allocation failure.
*/
int	build_map_grid(t_map *map, char **lines, int count)
{
	int	i;
	int	len;

	map->rows = count;
	map->cols = 0;
	map->grid = ft_calloc(count + 1, sizeof(char *));
	if (!map->grid)
		return (ft_error(ERR_MEM));
	i = 0;
	while (i < count)
	{
		map->grid[i] = ft_strdup(lines[i]);
		if (!map->grid[i])
		{
			free_array(map->grid);
			map->grid = NULL;
			return (ft_error(ERR_MEM));
		}
		len = (int)ft_strlen(map->grid[i]);
		if (len > map->cols)
			map->cols = len;
		i++;
	}
	return (0);
}

/*
** Scans the validated grid and builds the map->doors array.
** Each 'D' cell gets a corresponding t_door entry (state DOOR_CLOSED).
** Returns 0 on success, -1 on allocation failure.
*/
static int	collect_doors(t_map *map)
{
	int		count;
	int		y;
	int		x;
	int		i;

	count = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'D')
				count++;
			x++;
		}
		y++;
	}
	map->door_count = count;
	if (count == 0)
		return (0);
	map->doors = ft_calloc(count, sizeof(t_door));
	if (!map->doors)
		return (ft_error(ERR_MEM));
	i = 0;
	y = 0;
	while (y < map->rows)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == 'D')
			{
				map->doors[i].x = x;
				map->doors[i].y = y;
				map->doors[i].state = DOOR_CLOSED;
				map->doors[i].timer = 0.0;
				i++;
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*
** Top-level map validator called after build_map_grid.
** Runs character/player check, wall-closure check, then door collection.
** Returns 0 on success, -1 on any validation failure.
*/
int	validate_map(t_map *map)
{
	if (map->rows == 0)
		return (ft_error("Map is empty"));
	if (check_chars_and_player(map) == -1)
		return (-1);
	if (check_closed(map) == -1)
		return (-1);
	if (collect_doors(map) == -1)
		return (-1);
	return (0);
}
