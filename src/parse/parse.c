#include "cube3d.h"

/*
** Checks that path ends with ".cub".
** Returns 0 on success, -1 on error.
*/
static int	check_extension(char *path)
{
	int	len;

	len = (int)ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4) != 0)
		return (ft_error(ERR_EXT));
	return (0);
}

/*
** Drains the GNL static buffer by reading until EOF/error.
** Must be called while fd is still open so that read() fails with EBADF
** after close — which causes GNL to free its internal buffer_string.
*/
static void	gnl_drain(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

/*
** Reads every line from fd into a NULL-terminated char** array.
** Strips trailing newline from each line.
** Drains the GNL static buffer before returning NULL on failure so the
** caller's close(fd) does not leave a stale buffer for future GNL calls.
** Caller must free_array() the result.
*/
static char	**read_all_lines(int fd, int *count)
{
	char	**lines;
	char	**tmp;
	char	*line;
	int		cap;
	int		len;

	*count = 0;
	cap = 64;
	lines = ft_calloc(cap, sizeof(char *));
	if (!lines)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (*count >= cap - 2)
		{
			cap *= 2;
			tmp = ft_calloc(cap, sizeof(char *));
			if (!tmp)
			{
				free(line);
				free_array(lines);
				gnl_drain(fd);
				return (NULL);
			}
			ft_memcpy(tmp, lines, sizeof(char *) * (*count));
			free(lines);
			lines = tmp;
		}
		len = (int)ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		lines[(*count)++] = line;
		line = get_next_line(fd);
	}
	return (lines);
}

/*
** Adds a map line pointer to the map_lines buffer, growing it if needed.
** map_lines elements are *not* owned — they point into all_lines.
** Returns 0 on success, -1 on allocation failure.
*/
static int	append_map_line(char ***map_lines, int *map_count, int *map_cap,
	char *line)
{
	char	**tmp;

	if (*map_count >= *map_cap - 2)
	{
		*map_cap *= 2;
		tmp = ft_calloc(*map_cap, sizeof(char *));
		if (!tmp)
			return (-1);
		ft_memcpy(tmp, *map_lines, sizeof(char *) * (*map_count));
		free(*map_lines);
		*map_lines = tmp;
	}
	(*map_lines)[(*map_count)++] = line;
	return (0);
}

/*
** Checks that no non-empty lines remain after the map ends.
** Called when an empty line is encountered while in map mode.
** Returns 0 if clean, -1 if stray content is found.
*/
static int	check_no_content_after(char **all_lines, int total, int from)
{
	int	j;

	j = from;
	while (j < total)
	{
		if (!is_empty_line(all_lines[j]))
			return (ft_error(ERR_AFTER));
		j++;
	}
	return (0);
}

/*
** Iterates all lines, dispatching each to header parsing or map collection.
** Returns the number of map lines collected, or -1 on error.
*/
static int	collect_lines(t_map *map, char **all_lines, int total,
	char ***map_lines_out)
{
	char	**map_lines;
	int		map_count;
	int		map_cap;
	int		in_map;
	int		i;

	in_map = 0;
	map_count = 0;
	map_cap = 32;
	map_lines = ft_calloc(map_cap, sizeof(char *));
	if (!map_lines)
		return (ft_error(ERR_MEM));
	i = 0;
	while (i < total)
	{
		if (is_empty_line(all_lines[i]))
		{
			if (in_map)
			{
				if (check_no_content_after(all_lines, total, i + 1) == -1)
				{
					free(map_lines);
					return (-1);
				}
				break ;
			}
		}
		else if (in_map || is_map_line(all_lines[i]))
		{
			in_map = 1;
			if (append_map_line(&map_lines, &map_count, &map_cap,
					all_lines[i]) == -1)
			{
				free(map_lines);
				return (ft_error(ERR_MEM));
			}
		}
		else
		{
			if (parse_header_line(map, all_lines[i]) == -1)
			{
				free(map_lines);
				return (-1);
			}
		}
		i++;
	}
	*map_lines_out = map_lines;
	return (map_count);
}

/*
** Entry point for parsing a .cub file.
** Validates extension, reads file, parses headers and map, validates all.
** Populates game->map on success.
** Returns 0 on success, -1 on any error (error message already printed).
*/
int	parse_file(t_game *game, char *path)
{
	int		fd;
	char	**all_lines;
	char	**map_lines;
	int		total;
	int		map_count;
	t_map	*map;

	if (check_extension(path) == -1)
		return (-1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_error(ERR_OPEN));
	all_lines = read_all_lines(fd, &total);
	close(fd);
	if (!all_lines)
		return (ft_error(ERR_MEM));
	map = &game->map;
	ft_bzero(map, sizeof(t_map));
	map_lines = NULL;
	map_count = collect_lines(map, all_lines, total, &map_lines);
	if (map_count == -1)
	{
		free_array(all_lines);
		free_map(map);
		return (-1);
	}
	if (headers_complete(map) == -1)
	{
		free_array(all_lines);
		free(map_lines);
		free_map(map);
		return (-1);
	}
	if (map_count == 0)
	{
		free_array(all_lines);
		free(map_lines);
		free_map(map);
		return (ft_error(ERR_MAP));
	}
	if (build_map_grid(map, map_lines, map_count) == -1
		|| validate_map(map) == -1)
	{
		free_array(all_lines);
		free(map_lines);
		free_map(map);
		return (-1);
	}
	free_array(all_lines);
	free(map_lines);
	return (0);
}
