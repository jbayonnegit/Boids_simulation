#include "boids.h"

void	refresh(t_global *glb)
{
	SDL_SetRenderDrawColor(glb->renderer, 0, 0, 0, 255);
	SDL_RenderClear(glb->renderer);
	SDL_Delay(3000);
}

void	run(t_global *glb)
{
	t_boolean	run;
	SDL_Event	event;

	run = true;
	while (run)
	{
		refresh(glb);
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_WINDOWEVENT)
			{
				if (event.window.event == SDL_WINDOWEVENT_CLOSE)
				{
					window_clear(glb);
					run = false;
				}
			}
		}
	}
}

int	main(int argc, char **argv){
	
	t_global	*glb;

	(void)argc;
	(void)argv;
	glb = malloc(sizeof(t_global));
	if (!glb)
		return (-1);
	glb->boids = boids_random_init();
	if (!glb->boids)
		return (-1);
	if (!window_initialisation(glb))
		return (-1);
	run(glb);
	free_glb(glb);
}