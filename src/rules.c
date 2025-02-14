#include "boids.h"

void    get_allignement(t_rules *rules, t_boid *in_view)
{
	t_boid *tmp;
	int		c;

	tmp = in_view;
	c = 0;
	rules->all_x = 0;
	rules->all_y = 0;
	while (tmp)
	{
		rules->all_x += tmp->vx;
		rules->all_y += tmp->vy;
		c++;
		tmp = tmp->next;
	}
	rules->all_x /= c;
	rules->all_y /= c;
}

void	get_cohesion(t_rules *rules, t_boid *in_view)
{
	t_boid *tmp;
	int		c;

	tmp = in_view;
	c = 0;
	rules->coh_x = 0;
	rules->coh_y = 0;
	while (tmp)
	{
		rules->coh_x += tmp->x;
		rules->coh_y += tmp->y;
		c++;
		tmp = tmp->next;
	}
	rules->coh_x /= c;
	rules->coh_y /= c;
}

void	get_separation(t_rules *rules, t_boid *in_view, t_boid *boid)
{
	t_boid	*tmp;
	float	distance;

	tmp = in_view;
	rules->sep_x = 0;
	rules->sep_y = 0;
	while (tmp)
	{
		distance = sqrtf(powf(tmp->x - boid->x, 2) + powf(tmp->x - boid->x, 2));
		if (distance < 5)
		{
			rules->sep_x += -(tmp->x - boid->x);
			rules->sep_y += -(tmp->y - boid->y);
		}
		tmp = tmp->next;
	}
}

void	rules(t_boid *boid, t_boid *neighbor)
{
	t_boid	*in_view;
	t_boid	*tmp;
	t_rules	rules;
	float	distance;

	in_view = NULL;
	tmp = neighbor;
	while (tmp)
	{
		distance = sqrtf(powf(tmp->x - boid->x, 2) + powf(tmp->x - boid->x, 2));
		if (distance < D_MIN)
			add_back(in_view, dup_boid(neighbor));
		tmp = tmp->next;
	}
	get_allignement(&rules, in_view);
	get_separation(&rules, in_view, boid);
	get_cohesion(&rules, in_view);
	boid->vx += (rules.all_x * 0.5) + (rules.coh_x * 0.3) + (rules.sep_x * 0.1);
	boid->vy += (rules.all_y * 0.5) + (rules.coh_y * 0.3) + (rules.sep_y * 0.1);
	free_list(in_view);
}
