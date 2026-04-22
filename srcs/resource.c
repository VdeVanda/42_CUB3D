/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resource.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:00:00 by vabatist          #+#    #+#             */
/*   Updated: 2026/04/22 12:28:15 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/**
 * initializes the game’s textures.
 * Calls load_textures(game) to load all required texture images into game.
 * If loading fails, prints error message.
 */
int	init_texs(t_game *game)
{
	if (!load_textures(game))
	{
		ft_printf("Error\nTexture loading failed.\n");
		return (0);
	}
	return (1);
}

/**
 * Initializes the main 3D world image buffer (game->world_3d) where the final
 * rendered scene will be drawn each frame. It creates a new image with the
 * same dimensions as the game window and retrieves its data address for pixel
 * manipulation. If any step fails, it cleans up and sets world_3d to NULL.
 */
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
