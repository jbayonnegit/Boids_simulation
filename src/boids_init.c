#include "boids.h"

t_boid	*new_node(float x, float y, float vx, float vy)
{
	t_boid	*new;

	new = malloc(sizeof(t_boid));
	if (!new)
		return (NULL);
	new->x = x;			
	new->vx = vx;
	new->vy = vy;			
	new->y = y;
	return (new);
}

t_boid	**boids_random_init(void){

	t_boid	**boids;	
	int		i;

	boids = malloc(sizeof(t_boid *) * (NB_BOIDS + 1));
	if (!boids)
		return (NULL);
	i = 0;
	while (i < NB_BOIDS)
	{
		boids[i] =  new_node((HEIGHT / 2) * (float_rand() * 2) + 100, (WIDTH / 4) * (float_rand() * 2) + 100, float_rand(), float_rand());
		if (!boids[i])
			return (free_boid_init(boids, i), NULL);
		i++;
	}
	boids[i] = NULL;
	return (boids);
}