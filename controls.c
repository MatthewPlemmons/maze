#include "controls.h"


/**
 * exit_check - check if program was closed
 * Return: 1 if exit key detected, 0 otherwise.
 */
int exit_check(void)
{
	SDL_Event event;
	SDL_KeyboardEvent key;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return (1);
		case SDL_KEYDOWN:
			key = event.key;
			if (key.keysym.scancode == 0x29)
				return (1);
		}
	}
	return (0);
}

/**
 * move_player_forward - Moves player forward in the map.
 * @map: map array
 * @p: player struct
 */
void move_player_forward(int map[][MAP_WIDTH], Player *p)
{
	if (map[(int)(p->pos.x + p->dir.x * p->move_speed)][(int)p->pos.y] == 0)
		p->pos.x += p->dir.x * p->move_speed;
	if (map[(int)p->pos.x][(int)(p->pos.y + p->dir.y * p->move_speed)] == 0)
		p->pos.y += p->dir.y * p->move_speed;
}

/**
 * move_player_back - Moves player backward in the map.
 * @map: map array
 * @p: player struct
 */
void move_player_back(int map[][MAP_WIDTH], Player *p)
{
	if (map[(int)(p->pos.x - p->dir.x * p->move_speed)][(int)p->pos.y] == 0)
		p->pos.x -= p->dir.x * p->move_speed;
	if (map[(int)p->pos.x][(int)(p->pos.y - p->dir.y * p->move_speed)] == 0)
		p->pos.y -= p->dir.y * p->move_speed;
}

/**
 * rotate_player - Rotates the player around.
 * @p: player struct
 * @rot_speed: rotation speed of player
 */
void rotate_player(Player *p, float rot_speed)
{
	double old_dir_x = p->dir.x;
	double old_plane_x = p->plane.x;
	
	p->dir.x = p->dir.x * cos(rot_speed) - p->dir.y * sin(rot_speed);
	p->dir.y = old_dir_x * sin(rot_speed) + p->dir.y * cos(rot_speed);

	p->plane.x = p->plane.x * cos(rot_speed) - p->plane.y * sin(rot_speed);
	p->plane.y = old_plane_x * sin(rot_speed) + p->plane.y * cos(rot_speed);
}

/**
 * check_move_keys - Checks keyboard scancodes for the W,S,A and D keys.
 * @map: map array
 * @player: player struct
 */
void check_move_keys(int map[][MAP_WIDTH], Player *player)
{
	const Uint8 *keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_W])
		move_player_forward(map, player);
	if (keys[SDL_SCANCODE_S])
		move_player_back(map, player);
	if (keys[SDL_SCANCODE_A])
		rotate_player(player, -(player->rot_speed));
	if (keys[SDL_SCANCODE_D])
		rotate_player(player, player->rot_speed);
}

