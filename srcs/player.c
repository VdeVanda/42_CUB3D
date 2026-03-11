#include "../cub3D.h"

void check_player(t_game *game, int x, int y)
{
    if (!game->map[y])
		return;

	if (game->map[y][x] == 'N')
    {
		game->player->px = x * TILE_LEN + (TILE_LEN / 2);
		game->player->py = y * TILE_LEN + (TILE_LEN / 2);
		game->player->pa = 3 * PI / 2;
        game->player->fovla = game->player->pa - FOV;
        game->player->fovra = game->player->pa + FOV;
    }
	if (game->map[y][x] == 'S')
    {
		game->player->px = x * TILE_LEN + (TILE_LEN / 2);
		game->player->py = y * TILE_LEN + (TILE_LEN / 2);
		game->player->pa = PI / 2;
        game->player->fovla = game->player->pa - FOV;
        game->player->fovra = game->player->pa + FOV;
    }
	if (game->map[y][x] == 'W')
    {
		game->player->px = x * TILE_LEN + (TILE_LEN / 2);
		game->player->py = y * TILE_LEN + (TILE_LEN / 2);
		game->player->pa = PI;
        game->player->fovla = game->player->pa - FOV;
        game->player->fovra = game->player->pa + FOV;
    }
	if (game->map[y][x] == 'E')
    {
		game->player->px = x * TILE_LEN + (TILE_LEN / 2);
		game->player->py = y * TILE_LEN + (TILE_LEN / 2);
		game->player->pa = 0;
        game->player->fovla = game->player->pa - FOV;
        game->player->fovra = game->player->pa + FOV;
    }
	//if (strchr("NSEW", game->map[y][x]))
	//{
	//	add_cube(game->world_2d,10, 10, TILE_LEN * x + (TILE_LEN / 2), TILE_LEN * y + (TILE_LEN / 2), 0xFFFF00);
	//	printf("created player\n");
	//}
}
