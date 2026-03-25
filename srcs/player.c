/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:48 by vaires-m          #+#    #+#             */
/*   Updated: 2026/03/24 13:00:49 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	init_player_pos(t_game *game, int x, int y, float angle)
{
	game->player->px = x * TILE_LEN + (TILE_LEN / 2);
	game->player->py = y * TILE_LEN + (TILE_LEN / 2);
	game->player->pa = angle;
	game->player->fovla = game->player->pa - FOV;
	game->player->fovra = game->player->pa + FOV;
}

void	check_player(t_game *game, int x, int y)
{
	if (!game->map[y])
		return ;
	if (game->map[y][x] == 'N')
		init_player_pos(game, x, y, 3 * PI / 2);
	if (game->map[y][x] == 'S')
		init_player_pos(game, x, y, PI / 2);
	if (game->map[y][x] == 'W')
		init_player_pos(game, x, y, PI);
	if (game->map[y][x] == 'E')
		init_player_pos(game, x, y, 0);
}
