/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:25:42 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/24 12:52:46 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void free_intersects(t_intersects *xs)
{
	/* if (!xs || !xs->array)
		return; */
	if (xs->array)
		free(xs->array);
	xs->array = NULL;
	xs->count = 0;
}

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
	
    comps.inside = 0;
    if (dot(comps.normalv, comps.eyev) < 0)
    {
        comps.inside = 1;
        comps.normalv = negate_tuple(comps.normalv);
    }

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
            if (!containers /* || ft_lstlast(containers) == NULL */)
                comps.n1 = 1.0;
            else
            {
                t_shape *shape = (t_shape *)ft_lstlast(containers)->content;
                comps.n1 = shape->material.refractive_index;
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
            if (!containers /* || ft_lstlast(containers) == NULL */)
                comps.n2 = 1.0;
            else
            {
                t_shape *shape = (t_shape *)ft_lstlast(containers)->content;
                comps.n2 = shape->material.refractive_index;
            }
            break;
        }
    }
    ft_lstclear_safe(&containers);

    return (comps);
}

t_intersection	*hit(t_intersects intersections)
{
	int	i;

	i = 0;
	while (i < intersections.count)
	{
		if (intersections.array[i].t > EPSILON)
			return (&intersections.array[i]);
		i++;
	}
	return (NULL);
}

t_intersects local_intersect_sphere(t_shape *sphere, t_ray transformed_ray)
{
	t_intersects result;
	t_tuple		sphere_to_ray;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		sqrt_d;

	ft_bzero(&result, sizeof(t_intersects));
	sphere_to_ray = substract_tuple(transformed_ray.origin, sphere->center);
	a = dot(transformed_ray.direction, transformed_ray.direction);
	b = 2 * dot(transformed_ray.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return result;
	sqrt_d = sqrt(discriminant);
	result.count = 2;
	result.array = malloc(sizeof(t_intersection) * 2);
	result.array[0].t = (-b - sqrt_d) / (2 * a);
	result.array[0].object = sphere;
	result.array[1].t = (-b + sqrt_d) / (2 * a);
	result.array[1].object = sphere;

	return result;
}

t_intersects local_intersect_plane(t_shape *plane, t_ray transformed_ray)
{
	t_intersects result;

	ft_bzero(&result, sizeof(t_intersects));
	if (fabs(transformed_ray.direction.y) < EPSILON)

		return result;
	result.count = 1;
	result.array = malloc(sizeof(t_intersection));
	result.array[0].t = -transformed_ray.origin.y / transformed_ray.direction.y;
	result.array[0].object = plane;
	return (result);
}

t_intersects intersect(t_shape *shape, t_ray ray)
{
	t_ray local_ray;

	local_ray = transform_ray(ray, shape->transform_inv);
	if (shape->type == SHAPE_SPHERE)
	{
		return local_intersect_sphere(shape, local_ray);
	}
	else if (shape->type == SHAPE_PLANE)
	{
		return local_intersect_plane(shape, local_ray);
	}

	return (t_intersects){0, NULL};  // No intersections for unknown shapes
}

t_tuple local_normal_at_sphere(t_tuple sphere_center, t_tuple local_point)
{
	return (substract_tuple(local_point, sphere_center));
}

t_tuple local_normal_at_plane(t_tuple local_point)
{
	(void)local_point;
	return (vector(0, 1, 0));
}

t_tuple	normal_at(t_shape *shape, t_tuple world_point)
{
	t_tuple surface_normal;
	t_tuple world_normal;
	t_tuple local_point;
	t_tuple local_normal;

	local_point = multiply_matrix_by_tuple(shape->transform_inv, world_point);
	if (shape->type == SHAPE_SPHERE)
	{
		local_normal = local_normal_at_sphere(shape->center, local_point);
	}
	else if (shape->type == SHAPE_PLANE)
	{
		local_normal = local_normal_at_plane(local_point);
	}
	world_normal = multiply_matrix_by_tuple(shape->transpose_inv, local_normal);
	world_normal.w = 0;
	surface_normal = normalize(world_normal);
	return (surface_normal);
}
