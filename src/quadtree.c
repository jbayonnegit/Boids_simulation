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
	new = malloc(sizeof(int) * (nb + 2));
	if (!new)
		return (free(old), NULL);
	i = 0;
	while(i < nb - 1)
	{
		new[i] = old[i];
		i++;
	}
	new[i] = add;
	new[i + 1] = 0;
	return (new);
}

t_quad  *quadrant_init(float max_x, float max_y, float min_x, float min_y){

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

t_quad  *quadtree(int max_x, int min_x, int max_y, int min_y, t_boid **boids, int *view, int nb_v, int *k)
{
	t_quad	*root;
	int		*tmp;
	int		c;
	int		i;

	i = 0;
	c = 0;
	 if (*k >= NB_BOIDS)
	 	return (NULL);
	root = quadrant_init(max_x, max_y, min_x, min_y);
	if (!root)
		return (NULL);
	while (i < nb_v)
	{	
		if ((boids[view[i]]->x <= max_x && boids[view[i]]->x >= min_x) && (boids[view[i]]->y <= max_y && boids[view[i]]->y >= min_y))
		{
			c++;
			tmp = root->in_view;
			root->in_view = in_view_realloc(root->in_view, view[i], c);
			if (tmp)
				free(tmp);
		}
		i++;
	}
	if (c > QUAD_CAP)
	{
		int mid_x = (max_x + min_x) / 2;
		int mid_y = (max_y + min_y) / 2;

		root->NW = quadtree(mid_x, min_x, mid_y, min_y, boids, root->in_view, c, k);
		root->NE = quadtree(max_x, mid_x, mid_y, min_y, boids, root->in_view, c, k);
		root->SW = quadtree(mid_x, min_x, max_y, mid_y, boids, root->in_view, c, k);
		root->SE = quadtree(max_x, mid_x, max_y, mid_y, boids, root->in_view, c, k);
		free(root->in_view);
	}
	else
	{
		*k += c;
		root->leave = true;
		root->nb_view = c;
	}
	return (root);
}