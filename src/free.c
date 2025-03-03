#include "boids.h"

void	free_tree(t_quad *root)
{
	if (root->leave)
		free(root->in_view);
	if (root->NE)
	{
		free_tree(root->NE);
		root->NE = NULL;
	}
	if (root->NW)
	{
		free_tree(root->NW);
		root->NE = NULL;
	}
	if (root->SE)
	{
		free_tree(root->SE);
		root->NE = NULL;
	}
	if (root->SW)
	{
		free_tree(root->SW);
		root->NE = NULL;
	}
	free(root);
}

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
	while (i < NB_BOIDS)
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
	free_glb(glb);
	SDL_Quit();
}