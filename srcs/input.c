/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:10:00 by vabatist          #+#    #+#             */
/*   Updated: 2026/04/19 17:25:42 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/**
 * handles key press events.
 */
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

/**
 * handles key release events.
 */
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

/**
 * rotates the player to the left by adjusting the player's angle (pa)
 * and updating the field of view angles (fovra and fovla) accordingly.
 * The rotation speed is determined by the player's speed divided by 2,
 * which allows for smoother rotation.
 */
void	rotate_left(t_game *game)
{
	game->player->pa -= game->player->speed / 2;
	game->player->fovra = game->player->pa + FOV;
	game->player->fovla = game->player->pa - FOV;
}

/**
 * rotates the player to the right by adjusting the player's angle (pa)
 * and updating the field of view angles (fovra and fovla) accordingly.
 * The rotation speed is determined by the player's speed divided by 2,
 * which allows for smoother rotation.
 */
void	rotate_right(t_game *game)
{
	game->player->pa += game->player->speed / 2;
	game->player->fovra = game->player->pa + FOV;
	game->player->fovla = game->player->pa - FOV;
}
