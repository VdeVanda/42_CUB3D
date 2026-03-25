/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:50 by vaires-m          #+#    #+#             */
/*   Updated: 2026/03/25 16:32:20 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	move_front(t_game *game)
{
	float	x;
	float	y;
	int		tile_x;
	int		tile_y;

	x = cos(game->player->pa) * game->player->speed * 13;
	y = sin(game->player->pa) * game->player->speed * 13;
	tile_x = (int)(game->player->px + x) / TILE_LEN;
	tile_y = (int)(game->player->py + y) / TILE_LEN;
	if (tile_x < 0 || tile_y < 0 || tile_y >= game->map_rows)
		return ;
	if (!game->map[tile_y] || tile_x >= (int)strlen(game->map[tile_y]))
		return ;
	if (game->map[tile_y][tile_x] == '1')
		return ;
	game->player->px += x;
	game->player->py += y;
}

void	move_back(t_game *game)
{
	float	x;
	float	y;
	int		tile_x;
	int		tile_y;

	x = cos(game->player->pa) * game->player->speed * 13;
	y = sin(game->player->pa) * game->player->speed * 13;
	tile_x = (int)(game->player->px - x) / TILE_LEN;
	tile_y = (int)(game->player->py - y) / TILE_LEN;
	if (tile_x < 0 || tile_y < 0 || tile_y >= game->map_rows)
		return ;
	if (!game->map[tile_y] || tile_x >= (int)strlen(game->map[tile_y]))
		return ;
	if (game->map[tile_y][tile_x] == '1')
		return ;
	game->player->px -= x;
	game->player->py -= y;
}

void	move_strafe_left(t_game *game)
{
	float	x;
	float	y;
	int		tile_x;
	int		tile_y;

	x = cos(game->player->pa - PI / 2) * game->player->speed * 13;
	y = sin(game->player->pa - PI / 2) * game->player->speed * 13;
	tile_x = (int)(game->player->px + x) / TILE_LEN;
	tile_y = (int)(game->player->py + y) / TILE_LEN;
	if (tile_x < 0 || tile_y < 0 || tile_y >= game->map_rows)
		return ;
	if (!game->map[tile_y] || tile_x >= (int)strlen(game->map[tile_y]))
		return ;
	if (game->map[tile_y][tile_x] == '1')
		return ;
	game->player->px += x;
	game->player->py += y;
}

void	move_strafe_right(t_game *game)
{
	float	x;
	float	y;
	int		tile_x;
	int		tile_y;

	x = cos(game->player->pa + PI / 2) * game->player->speed * 13;
	y = sin(game->player->pa + PI / 2) * game->player->speed * 13;
	tile_x = (int)(game->player->px + x) / TILE_LEN;
	tile_y = (int)(game->player->py + y) / TILE_LEN;
	if (tile_x < 0 || tile_y < 0 || tile_y >= game->map_rows)
		return ;
	if (!game->map[tile_y] || tile_x >= (int)strlen(game->map[tile_y]))
		return ;
	if (game->map[tile_y][tile_x] == '1')
		return ;
	game->player->px += x;
	game->player->py += y;
}

int	game_loop(t_game *game)
{
	game->player->speed = 0.25;
	if (game->key_w)
		move_front(game);
	if (game->key_s)
		move_back(game);
	if (game->key_a)
		move_strafe_left(game);
	if (game->key_d)
		move_strafe_right(game);
	if (game->key_left)
		rotate_left(game);
	if (game->key_right)
		rotate_right(game);
	if (game->key_w || game->key_s || game->key_a || game->key_d
		|| game->key_left || game->key_right)
	{
		update_rays(game);
		render_strips(game);
	}
	return (0);
}
