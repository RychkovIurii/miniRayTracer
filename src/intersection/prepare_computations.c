/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_computations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:39:01 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/28 12:57:16 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/*
** Initializes the computations structure with the necessary values.
*/
t_intersection	initialize_computations(t_intersection hit, t_ray ray)
{
	t_intersection	comps;

	comps.t = hit.t;
	comps.object = hit.object;
	comps.point = get_ray_position(ray, comps.t);
	comps.eyev = negate_tuple(ray.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	if (dot(comps.normalv, comps.eyev) < 0)
		comps.normalv = negate_tuple(comps.normalv);
	comps.over_point = add_tuple(comps.point, multiply_tuple_scalar(
				comps.normalv, EPSILON));
	comps.under_point = substract_tuple(comps.point, multiply_tuple_scalar(
				comps.normalv, EPSILON));
	comps.reflectv = reflect(ray.direction, comps.normalv);
	comps.n1 = 1.0;
	comps.n2 = 1.0;
	return (comps);
}

/*
** Finds the refractive index of the object in the containers list.
*/
double	find_n(t_list *containers)
{
	t_shape	*shape;

	if (!containers || !ft_lstlast(containers))
		return (1.0);
	shape = (t_shape *)ft_lstlast(containers)->content;
	if (shape)
		return (shape->material.refractive_index);
	return (1.0);
}

/*
** Updates the containers list with the object.
*/
void	update_containers(t_list **containers, t_shape *object)
{
	t_list	*temp;

	temp = *containers;
	while (temp)
	{
		if (temp->content == object)
		{
			ft_lstremove(containers, temp->content);
			return ;
		}
		temp = temp->next;
	}
	ft_lstadd_back(containers, ft_lstnew(object)); // Check return value
}

/*
** Prepares the computations structure for the intersection.
** Finds the refractive index of intersected object.
*/
t_intersection	prepare_computations(
			t_intersection hit, t_ray ray, t_intersects *xs)
{
	int				i;
	t_list			*containers;
	t_intersection	comps;

	containers = NULL;
	comps = initialize_computations(hit, ray);
	if (!xs || xs->count == 0)
		return (comps);
	i = 0;
	while (i < xs->count)
	{
		if (xs->array[i].object == hit.object
			&& fabs(xs->array[i].t - hit.t) < EPSILON)
			comps.n1 = find_n(containers);
		update_containers(&containers, xs->array[i].object);
		if (xs->array[i].object == hit.object
			&& fabs(xs->array[i].t - hit.t) < EPSILON)
		{
			comps.n2 = find_n(containers);
			break ;
		}
		i++;
	}
	ft_lstclear_safe(&containers);
	return (comps);
}
