#include "boids.h"

t_boolean   is_leaf(t_quad *q_tree)
{

}

t_boolean intersect(t_boid *boid, t_quad *q_tree)
{

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

}