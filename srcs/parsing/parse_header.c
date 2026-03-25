/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:45:04 by vabatist          #+#    #+#             */
/*   Updated: 2026/03/25 12:09:57 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

/**
 * Parses the header of the .cub file, extracting texture paths,
 * floor and ceiling colors,
 * and validating the presence of all required elements.
 * It reads lines until it has successfully
 * parsed 6 valid header lines (4 textures + 2 colors).
 */
static int	get_tex_index(char *id)
{
	if (ft_strncmp(id, "NO", 3) == 0)
		return (TEX_N);
	if (ft_strncmp(id, "EA", 3) == 0)
		return (TEX_E);
	if (ft_strncmp(id, "SO", 3) == 0)
		return (TEX_S);
	if (ft_strncmp(id, "WE", 3) == 0)
		return (TEX_W);
	return (-1);
}

/**
 * Parses a texture line in the header, which should be in the format
 * "ID path/to/texture.xpm".
 * It validates the format, checks for duplicate texture IDs,
 * and verifies that the specified
 * texture file exists and is readable.
 */
static int	parse_texture_line(char *line, t_game *cub)
{
	char	**parts;
	int		count;
	int		index;
	int		fd;

	parts = ft_split(line, ' ');
	if (!parts)
		return (0);
	count = 0;
	while (parts[count])
		count++;
	if (count != 2)
		return (free_str_arr(parts), 0);
	index = get_tex_index(parts[0]);
	if (index == -1 || cub->tex_paths[index])
		return (free_str_arr(parts), 0);
	fd = open(parts[1], O_RDONLY);
	if (fd < 0)
		return (free_str_arr(parts), 0);
	close(fd);
	cub->tex_paths[index] = ft_strdup(parts[1]);
	free_str_arr(parts);
	return (1);
}

/**
 * Parses a single line from the header, determining
 * if it's a texture line or a color line,
 * and delegating to the appropriate parsing function.
 * It returns 1 if the line was successfully
 * parsed, 0 otherwise.
 */
static int	parse_header_line(char *line, t_game *cub)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture_line(line, cub));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color_line(line, 'F', cub));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color_line(line, 'C', cub));
	return (0);
}

/**
 * Main function to parse the header of the .cub file. It reads lines
 * until it has successfully parsed all required elements.
 */
int	parse_header(t_game *cub, int fd)
{
	char	*line;
	int		parsed;

	parsed = 0;
	while (parsed < 6)
	{
		line = get_next_line(fd);
		if (!line)
			return (parsing_error("Incomplete header"), 0);
		ft_strtrim_nl(line);
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (!parse_header_line(line, cub))
		{
			free(line);
			return (parsing_error("Invalid header element"), 0);
		}
		free(line);
		parsed++;
	}
	return (1);
}
