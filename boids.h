#ifndef BOIDS_H
# define BOIDS_H

# define V_MAX 30
# define NB_BOIDS 500
# define HEIGHT 1080
# define WIDTH 1920
# define M_PI 3.14159265358979323846
# define D_MIN 50
# define QUAD_CAP 30
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
	struct s_boid *next;
	
}				t_boid;

typedef struct s_quadtree
{
	int					count;
	SDL_Point			min;
	SDL_Point			max;
	t_boid				*in_view;
	struct s_quadtree	*NW;
	struct s_quadtree	*NE;
	struct s_quadtree	*SW;
	struct s_quadtree	*SE;
}				t_quad;

typedef struct s_global
{
	t_boid			*boids;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
}				t_global;

typedef struct s_triangle
{
	SDL_Point p1;
	SDL_Point p2;
	SDL_Point p3;
}				t_triangle;

typedef struct s_moyenne
{
	float	sep_x;	
	float	sep_y;
	float	all_x;	
	float	all_y;		
	float	coh_x;	
	float	coh_y;
}			t_rules;

typedef	struct	s_param
{
	float	coh;
	float	sep;
	float	all;
}				t_param;

typedef	enum s_boolean
{
	false,
	true,
}			t_boolean;

void		free_glb(t_global *glb);
t_boolean	window_initialisation(t_global *glb);
t_boid		*boids_random_init(void);
void		boid_update_rand(t_boid **boids, t_param *param);
void		free_boids_init(t_boid **boids, int i);
void		window_clear(t_global *glb);
void		draw_boids(t_boid *boids, SDL_Renderer *renderer);
float		float_rand(void);
float		rand_float_range(float a, float b);
void		add_back(t_boid *head, t_boid *new);
void		free_list(t_boid *boids);
t_quad		*quadtree(float max_x, float max_y, float min_x, float min_y, t_boid *Boids);
t_boid 		*list_dup(t_boid *head);
void		rules(t_boid *boid, t_boid *neighbor);
t_boid		*dup_boid(t_boid *boid);
void   		 update_boids(t_boid *boids);

#endif