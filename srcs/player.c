/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:48 by vaires-m          #+#    #+#             */
/*   Updated: 2026/04/19 18:06:56 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/**
 * initializes the player’s starting position and view direction
 * based on a map tile coordinate.
 */
static void	init_player_pos(t_game *game, int x, int y, float angle)
{
	game->player->px = x * TILE_LEN + (TILE_LEN / 2);
	game->player->py = y * TILE_LEN + (TILE_LEN / 2);
	game->player->pa = angle;
	game->player->fovla = game->player->pa - FOV;
	game->player->fovra = game->player->pa + FOV;
}

/**
 * sets the player’s initial angle
 * based on the start direction letter from the map (N, S, E, W),
 * and spawns them at the start tile.
 */
void	init_player_from_start(t_game *game)
{
	int		x;
	int		y;
	char	dir;

	x = game->player_start_col;
	y = game->player_start_row;
	dir = game->player_start_dir;
	if (dir == 'N')
		init_player_pos(game, x, y, 3 * PI / 2);
	else if (dir == 'S')
		init_player_pos(game, x, y, PI / 2);
	else if (dir == 'W')
		init_player_pos(game, x, y, PI);
	else if (dir == 'E')
		init_player_pos(game, x, y, 0);
}
