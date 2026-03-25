/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:00:00 by vabatist          #+#    #+#             */
/*   Updated: 2026/03/25 16:23:28 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_texs(t_game *game)
{
	game->tex_paths[WALL_NORTH] = "./assets/north.xpm";
	game->tex_paths[WALL_EAST] = "./assets/east.xpm";
	game->tex_paths[WALL_SOUTH] = "./assets/south.xpm";
	game->tex_paths[WALL_WEST] = "./assets/west.xpm";
	if (!load_textures(game))
	{
		printf("Error: Texture loading failed.\n");
		return ;
	}
}

void	init_worlds(t_game *game)
{
	game->world_3d = (t_img *)malloc(sizeof(t_img));
	if (!game->world_3d)
		return ;
	game->world_3d->img = mlx_new_image(game->mlx_3d, game->window_w_3d,
			game->window_h_3d);
	if (!game->world_3d->img)
	{
		free(game->world_3d);
		game->world_3d = NULL;
		return ;
	}
	game->world_3d->adr = mlx_get_data_addr(game->world_3d->img,
			&game->world_3d->bits_per_pixel, &game->world_3d->line_len,
			&game->world_3d->endian);
	if (!game->world_3d->adr)
	{
		mlx_destroy_image(game->mlx_3d, game->world_3d->img);
		free(game->world_3d);
		game->world_3d = NULL;
		return ;
	}
	game->world_3d->w = game->window_w_3d;
	game->world_3d->h = game->window_h_3d;
}
