#include "boids.h"

t_boolean	window_initialisation(t_global *glb)
{
	if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO) < 0){
		return (false);
	}
	glb->window = SDL_CreateWindow("Boids Simualtion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,  SDL_WINDOW_SHOWN);
	if (!glb->window){
		free(glb);
		return (false);
	}
	glb->renderer = SDL_CreateRenderer(glb->window, -1, SDL_RENDERER_ACCELERATED);
	if (!glb->renderer){
		free(glb->window);
		free(glb);
		return (false);
	}
}