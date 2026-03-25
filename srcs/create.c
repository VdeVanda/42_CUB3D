/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:56 by vaires-m          #+#    #+#             */
/*   Updated: 2026/03/25 12:48:31 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (!img || !img->adr || x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	dest = img->adr + (y * img->line_len) + (x * (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

unsigned int	get_color(t_img *img, int x, int y)
{
	char	*dest;

	if (!img || !img->adr || x < 0 || y < 0 || x >= img->w || y >= img->h)
		return (0);
	dest = img->adr + (y * img->line_len) + (x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dest);
}

static void	draw_cube_line(t_img *img, int params[3], int color)
{
	int	i;

	i = 0;
	while (i < params[2])
	{
		my_mlx_pixel_put(img, params[0] + i, params[1], color);
		i++;
	}
}

void	add_cube(t_img *img, int params[4], int color)
{
	int	j;
	int	line_params[3];

	j = 0;
	line_params[2] = params[0];
	while (j < params[1])
	{
		line_params[0] = params[2];
		line_params[1] = params[3] + j;
		draw_cube_line(img, line_params, color);
		j++;
	}
}

void	create_map(t_game *game, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		if (!game->map[i])
			break ;
		j = 0;
		while (game->map[i][j])
		{
			if (strchr("NSEW", game->map[i][j]))
				check_player(game, j, i);
			j++;
		}
		i++;
	}
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
