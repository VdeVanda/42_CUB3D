/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:45 by vaires-m          #+#    #+#             */
/*   Updated: 2026/03/25 16:47:33 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	draw_sky_floor(t_game *cub, int x, int wall_top, int wall_bottom)
{
	int	y;

	y = 0;
	while (y < wall_top)
	{
		my_mlx_pixel_put(cub->world_3d, x, y, cub->ceiling_color);
		y++;
	}
	y = wall_bottom;
	while (y < cub->window_h_3d)
	{
		my_mlx_pixel_put(cub->world_3d, x, y, cub->floor_color);
		y++;
	}
}

void	create_strip(t_game *game, int x)
{
	int	i;
	int	hall_height;
	int	y_start;
	int	y_end;
	int	params[3];

	if (game->rays[x].dist == 0)
		game->rays[x].dist = 1;
	hall_height = (TILE_LEN * game->window_h_3d) / game->rays[x].dist;
	y_start = (game->window_h_3d / 2) - (hall_height / 2);
	y_end = (game->window_h_3d / 2) + (hall_height / 2);
	draw_sky_floor(game, x, y_start, y_end);
	params[0] = hall_height;
	params[1] = y_start;
	i = y_start;
	while (i <= y_end && i < game->window_h_3d)
	{
		params[2] = i;
		my_mlx_pixel_put(game->world_3d, x, i,
			get_wall_color(game, params, x));
		i++;
	}
}

void	update_strips(t_game *game)
{
	int	x;

	x = 0;
	while (x < game->window_w_3d)
	{
		create_strip(game, x);
		x++;
	}
}

void	render_strips(t_game *game)
{
	update_strips(game);
	mlx_put_image_to_window(game->mlx_3d, game->win_3d,
		game->world_3d->img, 0, 0);
}
