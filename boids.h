#ifndef BOIDS_H
# define BOIDS_H
# define V_MAX 5
# define NB_BOIDS 500
# include <SDL2/SDL.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_coordinate
{
	float	x;
	float	y;
}				t_cord;

typedef struct s_speed_vectot
{
	float	x;
	float	y;
}				t_dir;

typedef struct s_boid
{
	t_cord			pos;
	t_dir			v;
	struct s_boid	*next;
}				t_boid;

typedef struct s_global
{
	t_boid	*Boids;
}				t_global;

typedef	enum s_boolean
{
	false,
	true,
}			t_boolean;

#endif