/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by vabatist          #+#    #+#             */
/*   Updated: 2026/03/25 17:05:13 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
