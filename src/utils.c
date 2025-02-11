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

	if (head == NULL)
	{
		head = new;
		tmp = NULL;
		return ;
	}
	tmp = head;
	fprintf(stderr, "okokok\n");
	fprintf(stderr, "adress head = %p | ", head);
	fprintf(stderr, "adress head next = %p\n", head->next);
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
	tmp = NULL;
	return ;
}

t_nb_view	*new_node(int j)
{
	t_nb_view	*new;

	new = malloc(sizeof(t_nb_view));
	if (!new)
	{
		fprintf(stderr, "malloc fail");
		return (NULL);
	}
	new->n = j;
	new->next = NULL;
	fprintf(stderr, "adress new = %p | ", new);
	fprintf(stderr, "adress new next = %p\n", new->next);
	fprintf(stderr, "alloc pour boid[%d]\n", j);
	return (new);
}