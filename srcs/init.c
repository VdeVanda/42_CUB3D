/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaires-m <vaires-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:54 by vaires-m          #+#    #+#             */
/*   Updated: 2026/03/24 13:00:55 by vaires-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

t_ray	*init_rays(t_game *game, int nbr)
{
	int		i;
	t_ray	*rays;

	i = 0;
	rays = malloc(sizeof(t_ray) * nbr);
	if (!rays)
		return (NULL);
	while (i < nbr)
	{
		rays[i].dist = 0.0f;
		rays[i].tex_x = 0.0f;
		rays[i].wall_dir = WALL_NORTH;
		i++;
	}
	game->rays_count = i;
	printf("%d \n", game->rays_count);
	return (rays);
}

static void	init_game_keys(t_game *game)
{
	game->key_w = 0;
	game->key_a = 0;
	game->key_s = 0;
	game->key_d = 0;
	game->key_left = 0;
	game->key_right = 0;
	game->key_up = 0;
	game->key_down = 0;
}

static void	init_game_values(t_game *game)
{
	game->rays_count = 0;
	game->mlx_3d = NULL;
	game->win_3d = NULL;
	game->world_3d = NULL;
	game->map = NULL;
	game->map_rows = 0;
	game->map_cols = 0;
	game->window_w_3d = 1500;
	game->window_h_3d = 1000;
	game->window_w = 0;
	game->window_h = 0;
}

int	init_structs(t_game **game)
{
	*game = (t_game *)malloc(sizeof(t_game));
	if (!*game)
		return (1);
	(*game)->player = (t_player *)malloc(sizeof(t_player));
	if (!(*game)->player)
	{
		free(*game);
		return (1);
	}
	init_game_values(*game);
	init_game_keys(*game);
	(*game)->rays = init_rays(*game, (*game)->window_w_3d);
	if (!(*game)->rays)
	{
		free((*game)->player);
		free(*game);
		return (1);
	}
	return (0);
}

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
