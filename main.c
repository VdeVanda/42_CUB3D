/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:58 by vaires-m          #+#    #+#             */
/*   Updated: 2026/04/15 14:32:17 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_texture_paths(t_game *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->tex_paths[i])
		{
			free(cub->tex_paths[i]);
			cub->tex_paths[i] = NULL;
		}
		i++;
	}
}

void	free_parsing_data(t_game *cub)
{
	int	i;

	free_texture_paths(cub);
	if (cub->map)
	{
		i = 0;
		while (cub->map[i])
		{
			free(cub->map[i]);
			i++;
		}
		free(cub->map);
		cub->map = NULL;
	}
}

static int	init_game(t_game **game, char *map_file)
{
	if (init_structs(game))
		return (ft_printf("Error\nInit structs failed.\n"), 1);
	init_parsing_data(*game);
	if (!parse_cub_file(*game, map_file))
		return (free_parsing_data(*game), cleanup_game(*game), 1);
	(*game)->mlx_3d = mlx_init();
	if (!(*game)->mlx_3d)
		return (ft_printf("Error\nMLX init failed.\n"), cleanup_game(*game), 1);
	init_worlds(*game);
	if (!(*game)->world_3d || !(*game)->world_3d->img)
		return (ft_printf("Error\nWorld init failed.\n"), cleanup_game(*game),
			1);
	init_texs(*game);
	if (!(*game)->tex_wall[0].img)
		return (ft_printf("Error\nTexture loading failed.\n"),
			cleanup_game(*game), 1);
	return (0);
}

static int	load_game_map(t_game *game)
{
	game->win_3d = mlx_new_window(game->mlx_3d, game->window_w_3d,
			game->window_h_3d, "cub3D");
	if (!game->win_3d)
		return (ft_printf("Error\nWindow creation failed.\n"),
			cleanup_game(game), 1);
	init_player_from_start(game);
	update_rays(game);
	render_strips(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	*game;

	if (argc != 2)
	{
		parsing_error("Wrong number of arguments");
		ft_printf("  \033[1;33mUsage:\033[0m ./cub3D maps/map.cub\n\n");
		return (1);
	}
	if (init_game(&game, argv[1]))
		return (1);
	if (load_game_map(game))
		return (1);
	mlx_hook(game->win_3d, 17, 0, close_window, game);
	mlx_hook(game->win_3d, 2, 1L << 0, key_press, game);
	mlx_hook(game->win_3d, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx_3d, game_loop, game);
	mlx_loop(game->mlx_3d);
	cleanup_game(game);
	return (0);
}
