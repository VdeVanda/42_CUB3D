/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:50 by vaires-m          #+#    #+#             */
/*   Updated: 2026/03/24 13:00:51 by vaires-m         ###   ########.fr       */
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

void	rotate_left(t_game *game)
{
	game->player->pa -= game->player->speed / 2;
	game->player->fovra = game->player->pa + FOV;
	game->player->fovla = game->player->pa - FOV;
}

void	rotate_right(t_game *game)
{
	game->player->pa += game->player->speed / 2;
	game->player->fovra = game->player->pa + FOV;
	game->player->fovla = game->player->pa - FOV;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->key_w = 1;
	if (keycode == KEY_A)
		game->key_a = 1;
	if (keycode == KEY_S)
		game->key_s = 1;
	if (keycode == KEY_D)
		game->key_d = 1;
	if (keycode == KEY_LEFT)
		game->key_left = 1;
	if (keycode == KEY_RIGHT)
		game->key_right = 1;
	if (keycode == KEY_ESC)
		close_window(game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->key_w = 0;
	if (keycode == KEY_A)
		game->key_a = 0;
	if (keycode == KEY_S)
		game->key_s = 0;
	if (keycode == KEY_D)
		game->key_d = 0;
	if (keycode == KEY_LEFT)
		game->key_left = 0;
	if (keycode == KEY_RIGHT)
		game->key_right = 0;
	return (0);
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
	int	moved;

	moved = 0;
	game->player->speed = 0.25;
	if (game->key_w)
	{
		move_front(game);
		moved = 1;
	}
	if (game->key_s)
	{
		move_back(game);
		moved = 1;
	}
	if (game->key_a)
	{
		move_strafe_left(game);
		moved = 1;
	}
	if (game->key_d)
	{
		move_strafe_right(game);
		moved = 1;
	}
	if (game->key_left)
	{
		rotate_left(game);
		moved = 1;
	}
	if (game->key_right)
	{
		rotate_right(game);
		moved = 1;
	}
	if (moved)
	{
		update_rays(game);
		render_strips(game);
	}
	return (0);
}
