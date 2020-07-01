#include "raycast.h"

/**
* calculate_step - Calculate ray step.
* @ray: ray to calculate step of
*/
void calculate_step(Ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (ray->pos.x - ray->grid_pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->grid_pos.x + 1.0 - ray->pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (ray->pos.y - ray->grid_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->grid_pos.y + 1.0 - ray->pos.y) * ray->delta_dist.y;
	}

}

/**
 * digital_differential_analysis - Find what squares a ray hits on map grid.
 * @ray: casted ray
 * @map: map array
 */
void digital_differential_analysis(Ray *ray, int map[][MAP_WIDTH])
{
	while (ray->hit == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->grid_pos.x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->grid_pos.y += ray->step.y;
			ray->side = 1;
		}
		/* Determine if the ray has hit a wall. */
		if (map[(int)ray->grid_pos.x][(int)ray->grid_pos.y] > 0)
			ray->hit = 1;
	}

}

/**
 * calculate_dist - Calculate distance of ray.
 * @ray: casted ray
 */
void calculate_dist(Ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = fabs((ray->grid_pos.x - ray->pos.x +
					    (1 - ray->step.x) / 2) / ray->dir.x);
	else
		ray->perp_wall_dist = fabs((ray->grid_pos.y - ray->pos.y +
					    (1 - ray->step.y) / 2) / ray->dir.y);
}

/**
 * ray_cast - Ray casting function.
 * @map: map array
 * @inst: current instance
 * @p: current player
 * @x: x coordinate
 */
void ray_cast(int map[][MAP_WIDTH], SDL_Instance *inst, Player *p, int x)
{
	Ray *ray;
	float cam;
	int line_height, draw_start, draw_end;

	cam = 2 * (float) x / (float) inst->width - 1;

	ray = initialize_ray(p, cam);
	if (!ray)
		return;

	calculate_step(ray);
	digital_differential_analysis(ray, map);
	calculate_dist(ray);

	line_height = abs((int) (inst->height / ray->perp_wall_dist));

	draw_start = -line_height / 2 + inst->height / 2;
	if (draw_start < 0)
		draw_start = 0;

	draw_end = line_height / 2 + inst->height / 2;
	if (draw_end >= inst->height)
		draw_end = inst->height - 1;

	/* Determine wall color */
	/*percent_height = (line_height % inst->height) * 100)*/
	SDL_SetRenderDrawColor(inst->renderer, 0, 255, 0, 255);
	if (ray->side == 1)
		SDL_SetRenderDrawColor(inst->renderer, 0, 150, 0, 255);

	SDL_RenderDrawLine(inst->renderer, x, draw_start, x, draw_end);
	free_ray(ray);
}
