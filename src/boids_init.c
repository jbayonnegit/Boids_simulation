#include "boids.h"

void	add_back(t_boid *head, t_boid *new)
{
	t_boid	*tmp;

	if (head == NULL)
	{
		head = new;
		tmp = NULL;
		fprintf(stderr, "new %p\n", new);				
		fprintf(stderr, "head %p\n", head);				
		return ;
	}
	tmp = head;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	tmp = NULL;
	return ;
}

t_boid	*new_node(float x, float y, float vx, float vy)
{
	t_boid	*new;

	new = malloc(sizeof(t_boid));
	if (!new)
		return (NULL);
	new->x = x;			
	new->vx = vx;
	new->vy = vy;			
	new->y = y;
	new->next = NULL;
	return (new);
}

t_boid	*boids_random_init(void){

	t_boid	*boids;	
	t_boid	*tmp;
	int		i;
	
	boids = new_node((HEIGHT / 2) * (float_rand() * 2) + 100, (WIDTH / 4) * (float_rand() * 2) + 100, float_rand(), float_rand());
	if (!boids)
		return (NULL);
	i = 0;
	while (i < NB_BOIDS)
	{
		tmp = new_node((HEIGHT / 2) * (float_rand() * 2) + 100, (WIDTH / 4) * (float_rand() * 2) + 100, float_rand(), float_rand());
		if (!tmp)
			return (free_list(boids), NULL);
		add_back(boids, tmp);
		i++;
	}
	return (boids);
}