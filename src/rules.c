#include "boids.h"

void    get_allignement(t_rules *rules,t_boid **boid, int *in_view, int nb)
{
	int		c;

	c = 0;
	rules->all_x = 0;
	rules->all_y = 0;
	if (nb == 0)
		return ;
	while (c < nb)
	{
		rules->all_x += boid[in_view[c]]->vx;
		rules->all_y += boid[in_view[c]]->vy;
		c++;
	}
	rules->all_x /= nb;
	rules->all_y /= nb;
}

void	get_cohesion(t_rules *rules,t_boid **boid, int *in_view, int nb)
{
	int		c;

	c = 0;
	rules->coh_x = 0;
	rules->coh_y = 0;
	if (nb == 0)
		return ;
	while (c < nb)
	{
		rules->coh_x += boid[in_view[c]]->x;
		rules->coh_y += boid[in_view[c]]->y;
		c++;
	}
	rules->coh_x /= nb;
	rules->coh_y /= nb;
}

void	get_separation(t_rules *rules, t_boid **boids, t_boid *boid, int *in_view, int nb)
{
	float	distance;
	int 	c;

	c = 0;
	rules->sep_x = 0;
	rules->sep_y = 0;
	while (c < nb)
	{
		distance = sqrtf(powf(boids[in_view[c]]->x - boid->x, 2) + powf(boids[in_view[c]]->x - boid->x, 2));
		if (distance < 8)
		{
			rules->sep_x += (boid->x - boids[in_view[c]]->x);
			rules->sep_y += (boid->y - boids[in_view[c]]->y);
		}
		c++;
	}
}

void	rules(t_boid **boids, t_boid *boid, int *neighbor, int nb)
{
	t_rules	rules;
	float	 speed;
	float	turnfactor;

	turnfactor = 0.5;
	get_allignement(&rules, boids, neighbor, nb);
	get_separation(&rules, boids, boid, neighbor, nb);
	get_cohesion(&rules, boids, neighbor, nb);
	boid->vx += ((rules.all_x - boid->vx) * 0.6) + ((rules.coh_x - boid->x ) * 0.005) + (rules.sep_x * 0.008);
	boid->vy += ((rules.all_y - boid->vy) * 0.6) + ((rules.coh_y - boid->y ) * 0.005) + (rules.sep_y * 0.008);
	if (boid->x + boid->vx < 100)
		boid->vx = boid->vx + turnfactor;
	if (boid->x + boid->vx> WIDTH - 100)
    	boid->vx = -boid->vx;
	if (boid->y + boid->vy > HEIGHT - 100)
    	boid->vy = boid->vy - turnfactor;
	if (boid->y + boid->vy < 100)
    	boid->vy = boid->vy + turnfactor;
	
	speed = sqrtf(boid->vx * boid->vx + boid->vy * boid->vy);
	if (speed > V_MAX)
	{
	    boid->vx = (boid->vx / speed) * V_MAX;
	    boid->vy = (boid->vy / speed) * V_MAX;
	}
	if (speed < V_MIN)
	{
	    boid->vx = (boid->vx / speed) * V_MIN;
	    boid->vy = (boid->vy / speed) * V_MIN;
	}
	boid->x += boid->vx;
	boid->y += boid->vy;
}
