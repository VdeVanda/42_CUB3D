/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 12:36:59 by vabatist          #+#    #+#             */
/*   Updated: 2026/03/11 19:20:13 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

/**
 * Checks if the provided string is a valid color representation (only digits).
 */
static int	is_valid_color_str(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n' && str[i] != '\r')
	{
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Parses a color string in the format "R,G,B" and returns the corresponding
 */
static unsigned int	parse_color_value(char *str)
{
	char	**rgb;
	int		i;
	unsigned int		r;
	unsigned int		g;
	unsigned int		b;
	char	*trimmed;

	trimmed = ft_strtrim(str, "\n\r\t ");
	if (!trimmed)
		return (-1);
	rgb = ft_split(trimmed, ',');
	free(trimmed);
	if (!rgb)
		return (-1);
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3 || !is_valid_color_str(rgb[0])
		|| !is_valid_color_str(rgb[1]) || !is_valid_color_str(rgb[2]))
		return (free_str_arr(rgb), -1);
	r = (unsigned int)ft_atoi(rgb[0]);
	g = (unsigned int)ft_atoi(rgb[1]);
	b = (unsigned int)ft_atoi(rgb[2]);
	free_str_arr(rgb);
	if (r > 255 || g > 255 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

/**
 * Assigns the parsed color to the appropriate field in the game struct based on the type ('F' for floor, 'C' for ceiling).
 */
static int	assign_color(char type, int color, t_game *cub)
{
	if (type == 'F')
	{
		cub->floor_color = color;
	}
	else if (type == 'C')
	{
		cub->ceiling_color = color;
	}
	else
		return (0);
	return (1);
}

/**
 * Parses a color line from the configuration file, validates it, and assigns it to the game struct.
 */
int	parse_color_line(char *line, char type, t_game *cub)
{
	char	**parts;
	int		count;
	int		color;

	parts = ft_split(line, ' ');
	if (!parts)
		return (0);
	count = 0;
	while (parts[count])
		count++;
	if (count != 2)
		return (free_str_arr(parts), 0);
	color = (int)parse_color_value(parts[1]);
	free_str_arr(parts);
	if (color == -1)
		return (0);
	return (assign_color(type, color, cub));
}
