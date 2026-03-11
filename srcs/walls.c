#include "../cub3D.h"

static void	draw_sky_floor(t_game *cub, int x, int wall_top, int wall_bottom)
{
	int	y;

	y = 0;
	while (y < wall_top)
	{
		my_mlx_pixel_put(cub->world_3d, x, y, cub->ceiling_color);
		y++;
	}
	y = wall_bottom;
	while (y < cub->window_h_3d)
	{
		my_mlx_pixel_put(cub->world_3d, x, y, cub->floor_color);
		y++;
	}
}

unsigned int get_wall_color(t_game *game, int wall_size, int y_start, int screen_y, int ray_index)
{
    int tex_x;
    int tex_y;
    int wall_dir;
    t_img *wall_tex;

    // Get the wall direction for this ray
    wall_dir = game->wall_direction[ray_index];
    wall_tex = &game->tex_wall[wall_dir];

    if (!wall_tex || !wall_tex->adr)
        return (0x808080);

    if (wall_size <= 0)
        wall_size = 1;

    tex_x = game->tex_float[ray_index] * wall_tex->w;
    tex_y = ((screen_y - y_start) * wall_tex->h) / wall_size;

    if (tex_x >= wall_tex->w)
        tex_x = wall_tex->w - 1;
    if (tex_y >= wall_tex->h)
        tex_y = wall_tex->h - 1;

    return (get_color(wall_tex, tex_x, tex_y));
}

void create_strip(t_game *game, int screen_height, int ray_len, int x, int ray_index)
{
    int i;

    if (ray_len == 0)
        ray_len = 1;
    int hall_height = (TILE_LEN * screen_height) / ray_len;
    int y_start = (screen_height / 2) - (hall_height / 2);
    int y_end = (screen_height / 2) + (hall_height / 2);

    draw_sky_floor(game, x, y_start, y_end);

    // Draw wall column
    i = y_start;
    while (i <= y_end && i < game->window_h_3d)
    {
        my_mlx_pixel_put(game->world_3d, x, i, get_wall_color(game, hall_height, y_start, i, ray_index));
        i++;
    }
}

void update_strips(t_game *game)
{
    int x = 0;

    // One ray per screen column
    while(x < game->window_w_3d)
    {
        create_strip(game, game->window_h_3d, game->rays[x], x, x);
        x++;
    }
}

void render_strips(t_game *game)
{
    update_strips(game);
    mlx_put_image_to_window(game->mlx_3d, game->win_3d, game->world_3d->img, 0, 0);
}
