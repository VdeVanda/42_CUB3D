/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:34:58 by vabatist          #+#    #+#             */
/*   Updated: 2026/03/11 19:20:22 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

/**
 * Initializes parsing-related fields in the game struct to default values.
 */
void	init_parsing_data(t_game *cub)
{
	cub->map = NULL;
	cub->map_rows = 0;
	cub->map_cols = 0;
	cub->tex_paths[TEX_N] = NULL;
	cub->tex_paths[TEX_E] = NULL;
	cub->tex_paths[TEX_S] = NULL;
	cub->tex_paths[TEX_W] = NULL;
	cub->floor_color = -1;
	cub->ceiling_color = -1;
	cub->player_start_dir = 0;
	cub->player_start_col = 0;
	cub->player_start_row = 0;
}

static int	validate_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (parsing_error("Invalid file name"), 0);
	if (ft_strncmp(".cub", filename + len - 4, 4) != 0)
		return (parsing_error("Map file must end with .cub"), 0);
	return (1);
}
/**
 * Main parsing function that reads the .cub file, extracts textures, colors, and map data,
 * and validates the map structure.
 */
int	parse_cub_file(t_game *cub, char *filename)
{
	int	fd;

	init_parsing_data(cub);
	if (!validate_filename(filename))
		return (0);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (parsing_error("Cannot open file"), 0);
	if (!parse_header(cub, fd))
	{
		close(fd);
		return (0);
	}
	if (!count_map_dimensions(cub, fd))
	{
		close(fd);
		return (parsing_error("No map found in file"), 0);
	}
	close(fd);
	if (!load_map(cub, filename))
		return (0);
	if (!validate_map(cub))
		return (0);
	return (1);
}

