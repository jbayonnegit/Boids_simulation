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

// void	free_quad(t_quad *root)
// {
// 	t_quad	*tmp;
// 	t_quad	*head;

// 	head = root;
// 	while(root->NE)
// 	{
// 		tmp = root;
// 		root = root->NE;
// 		if (root->leave == true)
// 		{
// 			tmp->leave == true;
// 			free(root->in_view);
// 			free(root);		
// 		}
// 		root = head;
// 	}
// 	while(root->NW)
// 	{
// 		tmp = root;
// 		root = root->NW;
// 		if (root->leave == true)
// 		{
// 			tmp->leave == true;
// 			free(root->in_view);
// 			free(root);		
// 		}		root = head;
// 	}
// 	while(root->SE)
// 	{
// 		tmp = root;
// 		root = root->SE;
// 		if (root->leave == true)
// 		{
// 			tmp->leave == true;
// 			free(root->in_view);
// 			free(root);		
// 		}		root = head;
// 	}
// 	while(root->SW)
// 	{
// 		tmp = root;
// 		root = root->SW;
// 		if (root->leave == true)
// 		{
// 			tmp->leave == true;
// 			free(root->in_view);
// 			free(root);		
// 		}
// 		root = head;
// 	}
// 	if (root->in_view)
// 		free(root->in_view);
// 	free(root);
// 	root = NULL;
// }

// void	free_tree(t_quad *root)
// {

// }

void	window_clear(t_global *glb)
{
	SDL_DestroyRenderer(glb->renderer);
	SDL_DestroyWindow(glb->window);
	free(glb);
	SDL_Quit();
}