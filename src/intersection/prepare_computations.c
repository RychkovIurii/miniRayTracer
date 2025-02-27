/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_computations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:39:01 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/27 16:50:02 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_lstclear_safe(t_list **lst)
{
	t_list	*ptr;
	t_list	*tmp;

	if (lst)
	{
		ptr = *lst;
		while (ptr != NULL)
		{
			tmp = ptr->next;
			free(ptr);
			ptr = tmp;
		}
		*lst = NULL;
	}
}

void	ft_lstremove(t_list **lst, void *content)
{
	t_list	*ptr;
	t_list	*prev;

	if (lst == NULL || *lst == NULL)
		return ;
	ptr = *lst;
	prev = NULL;
	while (ptr != NULL)
	{
		if (ptr->content == content)
		{
			if (prev == NULL)
				*lst = ptr->next;
			else
				prev->next = ptr->next;
			free(ptr);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

t_intersection prepare_computations(t_intersection hit, t_ray ray, t_intersects *xs)
{
	t_intersection comps;
	t_list *containers = NULL;  // Keeps track of the objects the ray is inside
	t_list *temp;
	int i;

	comps.t = hit.t;
	comps.object = hit.object;
	comps.point = get_ray_position(ray, comps.t);
	comps.eyev = negate_tuple(ray.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	
	if (dot(comps.normalv, comps.eyev) < 0)
		comps.normalv = negate_tuple(comps.normalv);

	comps.over_point = add_tuple(comps.point, multiply_tuple_scalar(comps.normalv, EPSILON));
	comps.under_point = substract_tuple(comps.point, multiply_tuple_scalar(comps.normalv, EPSILON));
	comps.reflectv = reflect(ray.direction, comps.normalv);
	
	comps.n1 = 1.0;
	comps.n2 = 1.0;

	if (!xs || xs->count == 0)  // If `xs` is NULL or empty, just return comps
		return comps;

for (i = 0; i < xs->count; i++)
{
		// If this intersection is the hit, record n1 (before processing)
		if (xs->array[i].object == hit.object && fabs(xs->array[i].t - hit.t) < EPSILON)
		{
			if (!containers || ft_lstlast(containers) == NULL)
				comps.n1 = 1.0;
			else
			{
				t_shape *shape = (t_shape *)ft_lstlast(containers)->content;
				if (shape) {
					comps.n1 = shape->material.refractive_index;
				} else {
					comps.n1 = 1.0;
				}
			}
		}

		// Process this intersection: if the object is already in containers, remove it; otherwise, add it.
		int removed = 0;
		temp = containers;
		while (temp)
		{
			if (temp->content == xs->array[i].object)
			{
				ft_lstremove(&containers, temp->content);
				removed = 1;
				break;
			}
			temp = temp->next;
		}
		if (!removed)
			ft_lstadd_back(&containers, ft_lstnew(xs->array[i].object));

		// If this intersection is the hit, record n2 (after processing) and break.
		if (xs->array[i].object == hit.object && fabs(xs->array[i].t - hit.t) < EPSILON)
		{
			if (!containers || ft_lstlast(containers) == NULL)
				comps.n2 = 1.0;
			else
			{
				t_shape *shape = (t_shape *)ft_lstlast(containers)->content;
				if (shape) {
					comps.n2 = shape->material.refractive_index;
				} else {
					comps.n2 = 1.0;
				}
			}
			break;
		}
	}
	ft_lstclear_safe(&containers);
	return (comps);
}
