/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:00:00 by vaires-m          #+#    #+#             */
/*   Updated: 2026/04/22 09:21:17 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/**
 * Convert the normalized texture coordinate (0.0 to 1.0)
 * to an actual pixel x coordinate on the wall texture,
 * and clamp it to the valid range of the texture width.
 * This is used to determine which vertical slice of the wall texture
 * to draw for a given ray.
 */
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

/**
 * Convert a screen Y position (screen_y) within the drawn wall slice
 * into a texture Y coordinate (tex_y) for the wall texture.
 */
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

/**
 * Return the final pixel color for a wall fragment by sampling the correct
 * wall texture using the current ray’s hit info.
 * If the texture pointer or its pixel buffer (adr) is missing,
 * return a default gray color (0x808080) to indicate a rendering error.
 * params[0] is treated as the on-screen wall height (wall_size).
 * If it’s <= 0, force it to 1 to avoid division by zero in get_tex_y().
 */
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
