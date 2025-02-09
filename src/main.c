#include "boids.h"

int main(int argc, char **argv){
	
	t_global    *glb;
	int         i;
	t_boolean	run;

	i = 0;
	glb = malloc(sizeof(t_global));
	if (!glb)
		return (-1);
	if (!boids_random_init(glb->boids))
		return (-1);
	if (!window_initialisation(glb))
		return (-1);
	run = true;
	free_glb(glb);
}