/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:47 by vaires-m          #+#    #+#             */
/*   Updated: 2026/03/25 17:56:46 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	handle_corner_hit(t_ray *ray, float angle, int *tiles)
{
	int		x_mod;
	int		y_mod;

	x_mod = ((tiles[0] % TILE_LEN) + TILE_LEN) % TILE_LEN;
	y_mod = ((tiles[1] % TILE_LEN) + TILE_LEN) % TILE_LEN;
	if (fabs(cos(angle)) > fabs(sin(angle)))
	{
		if (tiles[2] < tiles[4])
			ray->wall_dir = WALL_EAST;
		else
			ray->wall_dir = WALL_WEST;
		ray->tex_x = (float)y_mod / TILE_LEN;
	}
	else
	{
		if (tiles[3] < tiles[5])
			ray->wall_dir = WALL_SOUTH;
		else
			ray->wall_dir = WALL_NORTH;
		ray->tex_x = (float)x_mod / TILE_LEN;
	}
}

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

static void	set_wall_face(t_ray *ray, float angle, int *tiles)
{
	int		x_mod;
	int		y_mod;

	x_mod = ((tiles[0] % TILE_LEN) + TILE_LEN) % TILE_LEN;
	y_mod = ((tiles[1] % TILE_LEN) + TILE_LEN) % TILE_LEN;
	if (tiles[2] != tiles[4] && tiles[3] != tiles[5])
		handle_corner_hit(ray, angle, tiles);
	else if (tiles[2] < tiles[4] || tiles[2] > tiles[4])
	{
		if (tiles[2] < tiles[4])
			ray->wall_dir = WALL_EAST;
		else
			ray->wall_dir = WALL_WEST;
		ray->tex_x = (float)y_mod / TILE_LEN;
	}
	else if (tiles[3] < tiles[5] || tiles[3] > tiles[5])
	{
		if (tiles[3] < tiles[5])
			ray->wall_dir = WALL_SOUTH;
		else
			ray->wall_dir = WALL_NORTH;
		ray->tex_x = (float)x_mod / TILE_LEN;
	}
	else
		handle_same_tile(ray, angle, x_mod, y_mod);
}

t_ray	update_ray(t_game *game, float angle, int x, int y)
{
	t_ray	ray;
	int		tiles[6];
	int		prev[2];
	int		v_len;

	ray.dist = 0.0f;
	ray.tex_x = 0.0f;
	ray.wall_dir = WALL_NORTH;
	prev[0] = x;
	prev[1] = y;
	v_len = 0;
	while (v_len < 4000)
	{
		tiles[0] = x + (cos(angle) * v_len);
		tiles[1] = y + (sin(angle) * v_len);
		tiles[2] = tiles[0] / TILE_LEN;
		tiles[3] = tiles[1] / TILE_LEN;
		if (game->map[tiles[3]][tiles[2]] == '1')
		{
			tiles[4] = prev[0] / TILE_LEN;
			tiles[5] = prev[1] / TILE_LEN;
			set_wall_face(&ray, angle, tiles);
			ray.dist = v_len;
			return (ray);
		}
		prev[0] = tiles[0];
		prev[1] = tiles[1];
		v_len++;
	}
	return (ray);
}

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
		game->rays[i] = update_ray(game, la, game->player->px,
				game->player->py);
		la += angle_step;
		i++;
	}
}
