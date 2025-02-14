#include "boids.h"

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
	new->max.x = max_x;
	new->max.y = max_y;
	new->min.x = min_x;
	new->min.y = min_y;
	return (new);
}

/*max correspond au coin superieur gauche du quadrant et min au coin inferieur droit du quadrant
  La liste Boids liste tous les bois present du dans le quadrant parent*/


t_boid	*dup_boid(t_boid *boid)
{
	t_boid *dup;

	dup = malloc(sizeof(t_boid));
	if (!dup)
		return (NULL);
	dup->vx = boid->vx;
	dup->vy = boid->vy;
	dup->y= boid->y;
	dup->x = boid->x;
	dup->next = NULL;
	return (dup);
}

t_boid *list_dup(t_boid *head)
{
	t_boid *head_dup;
	t_boid	*tmp;
	t_boid	*boid_dup;

	if (!head)
		return (NULL);
	tmp = head;
	head_dup = dup_boid(tmp);
	if (!head_dup)
	{
		return (NULL);
	}
	tmp = tmp->next;
	while (tmp)
	{
		boid_dup = dup_boid(tmp);
		if (!boid_dup)
			return (NULL);
		add_back(head_dup, boid_dup);
		if (!head_dup)
		{
			fprintf(stderr, "zbi");
		}
		tmp = tmp->next;
	}
	return (head_dup);
}

t_quad  *quadtree(float max_x, float max_y, float min_x, float min_y, t_boid *Boids)
{
	t_quad	*head;
	t_boid	*in_view_copy;
	t_boid	*Boids_copy;

	head = quadrant_init(max_x, max_y, min_x, min_y);
	if (!head)
		return (NULL);
	Boids_copy = list_dup(Boids);
	if (!Boids_copy)
		return (NULL);
	head->count = 0; 
	head->in_view = NULL;
	in_view_copy = NULL;
	while (Boids_copy)
	{
		if ((Boids_copy->x >= max_x && Boids_copy->x <= min_x) && (Boids_copy->y >= max_y && Boids_copy->y <= min_y))
		{
			if (!head->in_view)
				head->in_view = dup_boid(Boids);
			else
				add_back(head->in_view, dup_boid(Boids_copy));
			head->count++;
		}
		if (head->count > QUAD_CAP)
		{	
			in_view_copy = list_dup(head->in_view);
			if (!in_view_copy)
				return(NULL);
			free_list(head->in_view);
			head->NE = quadtree(max_x / 2, max_y, min_x, min_y / 2, in_view_copy);
			if (!head->NE)
				return (NULL);
			if (head->NE)
			head->NW = quadtree(max_x, max_y, min_x / 2, min_y / 2, in_view_copy);
			if (!head->NE)
				return (NULL);
			head->SE = quadtree(max_x / 2, max_y / 2, min_x, min_y, in_view_copy);
			if (!head->NE)
				return (NULL);
			head->NE = quadtree(max_x, max_y / 2, min_x / 2, min_y, in_view_copy);
			if (!head->NE)
				return (NULL);
			free_list(Boids_copy);
			free_list(Boids);
			break ;
		}
		Boids_copy = Boids_copy->next;
	}
	fprintf(stderr, "DONE\n");
	return (head);
}