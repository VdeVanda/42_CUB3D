/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:52 by vaires-m          #+#    #+#             */
/*   Updated: 2026/03/25 16:39:36 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	count_map_col(char *file)
{
	size_t	len;
	int		fd;
	char	*line;

	len = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		if (strlen(line) > len)
			len = strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (len - 1);
}

int	count_map_rows(char *file)
{
	int		len;
	int		fd;
	char	*line;

	len = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		len++;
		line = get_next_line(fd);
	}
	close(fd);
	return (len);
}

static void	read_map_lines(int fd, char **map, int height)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (i < height)
			map[i] = line;
		else
			free(line);
		i++;
		line = get_next_line(fd);
	}
}

char	**load_maps(char *file, int height)
{
	char	**map;
	int		k;
	int		fd;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	k = 0;
	while (k <= height)
		map[k++] = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	read_map_lines(fd, map, height);
	close(fd);
	return (map);
}
