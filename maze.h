#ifndef _MAZE_H_
#define _MAZE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include <SDL2/SDL.h>

/* Adjust map size read in from .txt file. */
#define MAP_WIDTH 20
#define MAP_HEIGHT 20


/**
 * struct SDL_Instance - Contains screen rendering data.
 * @window: window to render to
 * @renderer: renders graphics
 * @height: height of screen
 * @width: width of screen
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
	int height;
	int width;
} SDL_Instance;

/**
 * struct vector_s - Contains vector data.
 * @x: x coordinate
 * @y: y coordinate
 */
typedef struct vector_s
{
	float x;
	float y;
} Vector;

/**
 * struct player_s - Struct for player data.
 * @pos: player position
 * @dir: player direction
 * @plane: plane coordinates
 * @move_speed: speed of player
 * @rot_speed: rotations speed of player
 */
typedef struct player_s
{
	Vector pos;
	Vector dir;
	Vector plane;
	float move_speed;
	float rot_speed;
} Player;

/* main.c in place of init.c */
SDL_Instance *init_instance(void);
Player *init_player(double x, double y);

/* free.c */
void free_instance(SDL_Instance *instance);
void free_player(Player *p);
void app_shutdown(SDL_Instance *instance, Player *player);

/* raycast.c */
void ray_cast(int map[][MAP_WIDTH], SDL_Instance *inst, Player *player, int x);

/* parser.c */
void map_file_parser(char *filepath, int map[][MAP_WIDTH]);
void init_map_array(FILE *fp, int h, int w, int map[][MAP_WIDTH]);
void print_map_array(int h, int w, int map[][MAP_WIDTH]);

#endif
