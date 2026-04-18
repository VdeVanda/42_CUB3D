/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:09:23 by vabatist          #+#    #+#             */
/*   Updated: 2026/04/18 17:38:55 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

/**
 * Checks if the map is properly enclosed by walls
 * and has exactly one player start.
 */
static int	is_valid_neighbor(char c)
{
	return (c != ' ' && c != '\0' && c != '\n');
}

static int	check_cell(t_game *cub, int x, int y)
{
	if (y == 0 || y == cub->map_rows - 1
		|| x == 0 || x == cub->map_cols - 1)
		return (0);
	if (!is_valid_neighbor(cub->map[y - 1][x]))
		return (0);
	if (!is_valid_neighbor(cub->map[y + 1][x]))
		return (0);
	if (!is_valid_neighbor(cub->map[y][x - 1]))
		return (0);
	if (!is_valid_neighbor(cub->map[y][x + 1]))
		return (0);
	return (1);
}

/**
 * It first ensures the cell is properly enclosed (not on the border and not
 * adjacent to "void" such as spaces or end-of-line) by delegating to
 * check_cell(). If the cell contains a player start marker, it stores the
 * player start position/direction in @p cub, converts the marker to '0'
 * (floor) in the map, and increments @p player_count.
 */
static int	check_walkable_cell(t_game *cub, int x, int y, int *player_count)
{
	if (!check_cell(cub, x, y))
		return (parsing_error("Map is not enclosed by walls"), 0);
	if (ft_strchr("NSEW", cub->map[y][x]))
	{
		cub->player_start_col = x;
		cub->player_start_row = y;
		cub->player_start_dir = cub->map[y][x];
		cub->map[y][x] = '0';
		(*player_count)++;
	}
	return (1);
}

/**
 * Validates the map by iterating through each cell and checking:
 * - If it's a walkable cell ('0' or player start), it calls check_walk
 * to ensure it's properly enclosed and counts player starts.
 * - If it's an invalid character (not '0', '1', space, or player start),
 * it returns an error.
 * Finally, it checks that there is exactly one player start position.
 */
int	validate_map(t_game *cub)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < cub->map_rows)
	{
		x = 0;
		while (x < cub->map_cols)
		{
			if (cub->map[y][x] == '0' || ft_strchr("NSEW", cub->map[y][x]))
			{
				if (!check_walkable_cell(cub, x, y, &player_count))
					return (0);
			}
			else if (cub->map[y][x] != '1' && cub->map[y][x] != ' ')
				return (parsing_error("Invalid character in map"), 0);
			x++;
		}
		y++;
	}
	if (player_count != 1)
		return (parsing_error("Must have exactly one player start"), 0);
	return (1);
}
