#include "boids.h"

float	float_rand(void){
	
	return (float)rand() / (float)RAND_MAX;
}

float rand_float_range(float a, float b) {

	return a + (b - a) * ((float)rand() / (float)RAND_MAX);
}

void	add_back(t_nb_view *head, t_nb_view *new)
{
	t_nb_view	*tmp;

	if (!head)
	{
		head = new;
		return ;
	}
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_nb_view	*new_node(int j)
{
	t_nb_view	*new;

	new = malloc(sizeof(t_nb_view));
	if (!new)
		return (NULL);
	new->n = j;
	new->next = NULL;
	return (new);
}