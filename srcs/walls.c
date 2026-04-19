/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:45 by vaires-m          #+#    #+#             */
/*   Updated: 2026/04/19 17:14:39 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/**
 * paints the ceiling and floor for a single vertical column x of the screen,
 * leaving the wall area (between wall_top and wall_bottom)
 * for another function to draw.
 */
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

/**
 * renders one vertical screen column x of the 3D view:
 * it computes the projected wall height from the ray distance,
 * centers that wall slice on the screen,
 * draws ceiling and floor for that column,
 * then fills the wall slice pixel-by-pixel using the correct texture color
 */
void	create_strip(t_game *game, int x)
{
	int	i;
	int	wall_height;
	int	y_start;
	int	y_end;
	int	params[3];

	if (game->rays[x].dist == 0)
		game->rays[x].dist = 1;
	wall_height = (TILE_LEN * game->window_h_3d) / game->rays[x].dist;
	y_start = (game->window_h_3d / 2) - (wall_height / 2);
	y_end = (game->window_h_3d / 2) + (wall_height / 2);
	draw_sky_floor(game, x, y_start, y_end);
	params[0] = wall_height;
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

/**
 * renders the whole 3D frame column by column.
 */
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

/**
 * renders the whole 3D frame by first updating all the strips (columns)
 * and then putting the resulting world_3d image to the window
 * using mlx_put_image_to_window().
 */
void	render_strips(t_game *game)
{
	update_strips(game);
	mlx_put_image_to_window(game->mlx_3d, game->win_3d,
		game->world_3d->img, 0, 0);
}
