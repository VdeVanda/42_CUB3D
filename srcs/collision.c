/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 11:26:35 by vabatist          #+#    #+#             */
/*   Updated: 2026/04/22 11:48:11 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/**
 * checks if a given pixel position is blocked.
 * converts pixel coordinates to tile coordinates
 * and returns 1 if the target is a wall ('1')
 * or outside the map bounds (treated as a wall), 0 otherwise.
 * @param g the game instance
 * @param px the x-coordinate in pixels to check
 * @param py the y-coordinate in pixels to check
 * @return 1 if blocked (wall or out of bounds), 0 otherwise
 */
static int	is_wall_at(t_game *g, float px, float py)
{
	int	tx;
	int	ty;

	tx = (int)px / TILE_LEN;
	ty = (int)py / TILE_LEN;
	if (tx < 0 || ty < 0 || ty >= g->map_rows)
		return (1);
	if (!g->map[ty] || tx >= (int)ft_strlen(g->map[ty]))
		return (1);
	return (g->map[ty][tx] == '1');
}

/**
 * checks if the player can stand at the given position
 * without colliding with a wall.
 * @param g the game instance
 * @param x the x-coordinate to check
 * @param y the y-coordinate to check
 * @return 1 if the position is clear, 0 otherwise
 * @note Where you adjust the “hit level”:
 *       change r = 8.0f to whatever you want (6..12 is common).
 */
int	can_stand_at(t_game *g, float x, float y)
{
	const float	r = 8.0f;

	if (is_wall_at(g, x + r, y) || is_wall_at(g, x - r, y))
		return (0);
	if (is_wall_at(g, x, y + r) || is_wall_at(g, x, y - r))
		return (0);
	return (1);
}
