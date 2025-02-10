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

typedef struct s_triangle
{
	SDL_Point p1;
	SDL_Point p2;
	SDL_Point p3;
}				t_triangle;

typedef struct s_view
{
	float	distance;
	float	angle;
}				t_view;

typedef struct s_nb_in_view
{
	int					n;
	struct s_nb_in_view *next;
}				t_nb_view;

typedef	enum s_boolean
{
	false,
	true,
}			t_boolean;

void		free_glb(t_global *glb);
t_boolean	window_initialisation(t_global *glb);
t_boid		**boids_random_init(void);
void		boid_update_rand(t_boid **boids);
void		free_boids_init(t_boid **boids, int i);
void		window_clear(t_global *glb);
void		draw_boids(t_boid **boids, SDL_Renderer *renderer);
void		boid_update_rand(t_boid **boids);
float		float_rand(void);
float 		rand_float_range(float a, float b);
t_nb_view	*new_node(int j);
void		add_back(t_nb_view *head, t_nb_view *new);

#endif