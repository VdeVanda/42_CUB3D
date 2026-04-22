/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:50 by vaires-m          #+#    #+#             */
/*   Updated: 2026/04/22 11:39:21 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/**
 * moves the player forward in the direction they’re facing.
 * Movement is applied per-axis (X then Y) and only if the player hitbox
 * can stand at the new position without colliding with walls.
 */
void	move_front(t_game *game)
{
	float	dx;
	float	dy;
	float	nx;
	float	ny;

	dx = cosf(game->player->pa) * game->player->speed * 13;
	dy = sinf(game->player->pa) * game->player->speed * 13;
	nx = game->player->px + dx;
	ny = game->player->py + dy;
	if (can_stand_at(game, nx, game->player->py))
		game->player->px = nx;
	if (can_stand_at(game, game->player->px, ny))
		game->player->py = ny;
}

/**
 * moves the player backward opposite to the direction they’re facing.
 * Movement is applied per-axis (X then Y) and only if the player hitbox
 * can stand at the new position without colliding with walls.
 */
void	move_back(t_game *game)
{
	float	dx;
	float	dy;
	float	nx;
	float	ny;

	dx = cosf(game->player->pa) * game->player->speed * 13;
	dy = sinf(game->player->pa) * game->player->speed * 13;
	nx = game->player->px - dx;
	ny = game->player->py - dy;
	if (can_stand_at(game, nx, game->player->py))
		game->player->px = nx;
	if (can_stand_at(game, game->player->px, ny))
		game->player->py = ny;
}

/**
 * moves the player to the left (strafe) perpendicular
 * to the direction they’re facing.
 * Movement is applied per-axis (X then Y) and only if the player hitbox
 * can stand at the new position without colliding with walls.
 */
void	move_strafe_left(t_game *game)
{
	float	dx;
	float	dy;
	float	nx;
	float	ny;

	dx = cosf(game->player->pa - PI / 2) * game->player->speed * 13;
	dy = sinf(game->player->pa - PI / 2) * game->player->speed * 13;
	nx = game->player->px + dx;
	ny = game->player->py + dy;
	if (can_stand_at(game, nx, game->player->py))
		game->player->px = nx;
	if (can_stand_at(game, game->player->px, ny))
		game->player->py = ny;
}

/**
 * moves the player to the right (strafe) perpendicular
 * to the direction they’re facing,
 * but only if the destination tile is not a wall and is inside the map.
 */
void	move_strafe_right(t_game *game)
{
	float	dx;
	float	dy;
	float	nx;
	float	ny;

	dx = cosf(game->player->pa + PI / 2) * game->player->speed * 13;
	dy = sinf(game->player->pa + PI / 2) * game->player->speed * 13;
	nx = game->player->px + dx;
	ny = game->player->py + dy;
	if (can_stand_at(game, nx, game->player->py))
		game->player->px = nx;
	if (can_stand_at(game, game->player->px, ny))
		game->player->py = ny;
}

/**
 * handles the main game loop, checking for key states and moving the player
 * accordingly. It updates the rays and re-renders the scene if any movement
 * or rotation keys are pressed.
 */
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
