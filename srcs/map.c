#include "../cub3D.h"

void print_map(t_game *game, int height)
{
    int i = 0;
    int j = 0;
    while (i < height)
    {
		j = 0;
        while (game->map[i][j])
        {
			printf("%c ", game->map[i][j]);
            j++;
        }
		printf("\n");
        i++;
    }
}

int count_map_col(char *file)
{
    size_t len = 0;
    int fd = open(file, O_RDONLY);
    if (fd < 0)
        return(0);
    char *line;
    while ((line = get_next_line(fd)))
	{
        if(strlen(line) > len)
            len = strlen(line);
		free(line);
	}
    close(fd);
    return(len - 1);
}

int count_map_rows(char *file)
{
    int len = 0;
    int fd = open(file, O_RDONLY);
    if (fd < 0)
        return(0);
    char *line;
    while ((line = get_next_line(fd)))
	{
		free(line);
		len++;
	}
    close(fd);
    return(len);
}

char **load_map(char *file, int height)
{
    char **map = malloc(sizeof(char *) * (height + 1));
    if (!map)
        return (NULL);
    
    int k = 0;
    while (k <= height)
        map[k++] = NULL;
    
    int i = 0;
    int fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        free(map);
        return (NULL);
    }
    
    char *line;
    while ((line = get_next_line(fd)))
    {
        if (i < height)
            map[i] = line;
        else 
            free(line);
        i++;
    }
    return(map);
}

void render_map(t_game *game)
{
    mlx_put_image_to_window(game->mlx_2d, game->win_2d, game->world_2d->img, 0, 0);
}