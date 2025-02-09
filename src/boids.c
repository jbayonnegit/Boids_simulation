#include "boids.h"

float	float_rand(void){
	
	return (float)rand() / (float)RAND_MAX;
}

float rand_float_range(float a, float b) {
   
    return a + (b - a) * ((float)rand() / (float)RAND_MAX);
}

t_boolean	boids_random_init(t_boid **boids){
	
	int i;

	srand(time(NULL));
	boids = malloc(sizeof(t_boid) * NB_BOIDS + 1);
	if (!boids)
		return (false);
	i = 0;
	while (i < NB_BOIDS)
	{
		boids[i]->x = 0;
		boids[i]->x = 0;
		boids[i]->vx = float_rand();
		boids[i]->vy = float_rand();
		i++;
	}
	boids[i] = NULL;
	return (true);
}

void	boid_update_rand(t_boid **boids){
	
	int	i;

	i = 0;
	while (boids[i])
	{
		if ((boids[i]->x +  boids[i]->vx) > WIDTH - 10){
			boids[i]->vx = -boids[i]->vx;
			boids[i]->vy = rand_float_range(-1.0f, 1.0f);
		}
		if ((boids[i]->y +  boids[i]->vy) > WIDTH - 10){
			boids[i]->vy = -boids[i]->vy;
			boids[i]->vx = rand_float_range(-1.0f, 1.0f);
		}
		boids[i]->x += boids[i]->vx;
		boids[i]->y += boids[i]->vy;
		i++;
	}
}