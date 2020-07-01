#include "raycast.h"

/**
 * initialize_ray - Intialize ray structure.
 * @p: player struct
 * @cam: camera
 * Return: Ray structure if successful, otherwise NULL
 */
Ray *initialize_ray(Player *p, float cam)
{
	Ray *ray;

	ray = (Ray *) malloc(sizeof(Ray));
	if (!ray)
		return (NULL);

	ray->pos = (Vector) {p->pos.x, p->pos.y};
	ray->dir = (Vector) {p->dir.x + p->plane.x * cam,
		   p->dir.y + p->plane.y * cam};

	/* Current position on the grid/map. */
	ray->grid_pos = (Vector) {floorf(ray->pos.x), floorf(ray->pos.y)};
	ray->side_dist = (Vector) {0, 0};

	ray->delta_dist = (Vector) {
		sqrt(1 + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x)),
		sqrt(1 + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y))
	};

	ray->step = (Vector) {0, 0};

	ray->hit = 0;
	ray->side = 0;
	return (ray);
}

/**
 * free_ray - Free ray struct memory.
 * @ray: ray struct
 */
void free_ray(Ray *ray)
{
	if (!ray)
		return;
	free(ray);
	ray = NULL;
}
