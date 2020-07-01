#include "maze.h"

/**
 * free_instance - Free memory allocated for an SDL_Instance structure.
 * @instance: struct to be freed
 */
void free_instance(SDL_Instance *instance)
{
	if (!instance)
		return;

	free(instance);
	instance = NULL;
}

/**
 * free_player - Free memory allocated for a Player structure.
 * @p: plauer struct to free
 */
void free_player(Player *p)
{
	if (!p)
		return;

	free(p);
	p = NULL;
}

/**
 * app_shutdown - Free memory from structures and SDL2 objects.
 * @instance: instance struct to free
 * @player: player struct to free
 */
void app_shutdown(SDL_Instance *instance, Player *player)
{
	SDL_DestroyRenderer(instance->renderer);
	SDL_DestroyWindow(instance->window);
	free_instance(instance);
	free_player(player);
	SDL_Quit();
}
