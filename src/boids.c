#include "boids.h"

float	float_rand(void){
	
	return (float)rand() / (float)RAND_MAX;
}

float rand_float_range(float a, float b) {
   
    return a + (b - a) * ((float)rand() / (float)RAND_MAX);
}

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
		boids[i]->x = HEIGHT / 2;
		boids[i]->y = WIDTH / 4;
		boids[i]->vx = float_rand();
		boids[i]->vy = float_rand();
		i++;
	}
	boids[i] = NULL;
	return (boids);
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
		if ((boids[i]->y +  boids[i]->vy) > HEIGHT - 10){
			boids[i]->vy = -boids[i]->vy;
			boids[i]->vx = rand_float_range(-1.0f, 1.0f);
		}
		if ((boids[i]->x +  boids[i]->vx) < 0 + 10){
			boids[i]->vx = -boids[i]->vx;
			boids[i]->vy = rand_float_range(-1.0f, 1.0f);
		}
		if ((boids[i]->y +  boids[i]->vy) < 0 + 10){
			boids[i]->vy = -boids[i]->vy;
			boids[i]->vx = rand_float_range(-1.0f, 1.0f);
		}
		boids[i]->x += boids[i]->vx;
		boids[i]->y += boids[i]->vy;
		i++;
	}
}

void	draw_boids(t_boid **boids, SDL_Renderer *renderer)
{
	int			i;
	float		angle;
	t_triangle	tr;

	i = 0;
	while (boids[i]){
		angle = atan2(boids[i]->vy, boids[i]->vx);

		tr.p1.x = boids[i]->x + cos(angle) * 10;
		tr.p1.y = boids[i]->y + sin(angle) * 10;
    	tr.p2.x = boids[i]->x + cos(angle + 2.5) * 10;
		tr.p2.y = boids[i]->y + sin(angle + 2.5) * 10;
		tr.p3.x = boids[i]->x + cos(angle - 2.5) * 10;
		tr.p3.y = boids[i]->y + sin(angle - 2.5) * 10;
	    SDL_RenderDrawLine(renderer, tr.p1.x, tr.p1.y, tr.p2.x, tr.p2.y);
	    SDL_RenderDrawLine(renderer, tr.p2.x, tr.p2.y, tr.p3.x, tr.p3.y);
	    SDL_RenderDrawLine(renderer, tr.p3.x, tr.p3.y, tr.p1.x, tr.p1.y);
		i++;
	}
}