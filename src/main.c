#include "boids.h"

void	refresh(t_global *glb)
{
	SDL_SetRenderDrawColor(glb->renderer, 0, 0, 0, 255);
	SDL_RenderClear(glb->renderer);
	SDL_SetRenderDrawColor(glb->renderer, 220, 255, 255, 255);
	update_boids(glb->boids);
	draw_boids(glb->boids, glb->renderer);
	SDL_RenderPresent(glb->renderer);
	SDL_Delay(50);
}

void	param_init(t_param *param)
{
	param->all = 0.5;
	param->coh = 0.3;
	param->sep = 0.01;
}

void	run(t_global *glb)
{
	t_boolean	run;
	t_param		param;
	SDL_Event	event;

	run = true;
	param_init(&param);
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
	return (0);
}