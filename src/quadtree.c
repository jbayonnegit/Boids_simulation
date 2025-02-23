#include "boids.h"

int	*first_init(int add)
{
	int	*new;

	new = malloc(sizeof(int) * 2);
	if (!new)
		return (NULL);
	new[0] = add;
	new[1] = 0;
	return (new);
}

int	*in_view_realloc(int *old, int add, int nb)
{
	int	*new;
	int	i;

	if (!old)
	{
		old = first_init(add);
		if (!old)
			return (NULL);
		return (old);
	}
	new = malloc(sizeof(int) * nb + 1);
	if (!new)
		return (free(old), NULL);
	while(i < nb - 1)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = add;
	new[i + 1] = 0;
	return (new);
}

t_quad  *quadrant_init(float max_x, float max_y, float min_x, float min_y, int *view){

	t_quad  *new;

	new = (t_quad *)malloc(sizeof(t_quad));
	if (!new)
		return (NULL);
	new->NE = NULL;
	new->NW = NULL;
	new->SE = NULL;
	new->SW = NULL;
	new->in_view = NULL;
	new->leave = false;
	new->max.x = max_x;
	new->max.y = max_y;
	new->min.x = min_x;
	new->min.y = min_y;
	return (new);
}

t_quad  *quadtree(float max_x, float min_x, float max_y, float min_y, t_boid **boids, int *view, int nb_v)
{
	t_quad	*root;
	int		c;
	int		i;

	i = 0;
	c = 0; 
	root = quadrant_init(max_x, max_y, min_x, min_y, view);
	if (!root)
		return (NULL);
	while (i < nb_v)
	{	
		if ((boids[view[i]]->x <= max_x && boids[view[i]]->x >= min_x) && (boids[view[i]]->y <= max_y && boids[view[i]]->y >= min_y))
		{
			c++;
			root->in_view = in_view_realloc(root->in_view, view[i], c);
		}
		i++;
	}
	if (c > QUAD_CAP)
	{
		root->NW = (max_x / 2, min_x, max_y / 2, min_y, boids, root->in_view, c); 
		root->NE = (max_x, max_x / 2, max_y / 2, min_y, boids, root->in_view, c);
		root->SW = (max_x / 2, min_x, max_y, max_y / 2, boids, root->in_view, c);
		root->SE = (max_x, max_x / 2, max_y, max_y / 2, boids, root->in_view, c);
		free(root->in_view);
	}
	else
		root->leave = true;
	return (root);
}