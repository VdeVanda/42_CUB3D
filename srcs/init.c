/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:54 by vaires-m          #+#    #+#             */
/*   Updated: 2026/04/22 11:15:52 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/**
 * Initializes the rays array for the game. It allocates memory for the specified
 * number of rays and sets the initial values for each ray's distance, texture
 * x-coordinate, and wall direction. The function also updates the game's
 * rays_count field with the number of rays initialized.
 */
t_ray	*init_rays(t_game *game, int nbr)
{
	int		i;
	t_ray	*rays;

	i = 0;
	rays = malloc(sizeof(t_ray) * nbr);
	if (!rays)
		return (NULL);
	while (i < nbr)
	{
		rays[i].dist = 0.0f;
		rays[i].tex_x = 0.0f;
		rays[i].wall_dir = WALL_NORTH;
		i++;
	}
	game->rays_count = i;
	return (rays);
}

/**
 * Initializes the key states for the game. It sets all key state variables
 * to 0, indicating that no keys are currently pressed. This function is called
 * during the initialization of the game to ensure that the key states are in a
 * known state before any user input is processed.
 */
static void	init_game_keys(t_game *game)
{
	game->key_w = 0;
	game->key_a = 0;
	game->key_s = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
}

/**
 * A safe default initialization function for the game structure
 * to start with known default values, no garbage.
 * Define default window size.
 */
static void	init_game_values(t_game *game)
{
	game->rays_count = 0;
	game->mlx_3d = NULL;
	game->win_3d = NULL;
	game->world_3d = NULL;
	game->map = NULL;
	game->map_rows = 0;
	game->map_cols = 0;
	game->window_w_3d = 1500;
	game->window_h_3d = 1000;
	game->fisheye_level = 4;
}

/**
 * Allocates and initializes the main game structure and its components.
 */
int	init_structs(t_game **game)
{
	*game = (t_game *)malloc(sizeof(t_game));
	if (!*game)
		return (1);
	(*game)->player = (t_player *)malloc(sizeof(t_player));
	if (!(*game)->player)
	{
		free(*game);
		return (1);
	}
	init_game_values(*game);
	init_game_keys(*game);
	(*game)->rays = init_rays(*game, (*game)->window_w_3d);
	if (!(*game)->rays)
	{
		free((*game)->player);
		free(*game);
		return (1);
	}
	return (0);
}
