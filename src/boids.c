#include "boids.h"

t_boolean   is_leaf(t_quad *q_tree)
{
	if (q_tree->in_view != NULL)
		return (true);
	return (false);
}

t_boolean intersect(t_boid *boid, t_quad *q_tree)
{
	float	dist_x;
	float	dist_y;
	float	distance;

	dist_x = 0;
	dist_y = 0;
	if (boid->x < q_tree->max.x)
		dist_x = q_tree->max.x - boid->x;
	else if (boid->x > q_tree->min.x)
		dist_x = boid->x - q_tree->min.x;
	if (boid->y < q_tree->max.y)
		dist_y = q_tree->max.y - boid->y;
	else if (boid->y > q_tree->min.y)
		dist_y = boid->y - q_tree->min.y;
	distance = sqrtf(dist_x * dist_x + dist_y * dist_y);
	if (distance <= D_MIN)
		return (true);
	return (false);
}

void    neighbor(t_boid *boids, t_quad *q_tree)
{
	if (is_leaf(q_tree))
	{
		rules(boids, q_tree->in_view);
		fprintf(stderr, "feuille");				
		return ;
	}
	if (intersect(boids, q_tree->NE))
	{
		neighbor(boids, q_tree->NE);
	}		
	if (intersect(boids, q_tree->NW))
	{
		neighbor(boids, q_tree->NW);
	}		
	if (intersect(boids, q_tree->SE))
	{
		neighbor(boids, q_tree->SE);
	}		
	if (intersect(boids, q_tree->SW))
	{
		neighbor(boids, q_tree->SW);
	}
}

void    update_boids(t_boid *boids)
{
	t_quad  *q_tree;
	t_boid  *lst_boids_copy;
	t_boid  *head;

	lst_boids_copy = list_dup(boids);
	if (!lst_boids_copy)
		return ;
	q_tree = quadtree(0.0f, 0.0f, (float)WIDTH, (float)HEIGHT, lst_boids_copy);
	if (!q_tree)
			return ;
	head = boids;
	while (boids)
	{
		fprintf(stderr, "hello");
		neighbor(boids, q_tree);
		if ((boids->x +  boids->vx) > WIDTH - 10){
			boids->vx = -boids->vx;
			boids->vy = rand_float_range(-1.0f, 1.0f);
		}
		else if ((boids->y + boids->vy) > HEIGHT - 10){
			boids->vy = -boids->vy;
			boids->vx = rand_float_range(-1.0f, 1.0f);
		}
		else if ((boids->x + boids->vx) < 0 + 10){
			boids->vx = -boids->vx;
			boids->vy = rand_float_range(-1.0f, 1.0f);
		}
		else if ((boids->y + boids->vy) < 0 + 10){
			boids->vy = -boids->vy;
			boids->vx = rand_float_range(-1.0f, 1.0f);
		}
		boids->x += boids->vx;
		boids->y += boids->vy;
		boids = boids->next;
	}
	boids = head;
}