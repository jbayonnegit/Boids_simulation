#include "boids.h"

float	float_rand(void){
	
	return (float)rand() / (float)RAND_MAX;
}

float rand_float_range(float a, float b) {

	return a + (b - a) * ((float)rand() / (float)RAND_MAX);
}

void	draw_boids(t_boid *boids, SDL_Renderer *renderer)
{
	float		angle;
	t_boid		*tmp;
	t_triangle	tr;

	tmp = boids;
	while (tmp){
		angle = atan2(tmp->vy, tmp->vx);

		tr.p1.x = tmp->x + cos(angle) * 10;
		tr.p1.y = tmp->y + sin(angle) * 10;
    	tr.p2.x = tmp->x + cos(angle + 2.5) * 10;
		tr.p2.y = tmp->y + sin(angle + 2.5) * 10;
		tr.p3.x = tmp->x + cos(angle - 2.5) * 10;
		tr.p3.y = tmp->y + sin(angle - 2.5) * 10;
	    SDL_RenderDrawLine(renderer, tr.p1.x, tr.p1.y, tr.p2.x, tr.p2.y);
	    SDL_RenderDrawLine(renderer, tr.p2.x, tr.p2.y, tr.p3.x, tr.p3.y);
	    SDL_RenderDrawLine(renderer, tr.p3.x, tr.p3.y, tr.p1.x, tr.p1.y);
		tmp = tmp->next;
	}
}