#include "boids.h"
float distance_euclidienne(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}

float get_angle(t_boid *current, t_boid *neighbor) {
    float dx = neighbor->x - current->x;
    float dy = neighbor->y - current->y;
    float norme_current = sqrtf(powf(current->vx, 2) + powf(current->vy, 2));
    float norme_neighbor = sqrtf(powf(dx, 2) + powf(dy, 2));

    if (norme_current == 0 || norme_neighbor == 0) return 180;

    float scalaire = (current->vx * dx) + (current->vy * dy);
    float angle = acosf(scalaire / (norme_current * norme_neighbor)) * (180.0 / M_PI);
    
    return angle; 
}

t_boolean rect_intersects_circle(SDL_Point min, SDL_Point max, float x, float y, float r) 
{
	float closestX = fmax(min.x, fmin(x, max.x));
	float closestY = fmax(min.y, fmin(y, max.y));

	float distanceX = x - closestX;
	float distanceY = y - closestY;
	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

	if (distanceSquared <= r * r)
		return (true);
	else
		return (false);
}

int	*find_neighbor(t_quad *root, float x, float y, float r, int *neighbor, int *count, t_boid **boid, t_boid *boidi)
{
	int		i;
	int		d;
	int		*tmp;
	//float	angle;

	i = 0;
	d = 0;
	if (!root)
		return (neighbor);
	if (!rect_intersects_circle(root->min, root->max, x, y, r))
		return (neighbor);
	if (root->leave == true)
	{
		while (i < root->nb_view)
		{
			d = distance_euclidienne(x, y, boid[root->in_view[i]]->x, boid[root->in_view[i]]->y);
		//	angle = get_angle(boidi, boid[root->in_view[i]]);
			if (d <= r )
			{
				*count += 1;
				tmp = neighbor;
				neighbor = in_view_realloc(neighbor, root->in_view[i], *count);
				if (!neighbor)
				{
					exit(-1);
				}
				free(tmp);
			}
			i++;
			
		}
	}
	else
	{
		neighbor = find_neighbor(root->NE, x, y, r, neighbor, count, boid, boidi);
		neighbor = find_neighbor(root->NW, x, y, r, neighbor, count, boid, boidi);
		neighbor = find_neighbor(root->SE, x, y, r, neighbor, count, boid, boidi);
		neighbor = find_neighbor(root->SW, x, y, r, neighbor, count, boid, boidi);
	}
	return (neighbor);
}

int	*view_init_first(void)
{
	int	*view_init;

	int	i;
	view_init = malloc(sizeof(int) * (NB_BOIDS + 1));
	if (!view_init)
	{
		exit(-1);
	}
	i = 0;
	while (i < NB_BOIDS)
	{
		view_init[i] = i;
		i++; 
	}
	view_init[i] = 0;
	return (view_init);
}

void    update_boids(t_boid **boid)
{
	int		*neighbor;
	int		*view_init;
	int		c;
	t_quad	*root;
	int		i;
	int 	k;

	k = 0;
	view_init = view_init_first();
	root = quadtree(WIDTH, 0, HEIGHT, 0, boid, view_init, NB_BOIDS, &k);
	if (!root)
		return ;
	i = 0;
	while (i < NB_BOIDS)
	{
		c = 0;
		neighbor = NULL;
		fprintf(stderr, "BOIDS[%d]\n", i);
		neighbor = find_neighbor(root, boid[i]->x, boid[i]->y, D_MIN, NULL, &c, boid, boid[i]);
		rules(boid, boid[i], neighbor, c);
		free(neighbor);
		i++;
	}
}