/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vabatist <vabatist@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 17:33:37 by vabatist          #+#    #+#             */
/*   Updated: 2026/03/11 19:21:28 by vabatist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	parsing_error(char *msg)
{
	ft_printf("\n  \033[1;31mError: %s\033[0m\n\n", msg);
	ft_printf("  \033[1;33mUsage:\033[0m ./cub3d assets/map.cub\n");
}

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
 * This is useful for cleaning up lines read from a file before further processing.
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
