#include "../cub3D.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dest;

    if (!img || !img->adr || x < 0 || y < 0 || x >= img->w || y >= img->h)
        return;

    dest = img->adr + (y * img->line_len) + (x * (img->bits_per_pixel / 8));
    *(unsigned int*)dest = color;
}

unsigned int get_color(t_img *img, int x, int y)
{
    char *dest;

    if (!img || !img->adr || x < 0 || y < 0 || x >= img->w || y >= img->h)
        return(0);
    dest = img->adr + (y * img->line_len) + (x * (img->bits_per_pixel / 8));
    return(*(unsigned int*) dest);
}

void add_cube(t_img *img, int width, int height, int x, int y, int color)
{
    int i;
    int j;

    j = 0;
    while (j < height)
    {
        i = 0;
        while (i < width)
        {
            my_mlx_pixel_put(img, x + j, y + i, color);
            i++;
        }
        j++;
    }
}

void create_map(t_game *game, int height)
{
    int i = 0;
    int j = 0;
    int x = 0;
    int y = 0;
    while (i < height)
    {
        if (!game->map[i]) 
            break;
		j = 0;
		x = 0;
        while (game->map[i][j])
        {
            if (game->map[i][j] == '1')
            {
                x++;                
            }
			if (strchr("0NSEW", game->map[i][j]))
			{
				check_player(game, x, y);
                x++;
            }
            j++;
        }
        y++;
        i++;
    }
}