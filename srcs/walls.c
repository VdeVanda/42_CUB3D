/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:45 by vaires-m          #+#    #+#             */
/*   Updated: 2026/03/24 13:00:46 by vaires-m         ###   ########.fr       */
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

static int	get_tex_x(t_img *wall_tex, float tex_x_norm)
{
	int	tex_x;

	if (tex_x_norm < 0.0f)
		tex_x_norm = 0.0f;
	if (tex_x_norm >= 1.0f)
		tex_x_norm = 0.999f;
	tex_x = (int)(tex_x_norm * wall_tex->w);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= wall_tex->w)
		tex_x = wall_tex->w - 1;
	return (tex_x);
}

static int	get_tex_y(t_img *wall_tex, int wall_size, int y_start, int screen_y)
{
	int	tex_y;

	tex_y = ((screen_y - y_start) * wall_tex->h) / wall_size;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= wall_tex->h)
		tex_y = wall_tex->h - 1;
	return (tex_y);
}

unsigned int	get_wall_color(t_game *game, int params[3], int ray_idx)
{
	int		tex_x;
	int		tex_y;
	t_img	*wall_tex;

	wall_tex = &game->tex_wall[game->rays[ray_idx].wall_dir];
	if (!wall_tex || !wall_tex->adr)
		return (0x808080);
	if (params[0] <= 0)
		params[0] = 1;
	tex_x = get_tex_x(wall_tex, game->rays[ray_idx].tex_x);
	tex_y = get_tex_y(wall_tex, params[0], params[1], params[2]);
	return (get_color(wall_tex, tex_x, tex_y));
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
