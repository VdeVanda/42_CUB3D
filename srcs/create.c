/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:56 by vaires-m          #+#    #+#             */
/*   Updated: 2026/04/18 19:01:51 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/**
 * Puts a pixel of a specified color at the given (x, y) coordinates in the
 * provided image. It calculates the memory address for the pixel based on the
 * image's data address, line length, and bits per pixel. It also includes
 * bounds checking to ensure that the (x, y) coordinates are within the
 * dimensions of the image before attempting to write the color value.
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (!img || !img->adr || x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dest = img->adr + (y * img->line_len) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

/**
 * Retrieves the color value of a pixel at the specified (x, y) coordinates from
 * the provided image. It calculates the memory address for the pixel based on
 * the image's data address, line length, and bits per pixel. It also includes
 * bounds checking to ensure that the (x, y) coordinates are within the
 * dimensions of the image before attempting to read the color value.
 */
unsigned int	get_color(t_img *img, int x, int y)
{
	char	*dest;

	if (!img || !img->adr || x < 0 || y < 0 || x >= img->w || y >= img->h)
		return (0);
	dest = img->adr + (y * img->line_len) + (x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dest);
}

static int	set_texture(t_game *cub, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx_3d, path, &tex->w, &tex->h);
	if (!tex->img)
		return (0);
	tex->adr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_len, &tex->endian);
	if (!tex->adr)
		return (0);
	return (1);
}

int	load_textures(t_game *cub)
{
	if (!set_texture(cub, &cub->tex_wall[TEX_N], cub->tex_paths[TEX_N]))
		return (0);
	if (!set_texture(cub, &cub->tex_wall[TEX_E], cub->tex_paths[TEX_E]))
		return (0);
	if (!set_texture(cub, &cub->tex_wall[TEX_S], cub->tex_paths[TEX_S]))
		return (0);
	if (!set_texture(cub, &cub->tex_wall[TEX_W], cub->tex_paths[TEX_W]))
		return (0);
	return (1);
}
