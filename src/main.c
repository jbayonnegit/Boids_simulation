#include "boids.h"

void	draw_tree(t_quad *root, t_global *glb)
{
	SDL_Rect	quad;

	quad.x = root->min.x;
	quad.y = root->min.y;
	quad.w = root->max.x;
	quad.h = root->max.y;
	SDL_SetRenderDrawColor(glb->renderer, 50, 255, 0, 255);
	SDL_RenderDrawRect(glb->renderer, &quad);
	if (root->leave == true)
	{
		return ;
	}
	else
	{
		if (root->NW)
			draw_tree(root->NW, glb);
		if (root->NE)
			draw_tree(root->NE, glb);
		if (root->SW)
			draw_tree(root->SW, glb);
		if (root->SE)
			draw_tree(root->SE, glb);
	}
}

void	refresh(t_global *glb)
{
	t_quad	*root;

	SDL_SetRenderDrawColor(glb->renderer, 0, 0, 0, 255);
	SDL_RenderClear(glb->renderer);
	root = update_boids(glb->boids);
	//draw_tree(root, glb);
	free_tree(root);
	root = NULL;
	//SDL_SetRenderDrawColor(glb->renderer, 220, 255, 255, 255);
	draw_boids(glb->boids, glb->renderer);
	SDL_RenderPresent(glb->renderer);
	SDL_Delay(5);
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