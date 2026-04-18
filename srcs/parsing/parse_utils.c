/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:33:37 by vabatist          #+#    #+#             */
/*   Updated: 2026/04/18 18:20:34 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

/**
 * Prints a parsing error message to standard output. This function is used
 * throughout the parsing process to report specific issues encountered in the
 * .cub file, such as missing elements, invalid formats, or map issues.
 * It provides a centralized way to handle error reporting during parsing.
 */
void	parsing_error(char *msg)
{
	ft_printf("Error\n%s\n", msg);
}

/**
 * Frees a NULL-terminated array of strings. This is used to clean up memory
 * allocated by functions like ft_split() after we're done processing the array.
 * It iterates through the array, freeing each individual string, and then frees
 * the array itself.
 */
void	free_str_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * Trims newline characters from the end of a string, if present.
 * This is useful for cleaning up lines read
 * from a file before further processing.
 */
char	*ft_strtrim_nl(char *str)
{
	int	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}

/**
 * Pads a line with spaces to ensure it matches the maximum column width
 * of the map. This is necessary for consistent indexing when rendering
 * the map later. It allocates a new string of the specified width,
 * copies the original line into it, and fills the rest with spaces
 * if the original line is shorter.
 */
char	*pad_line(char *line, int width)
{
	char	*new_line;
	int		i;

	new_line = malloc(width + 1);
	if (!new_line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}
