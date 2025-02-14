#include "boids.h"


void	free_list(t_boid *boids)
{
	t_boid *tmp;

	tmp = boids->next;
	while(tmp->next)
	{
		free(boids);
		boids = tmp;
		tmp = tmp->next;
	}
	free(tmp);
	boids = NULL;
	tmp = NULL;
}

void	free_glb(t_global *glb)
{
	free_list(glb->boids);
	free(glb);
}

void	window_clear(t_global *glb)
{
	free_list(glb->boids);
	SDL_DestroyRenderer(glb->renderer);
	SDL_DestroyWindow(glb->window);
	free(glb);
	SDL_Quit();
}