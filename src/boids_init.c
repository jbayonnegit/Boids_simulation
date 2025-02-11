#include "boids.h"

t_boid	**boids_malloc(void){

	t_boid **boids;
	int i;

	srand(time(NULL));
	boids = malloc(sizeof(t_boid *) * (NB_BOIDS + 1));
	if (!boids)
		return (NULL);
	i = 0;
	while (i < NB_BOIDS)
	{
		boids[i] = malloc(sizeof(t_boid));
		if (!boids[i])
			return (free_boids_init(boids, i), NULL);
		i++;
	}
	return (boids);
}

t_boid	**boids_random_init(void){

	t_boid	**boids;	
	int		i;
	
	boids = boids_malloc();
	if (!boids)
		return (NULL);
	i = 0;
	while (i < NB_BOIDS)
	{
		boids[i]->x = (HEIGHT / 2) * (float_rand() * 2) + 100;
		boids[i]->y = (WIDTH / 4) * (float_rand() * 2) + 100;
		boids[i]->vx = float_rand();
		boids[i]->vy = float_rand();
		i++;
	}
	boids[i] = NULL;
	return (boids);
}