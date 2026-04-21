/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2026/04/19 19:21:09 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	set_wall_face(t_ray *ray, t_game *game, float angle, int *tiles);

/**
 * helper called after a ray hits a wall.
 * It packages hit data into a convenient form
 * and writes the final info into the t_ray:
 * - Copies the hit point in pixels
 * - Converts hit point to tile coordinates
 * - Converts the previous ray position to previous tile coords
 * - Calls set_wall_face to determine which wall face (N/S/E/W) was hit
 * - Stores the hit distance
 */
static void	apply_wall_hit(t_game *g, t_ray *r, float ang, int *packed)
{
	int	tiles[6];

	tiles[0] = packed[0];
	tiles[1] = packed[1];
	tiles[2] = packed[0] / TILE_LEN;
	tiles[3] = packed[1] / TILE_LEN;
	tiles[4] = packed[4] / TILE_LEN;
	tiles[5] = packed[5] / TILE_LEN;
	set_wall_face(r, g, ang, tiles);
	r->dist = packed[6];
}

/**
 * shoots a ray from the starting point at direction angle
 * and advances it forward in 1-pixel steps to 3999.
 * 4000 is just a hard maximum ray length (a “view distance” / safety cap)
 * so the loop can’t run forever if the ray never hits a wall.
 * When it hits a wall, it calls apply_wall_hit() to fill the ray data
 * and returns the t_ray. If no wall is found within the 4000-step limit,
 * it returns the default-initialized ray.
 */
static t_ray	cast_ray(t_game *game, float angle, int x, int y)
{
	t_ray	ray;
	int		packed[7];
	int		prev[2];
	int		vl;

	ray.dist = 0.0f;
	ray.tex_x = 0.0f;
	ray.wall_dir = WALL_NORTH;
	prev[0] = x;
	prev[1] = y;
	vl = 0;
	while (vl < 4000)
	{
		packed[0] = x + (int)(cos(angle) * vl);
		packed[1] = y + (int)(sin(angle) * vl);
		packed[4] = prev[0];
		packed[5] = prev[1];
		packed[6] = vl;
		if (game->map[packed[1] / TILE_LEN][packed[0] / TILE_LEN] == '1')
			return (apply_wall_hit(game, &ray, angle, packed), ray);
		prev[0] = packed[0];
		prev[1] = packed[1];
		vl++;
	}
	return (ray);
}

/**
 * updates all the rays in the game by casting them from the player's position
 * at the appropriate angles based on the player's field of view. It iterates
 * through each ray index, calculates the angle for that ray,
 * and calls cast_ray() to fill the ray data in the game structure.
 * Starts from the player’s left FOV angle (fovla).
 */
void	update_rays(t_game *game)
{
	int		i;
	float	la;
	float	angle_step;

	i = 0;
	la = game->player->fovla;
	angle_step = (2 * FOV) / game->rays_count;
	while (i < game->rays_count)
	{
		game->rays[i] = cast_ray(game, la, game->player->px,
				game->player->py);
		la += angle_step;
		i++;
	}
}
