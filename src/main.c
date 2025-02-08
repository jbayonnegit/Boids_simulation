#include "boids.h"

int main(int argc, char **argv)
{
    t_global    *glb;
    int         i;

    i = 0;
    glb = malloc(sizeof(t_global));
    if (!glb)
        return (-1);
    glb->Boids = malloc(sizeof(t_boid) * NB_BOIDS);
    if (!Boids)
        return (-1);
    while (i < NB_BOIDS)
    {
        glb->Boids[i] = 
        i++;
    }
}