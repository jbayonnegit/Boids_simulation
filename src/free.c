#include "boids.h"

void	free_boids_init(t_boid **boids, int i){

	while (boids[i])
	{
		free(boids[i]);
		i--;
	}
	free(boids);
}

void	free_boids(t_boid **boids)
{
	int	i;

	i = 0;
	while(boids[i])
	{
		free(boids[i]);
		i++;
	}
	free(boids);
}

void	free_glb(t_global *glb)
{
	free_boids(glb->boids);
	free(glb);
}

void	window_clear(t_global *glb)
{
	free_boids(glb->boids);
	SDL_DestroyRenderer(glb->renderer);
	SDL_DestroyWindow(glb->window);
	free(glb);
	SDL_Quit();
}