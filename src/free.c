#include "boids.h"

void	free_glb(t_global *glb)
{
	free(glb->renderer);
	free(glb->window);
	free(glb);
}