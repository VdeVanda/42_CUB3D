/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:47 by vaires-m          #+#    #+#             */
/*   Updated: 2026/04/22 13:39:40 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/**
 * helper called when a ray hits a wall tile but the hit point is exactly on the
 * boundary between two tiles. It determines the wall face based on the ray angle
 * and the position of the hit point within the tile, and sets the ray's wall_dir
 * and tex_x accordingly.
 * 
 * tiles[] layout used by set_wall_face helpers:
 * [0] hit_x_px      : hit position x in pixels
 * [1] hit_y_px      : hit position y in pixels
 * [2] hit_tile_x    : hit_x_px / TILE_LEN
 * [3] hit_tile_y    : hit_y_px / TILE_LEN
 * [4] prev_tile_x   : previous ray x tile coordinate
 * [5] prev_tile_y   : previous ray y tile coordinate
*/
static void	handle_same_tile(t_ray *ray, float angle, int x_mod, int y_mod)
{
	float	dx;
	float	dy;

	dx = cos(angle);
	dy = sin(angle);
	if (fabs(dx) > fabs(dy))
	{
		if (dx > 0)
			ray->wall_dir = WALL_WEST;
		else
			ray->wall_dir = WALL_EAST;
		ray->tex_x = (float)y_mod / TILE_LEN;
	}
	else
	{
		if (dy > 0)
			ray->wall_dir = WALL_NORTH;
		else
			ray->wall_dir = WALL_SOUTH;
		ray->tex_x = (float)x_mod / TILE_LEN;
	}
}

/**
 * helper for when the ray hits a vertical tile boundary (E/W face).
 * It compares the adjacent tiles to determine if the hit is on an E or W face,
 * and calculates the texture coordinate based on the y_mod of the hit point.
 */
static void	handle_ew_face(t_ray *ray, int *mods, int *tiles)
{
	if (tiles[2] < tiles[4])
		ray->wall_dir = WALL_EAST;
	else
		ray->wall_dir = WALL_WEST;
	ray->tex_x = (float)mods[1] / TILE_LEN;
}

/**
 * helper for when the ray hits a horizontal tile boundary (N/S face).
 * It compares the adjacent tiles to determine if the hit is on a N or S face,
 * and calculates the texture coordinate based on the x_mod of the hit point.
 */
static void	handle_ns_face(t_ray *ray, int *mods, int *tiles)
{
	if (tiles[3] < tiles[5])
		ray->wall_dir = WALL_SOUTH;
	else
		ray->wall_dir = WALL_NORTH;
	ray->tex_x = (float)mods[0] / TILE_LEN;
}

/**
 * Determine which wall face (N/S/E/W) the ray hit
 * and compute the ray’s texture coordinate.
 * - Primary decision is based on which tile boundary was hit
 *   (vertical vs horizontal).
 * -If it’s ambiguous (corner), it checks neighboring map cells
 *   (xy_free, yx_free).
 * - If still not clear, fall back to inferring the face from the ray direction
 *   (angle) via handle_same_tile().
 */
void	set_wall_face(t_ray *ray, t_game *game, float angle, int *tiles)
{
	int	mods[2];
	int	yx_free;
	int	xy_free;

	mods[0] = ((tiles[0] % TILE_LEN) + TILE_LEN) % TILE_LEN;
	mods[1] = ((tiles[1] % TILE_LEN) + TILE_LEN) % TILE_LEN;
	if (tiles[2] == tiles[4] && tiles[3] == tiles[5])
		handle_same_tile(ray, angle, mods[0], mods[1]);
	else if (tiles[2] == tiles[4])
		handle_ns_face(ray, mods, tiles);
	else if (tiles[3] == tiles[5])
		handle_ew_face(ray, mods, tiles);
	else
	{
		yx_free = (game->map[tiles[5]][tiles[2]] != '1');
		xy_free = (game->map[tiles[3]][tiles[4]] != '1');
		if (!xy_free)
			handle_ns_face(ray, mods, tiles);
		else if (!yx_free)
			handle_ew_face(ray, mods, tiles);
		else
			handle_same_tile(ray, angle, mods[0], mods[1]);
	}
}
