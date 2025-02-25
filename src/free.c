#include "boids.h"

void	free_boid_init(t_boid **boid, int i)
{
	int	c;

	c = 0;
	while (c < i)
	{
		free(boid[c]);
		c++;
	}
	free(boid);
}

void	free_boid(t_boid **boid)
{
	int	i;

	i = 0;
	while (boid[i])
	{
		free(boid[i]);
		i++;
	}
	free(boid);
}

void	free_glb(t_global *glb)
{
	free_boid(glb->boids);
	free(glb);
}

void	window_clear(t_global *glb)
{
	SDL_DestroyRenderer(glb->renderer);
	SDL_DestroyWindow(glb->window);
	free(glb);
	SDL_Quit();
}