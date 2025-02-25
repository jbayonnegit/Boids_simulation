#include "boids.h"

float	float_rand(void){
	
	return (float)rand() / (float)RAND_MAX;
}

float rand_float_range(float a, float b) {

	return a + (b - a) * ((float)rand() / (float)RAND_MAX);
}

void	draw_boids(t_boid **boids, SDL_Renderer *renderer)
{
	float		angle;
	int			i;
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