#ifndef BOIDS_H
# define BOIDS_H

# define V_MAX 4
# define V_MIN 1
# define NB_BOIDS 2000
# define HEIGHT 900
# define WIDTH 1440
# define M_PI 3.14159265358979323846
# define D_MIN 10
# define QUAD_CAP 50
# include </opt/homebrew/include/SDL2/SDL.h>
# include <stdlib.h>
# include <math.h>
# include <time.h>

typedef enum s_boolean
{
	false,
	true,
}	t_boolean;

typedef struct s_boid
{
	float	x;
	float	y;
	float	vx;
	float	vy;	
}				t_boid;

typedef struct s_quadtree
{
	SDL_Point			min;			// Point superieur gauche
	SDL_Point			max;			// Point inferieur droit
	t_boolean			leave;			// True si c'est une feuille, False si c'est une branche
	int					*in_view;		// Array des Boids en vue
	int					nb_view;		// Array des Boids en vue
	struct s_quadtree	*NW;			// Branche Nord Ouest
	struct s_quadtree	*NE;			// Branche Nord Est
	struct s_quadtree	*SW;			// Branche Sud Ouest
	struct s_quadtree	*SE;			// Branche Sud Est
}				t_quad;

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

void		free_glb(t_global *glb);
t_boolean	window_initialisation(t_global *glb);
t_boid		**boids_random_init(void);
void		boid_update_rand(t_boid **boids, t_param *param);
void		free_boids_init(t_boid **boids, int i);
void		window_clear(t_global *glb);
void		draw_boids(t_boid **boids, SDL_Renderer *renderer);
float		float_rand(void);
t_quad  	*quadtree(int max_x, int min_x, int max_y, int min_y, t_boid **boids, int *view, int nb_v, int *k);
int			*in_view_realloc(int *old, int add, int nb);
void		rules(t_boid **boids, t_boid *boid, int *neighbor, int nb);
t_boid		*dup_boid(t_boid *boid);
float 		rand_float_range(float a, float b);
t_quad   	*update_boids(t_boid **boids);
void		free_boid_init(t_boid **boid, int i);
void		free_tree(t_quad *root);

#endif
