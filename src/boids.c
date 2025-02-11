#include "boids.h"

float	get_angle(t_boid *current, t_boid *comp){

	float	angle;
	float	scalaire;
	float	norme_current;
	float	norme_comp;

	scalaire = (current-> vx * (comp->x - current->x)) + (current->vy * (comp->y - current->y)); 
	norme_current = sqrtf(powf(current->vx, 2) + powf(current->vy, 2));
	norme_comp = sqrtf(powf(comp->x - current->x, 2) + powf(comp->y - current->y, 2));
	angle = acosf(scalaire / (norme_current * norme_comp)); 
	return (angle * ( 180 / M_PI));
}

t_nb_view	*boid_in_view(t_boid **boids, int i, float field_distance){

	t_nb_view	*nb_v;
	t_nb_view	*head;
	int			j;
	float		d;
	float		angle;

	j = 0;
	fprintf(stderr, "============================%d========================\n\n", i);
	nb_v = NULL;
	d = sqrtf(powf((boids[j]->x - boids[i]->x), 2) + powf((boids[j]->y - boids[i]->y), 2));
	angle = get_angle(boids[i], boids[j]);
	if (d <= field_distance && ((angle * (M_PI / 180)) <= 120 || (angle * (M_PI / 180)) >= 240 ))
	{
		if (j == i)
			j++;
		fprintf(stderr, "boid %d is in view | ", j);
		head = new_node(j);
		j++;
	}
	else
		head = NULL;
	while (j < NB_BOIDS - 1)
	{
		if (j == i)
			j++;
		d = sqrtf(powf((boids[j]->x - boids[i]->x), 2) + powf((boids[j]->y - boids[i]->y), 2));
		angle = get_angle(boids[i], boids[j]);
		if (d <= field_distance && (angle  <= 60 || angle >= 300 ))
		{
			fprintf(stderr, "boid %d is in view | ", j);
			nb_v = new_node(j);
			add_back(head, nb_v);
		}
		j++;
	}
		fprintf(stderr, "============================%d========================\n\n", i);

	return (head);
}

float	how_many_in_view(t_nb_view *in_view){
	
	float		nb;
	t_nb_view	*tmp;

	nb = 0;
	tmp = in_view;
	while (tmp)
	{
		tmp = tmp->next;
		nb++;
	}
	return (nb);
}

void	rules(t_nb_view *view, t_moyenne *moy, t_boid **boids, int	i){

	float		n_in_view;
	t_nb_view	*head;
	float		d;
	float		norme;

	head = view;
	n_in_view = how_many_in_view(view); // compte le nombre de boid dans la chaine
	fprintf(stderr, "nb_in_view = %f\n", n_in_view);
	while (view)
	{
		// cohesiion
		moy->coh_x += boids[view->n]->x;
		moy->coh_y += boids[view->n]->y;
		// allignement
		moy->all_x += boids[view->n]->vx;
		moy->all_y += boids[view->n]->vy;
		view = view->next;
	}
	if (n_in_view > 0)
	{
		moy->coh_x /= n_in_view;	
		moy->coh_y/= n_in_view;
		moy->coh_x -= boids[i]->x;	
		moy->coh_y -= boids[i]->y;
		//allignement
		norme = sqrtf(powf(moy->all_x, 2) + powf(moy->all_y, 2));
		if (norme > 0)
		{
		moy->all_x /= norme;	
		moy->all_y /= norme;
		}
	}
	view = head;
	while (view)
	{
		d = sqrtf(powf(boids[view->n]->x - boids[i]->x, 2) + powf(boids[view->n]->y - boids[i]->y, 2));
		if (d < D_MIN)
		{
			moy->sep_x += ((boids[i]->x - boids[view->n]->x) / d);
			moy->sep_y += ((boids[i]->y - boids[view->n]->y) / d);
		}
		view = view->next;
	}
	view = head;
}

void	get_direction(t_boid **boids, t_param *param){

	t_nb_view	*view;
	t_moyenne	moy;
	int			i;
	float		norme;

	i = 0;
	moy.sep_x = 0;	
	moy.all_x = 0;
	moy.all_y = 0;
	moy.coh_y = 0;	
	moy.coh_x = 0;
	moy.sep_y = 0;
	while (boids[i])
	{
		view = boid_in_view(boids, i, 100);
		if (view != NULL)
		{
			rules(view, &moy, boids, i);
			fprintf(stderr, "I = %d, vx %f vy %f\n", i, boids[i]->vx, boids[i]->vy);
			boids[i]->vx += (moy.coh_x * param->coh) + (moy.all_x * param->all) + (moy.sep_x * param->sep);
			boids[i]->vy += (moy.coh_y * param->coh) + (moy.all_y * param->all) + (moy.sep_y * param->sep);
			norme = sqrtf(powf(boids[i]->vx, 2) + powf(boids[i]->vy, 2));
			if (norme > V_MAX)
			{
				boids[i]->vx /= norme * V_MAX;
				boids[i]->vy /= norme * V_MAX;
			}
			fprintf(stderr, "I = %d, vx %f vy %f\n", i, boids[i]->vx, boids[i]->vy);
		}
		if (view)
			free_inview(view);
		view = NULL;
		i++;
	}
}

void	boid_update_rand(t_boid **boids, t_param *param){
	
	int	i;

	i = 0;
	get_direction(boids, param);
	while (boids[i])
	{
		if ((boids[i]->x +  boids[i]->vx) > WIDTH - 10){
			boids[i]->vx = -boids[i]->vx;
			boids[i]->vy = rand_float_range(-1.0f, 1.0f);
		}
		else if ((boids[i]->y +  boids[i]->vy) > HEIGHT - 10){
			boids[i]->vy = -boids[i]->vy;
			boids[i]->vx = rand_float_range(-1.0f, 1.0f);
		}
		else if ((boids[i]->x +  boids[i]->vx) < 0 + 10){
			boids[i]->vx = -boids[i]->vx;
			boids[i]->vy = rand_float_range(-1.0f, 1.0f);
		}
		else if ((boids[i]->y +  boids[i]->vy) < 0 + 10){
			boids[i]->vy = -boids[i]->vy;
			boids[i]->vx = rand_float_range(-1.0f, 1.0f);
		}
		else
		{
			boids[i]->x += boids[i]->vx;
			boids[i]->y += boids[i]->vy;
		}
		i++;
	}
}

void	draw_boids(t_boid **boids, SDL_Renderer *renderer)
{
	int			i;
	float		angle;
	t_triangle	tr;

	i = 0;
	while (boids[i]){
		angle = atan2(boids[i]->vy, boids[i]->vx);

		tr.p1.x = boids[i]->x + cos(angle) * 10;
		tr.p1.y = boids[i]->y + sin(angle) * 10;
    	tr.p2.x = boids[i]->x + cos(angle + 2.5) * 10;
		tr.p2.y = boids[i]->y + sin(angle + 2.5) * 10;
		tr.p3.x = boids[i]->x + cos(angle - 2.5) * 10;
		tr.p3.y = boids[i]->y + sin(angle - 2.5) * 10;
	    SDL_RenderDrawLine(renderer, tr.p1.x, tr.p1.y, tr.p2.x, tr.p2.y);
	    SDL_RenderDrawLine(renderer, tr.p2.x, tr.p2.y, tr.p3.x, tr.p3.y);
	    SDL_RenderDrawLine(renderer, tr.p3.x, tr.p3.y, tr.p1.x, tr.p1.y);
		i++;
	}
}