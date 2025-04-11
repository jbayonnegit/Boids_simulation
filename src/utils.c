#include "boids.h"

float	float_rand(void){
	
	return (float)rand() / (float)RAND_MAX;
}

float rand_float_range(float a, float b) {

	return a + (b - a) * ((float)rand() / (float)RAND_MAX);
}

void	get_gradient(SDL_Color C1, SDL_Color C2, SDL_Color *Color, int speed)
{
	speed /= 100;
	Color->a = 255;	
	Color->r = C1.r - (C2.r * speed);	
	Color->g = C1.g - (C2.g * speed);	
	Color->b = C1.b - (C2.b * speed);
}

void	draw_boids(t_boid **boids, SDL_Renderer *renderer)
{
	float		angle;
	int		speed;
	SDL_Color	C1;
	SDL_Color	C2;
	SDL_Color	Color;
	int			i;
	t_triangle	tr;

	i = 0;
	C1.a = 255;
	C1.r = 137;
	C1.g = 157;
	C1.b = 246;
	C2.a = 255;
	C2.r = 233;
	C2.g = 58;
	C2.b = 40;
	while (boids[i]){
		angle = atan2(boids[i]->vy, boids[i]->vx);
		speed = sqrt(boids[i]->vx * boids[i]->vx + boids[i]->vy * boids[i]->vy);
		speed =  speed * 100 / V_MAX;
		printf("speed  : %d\n", speed);
		get_gradient(C1, C2, &Color, speed);
		tr.p1.x = boids[i]->x + cos(angle) * 10;
		tr.p1.y = boids[i]->y + sin(angle) * 10;
    	tr.p2.x = boids[i]->x + cos(angle + 2.5) * 10;
		tr.p2.y = boids[i]->y + sin(angle + 2.5) * 10;
		tr.p3.x = boids[i]->x + cos(angle - 2.5) * 10;
		tr.p3.y = boids[i]->y + sin(angle - 2.5) * 10;
		SDL_SetRenderDrawColor(renderer, Color.r, Color.g, Color.b, 255);
	    SDL_RenderDrawLine(renderer, tr.p1.x, tr.p1.y, tr.p2.x, tr.p2.y);
	    SDL_RenderDrawLine(renderer, tr.p2.x, tr.p2.y, tr.p3.x, tr.p3.y);
	    SDL_RenderDrawLine(renderer, tr.p3.x, tr.p3.y, tr.p1.x, tr.p1.y);
		i++;	
	}
}