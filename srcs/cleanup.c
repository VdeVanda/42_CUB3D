/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:58 by vaires-m          #+#    #+#             */
/*   Updated: 2026/03/25 17:13:04 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex_wall[i].img && game->mlx_3d)
			mlx_destroy_image(game->mlx_3d, game->tex_wall[i].img);
		i++;
	}
	if (game->world_3d)
	{
		if (game->world_3d->img && game->mlx_3d)
			mlx_destroy_image(game->mlx_3d, game->world_3d->img);
		free(game->world_3d);
		game->world_3d = NULL;
	}
}

static void	free_paths_and_resources(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex_paths[i])
		{
			free(game->tex_paths[i]);
			game->tex_paths[i] = NULL;
		}
		i++;
	}
	free_textures(game);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->rays)
		free(game->rays);
	free_paths_and_resources(game);
	if (game->map)
		free_map(game->map);
	if (game->win_3d && game->mlx_3d)
		mlx_destroy_window(game->mlx_3d, game->win_3d);
	if (game->mlx_3d)
	{
		mlx_destroy_display(game->mlx_3d);
		free(game->mlx_3d);
	}
	if (game->player)
		free(game->player);
	free(game);
}

int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
