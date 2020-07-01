#include "maze.h"
#include "controls.h"

#define WIDTH 800
#define HEIGHT 600


/**
 * init_instance - Initialize a new SDL2 instance.
 * Return: SDL_Instance structure if successful, otherwise NULL
 */
SDL_Instance *init_instance(void)
{
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	SDL_Instance *instance;

	instance = malloc(sizeof(SDL_Instance));
	if (!instance)
		return (NULL);

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Error initializing SDL: %s\n", SDL_GetError());
		return (NULL);
	}

	instance->window = SDL_CreateWindow("SDL Window Test",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (!instance->window)
	{
		SDL_Log("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return (NULL);
	}

	instance->renderer = SDL_CreateRenderer(instance->window,
						-1, render_flags);
	if (!instance->renderer)
	{
		SDL_DestroyWindow(instance->window);
		SDL_Log("Error creating renderer: %s\n", SDL_GetError());
		SDL_Quit();
		return (NULL);
	}

	instance->height = HEIGHT;
	instance->width = WIDTH;
	return (instance);
}

/**
 * init_player - Initialize player struct.
 * @x: x coordinate of player position
 * @y: y coordinate of player position
 * Return: Player structure if successful, NULL otherwise
 */
Player *init_player(double x, double y)
{
	Player *p;

	p = (Player *) malloc(sizeof(Player));
	if (!p)
		return (NULL);

	p->pos = (Vector) {x, y};
	p->dir = (Vector) {-3, 0};
	p->plane = (Vector) {0.0f, -2.0f};
	p->move_speed = 0.0;
	p->rot_speed = 0.0;
	return (p);
}


/**
 * main - Starting function for maze application.
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 if successful, a nonzero value otherwise
 */
int main(int argc, char *argv[])
{
	SDL_Instance *instance;
	Player *player;
	double curr_tick, prev_tick, frame_time;
	int map[MAP_HEIGHT][MAP_WIDTH];

	if (argc != 2)
	{
		printf("Usage: maze.c map.txt\n");
		return (1);
	}
	map_file_parser(argv[1], map);
	instance = init_instance();
	if (!instance)
		return (1);

	/* (4, 3) is starting coordinates, define macro for this */
	player = init_player(4, 3);
	curr_tick = prev_tick = 0; /* Time of current and previous frame. */
	while (1)
	{
		if (exit_check() == 1)
			return (1);

		SDL_SetRenderDrawColor(instance->renderer, 0, 0, 0, 0);
		SDL_RenderClear(instance->renderer);

		for (int x = 0; x < WIDTH; ++x)
			ray_cast(map, instance, player, x);
		SDL_RenderPresent(instance->renderer);

		prev_tick = curr_tick;
		curr_tick = SDL_GetTicks();
		frame_time = (curr_tick - prev_tick) / 1000.0;
		player->move_speed = frame_time * 5.0;
		player->rot_speed = frame_time * 3.0;
		check_move_keys(map, player);
	}
	app_shutdown(instance, player);
	return (0);
}
