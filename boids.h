#ifndef BOIDS_H
# define BOIDS_H
# define V_MAX 5
# define NB_BOIDS 500
# define HEIGHT 720
# define WIDTH 1280
# include <SDL2/SDL.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>

typedef struct s_boid
{
	float	x;
	float	y;
	float	vx;
	float	vy;
}				t_boid;

typedef struct s_global
{
	t_boid			**boids;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
}				t_global;

typedef	enum s_boolean
{
	false,
	true,
}			t_boolean;

void		free_glb(t_global *glb);
t_boolean	window_initialisation(t_global *glb);
t_boolean	boids_random_init(t_boid **boids);
void		boid_update_rand(t_boid **boids);


#endif