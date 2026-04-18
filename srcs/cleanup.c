/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:58 by vaires-m          #+#    #+#             */
/*   Updated: 2026/04/18 18:58:10 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/**
 * Frees the memory allocated for the game map. It iterates through each row of
 * the map, freeing the memory for each row string, and then frees the array
 * of row pointers itself. This function is called during cleanup to ensure that
 * all dynamically allocated memory for the map is properly released.
 */
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

/**
 * Frees the textures loaded in the game. It iterates through the array of wall
 * textures, destroying each image using mlx_destroy_image() if it exists.
 * It also frees the world_3d image if it exists.
 */
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

/**
 * Cleans up all resources allocated for the game.
 * This includes freeing the rays array, textures, map,
 * and destroying the window and display if they were created.
 */
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

/**
 * Performs a comprehensive cleanup of all game resources.
 * It frees the rays array, textures, map, and destroys the window
 * and display if they were created.
 */
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

/**
 * Handles the window close event. It calls cleanup_game() to free all resources
 * and then exits the program. This function is registered as a callback for the
 * window close event to ensure that resources are properly released when the
 * user closes the game window.
 */
int	close_window(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
