/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:52 by vaires-m          #+#    #+#             */
/*   Updated: 2026/03/24 13:00:53 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	print_map(t_game *game, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < height)
	{
		j = 0;
		while (game->map[i][j])
		{
			printf("%c ", game->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	count_map_col(char *file)
{
	size_t	len;
	int		fd;
	char	*line;

	len = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	while ((line = get_next_line(fd)))
	{
		if (strlen(line) > len)
			len = strlen(line);
		free(line);
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
	while ((line = get_next_line(fd)))
	{
		free(line);
		len++;
	}
	close(fd);
	return (len);
}

char	**load_maps(char *file, int height)
{
	char	**map;
	int		k;
	int		i;
	int		fd;
	char	*line;

	map = malloc(sizeof(char *) * (height + 1));
	if (!map)
		return (NULL);
	k = 0;
	while (k <= height)
		map[k++] = NULL;
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(map);
		return (NULL);
	}
	while ((line = get_next_line(fd)))
	{
		if (i < height)
			map[i] = line;
		else
			free(line);
		i++;
	}
	return (map);
}

void	render_map(t_game *game)
{
	mlx_put_image_to_window(game->mlx_3d, game->win_3d, game->world_3d->img, 0,
		0);
}
