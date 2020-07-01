#ifndef _RAYCAST_H_
#define _RAYCAST_H_

#include "maze.h"

/**
 * struct ray_s - Struct containing ray data.
 * @pos: position
 * @dir: rirection
 * @grid_pos: grid position
 * @side_dist: distane of side
 * @delta_dist: change in distance
 * @step: ray step
 * @perp_wall_dist: perpendicular wall distance
 * @hit: check if ray hit wall
 * @side: check what side of wall hit
 */
typedef struct ray_s
{
	Vector pos;
	Vector dir;
	Vector grid_pos;
	Vector side_dist;
	Vector delta_dist;
	Vector step;
	double perp_wall_dist;
	int hit;
	int side;
} Ray;


/* raycast_init.c prototypes */
Ray *initialize_ray(Player *p, float cam);
void free_ray(Ray *ray);

/* raycast.c prototypes */
void ray_cast(int map[][MAP_WIDTH], SDL_Instance *inst, Player *player, int x);
void calculate_step(Ray *ray);
void digital_differential_analysis(Ray *ray, int map[][MAP_WIDTH]);
void calculate_dist(Ray *ray);

#endif
