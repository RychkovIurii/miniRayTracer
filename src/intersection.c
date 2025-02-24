/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:25:42 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/24 15:30:54 by henbuska         ###   ########.fr       */
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

/* Checks to see if the intersection at 't' is within a radius
(radius of cylinder) from the y axis */

int	check_cylinder_cap(t_shape cyl, t_ray ray, double t)
{
	double	x;
	double	z;
	double	sum_of_squares;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;

	sum_of_squares = x * x + z * z;
	return (sum_of_squares <= cyl.radius * cyl.radius);
}

/* Checks cap intersectins (top and bottom)
 - if the ray's y-direction is close to zero (parallel to cap), skips cap checks since
   ray cannot intersect cylinder
 - calculates t for top cap and bottom cap
 - uses check_cap function to check if the intersection point lies within the cap's radius
 - adds valid cap intersections to xs
 */

t_intersects	intersect_cylinder_caps(t_shape *cyl, t_ray ray, t_intersects result)
{
	double	t;

	t = (cyl->min - ray.origin.y) / ray.direction.y;  // check intersection with bottom cap
	if (check_cylinder_cap(*cyl, ray, t))
	{
		result.array[2].t = t;
		result.count = 3;
		result.array[2].object = cyl;
	}
	t = (cyl->max - ray.origin.y) / ray.direction.y;  // check intersection with top cap
	if (check_cylinder_cap(*cyl, ray, t))
	{
		result.array[3].t = t;
		result.count = 4;
		result.array[3].object = cyl;
	}
	return (result);
}

t_intersects	local_intersect_cylinder(t_shape *cylinder, t_ray ray)
{
	t_intersects	result;
	double			a;
	double			b;
	double			c;
	double			discriminant;
	double			sqrt_discriminant;
	double			temp;
	double			y0;
	double			y1;
	double			t0;
	double			t1;
	int				count;
	
	//ft_bzero(&result, sizeof(t_intersects));
	/* Wall intersections
	 - if discriminant is negative, the ray misses the wall completely
	 - if a is effectively zero (i.e. ray is parallel to the cylinder's axis), skip wall
	checking and move to check caps */
	
	result.count = 0;
	result.array = ft_calloc(4, sizeof(t_intersection));
	if (!result.array)
		return (result);
	a = (ray.direction.x * ray.direction.x) + (ray.direction.z * ray.direction.z);
	if (fabs(a) > EPSILON)
	{
		b = 2 * ray.origin.x * ray.direction.x + 2 * ray.origin.z * ray.direction.z;
		c = ray.origin.x * ray.origin.x + ray.origin.z * ray.origin.z - 1;
		discriminant = b * b - 4 * a * c;
		if (discriminant >= 0)
		{
			sqrt_discriminant = sqrt(discriminant);
			t0 = (-b - sqrt_discriminant) / (2 * a); // Closest intersection
			t1 = (-b + sqrt_discriminant) / (2 * a); // Farther intersection
			//printf("Wall Intersection t0: %f, t1: %f\n", t0, t1);
			/*if (t0 > t1)
			{
				temp = t0;
				t0 = t1;
				t1 = temp;
			}	*/
			//check corresponding y coordinates for each t to determine whether the intersection is within
			//the cylinder's height bounds and add valid intersections to xs
			y0 = ray.origin.y + t0 * ray.direction.y;
			if (cylinder->min < y0 && y0 < cylinder->max)
			{
				//printf("Valid wall intersection at t0: %f, y0: %f\n", t0, y0);
				result.array[0].t = t0;
				result.count = 1;
				result.array[0].object = cylinder;
			}
			y1 = ray.origin.y + t1 * ray.direction.y;
			if (cylinder->min < y1 && y1 < cylinder->max)
			{
				//printf("Valid wall intersection at t1: %f, y1: %f\n", t1, y1);
				result.array[1].t = t1;
				result.count = 2;
				result.array[1].object = cylinder;
			}
		}
	}
	/* Check intersections for caps */
	if (cylinder->closed == 1 && fabs(ray.direction.y) > EPSILON)
		result = intersect_cylinder_caps(cylinder, ray, result);
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
	else if (shape->type == SHAPE_CYLINDER)
	{
		return local_intersect_cylinder(shape, local_ray);
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

t_tuple	local_normal_at_cylinder(t_shape cylinder, t_tuple point)
{
	double	distance;
	
	distance = point.x * point.x + point.z * point.z;
	if (distance < (cylinder.radius * cylinder.radius) && point.y >= cylinder.max - EPSILON)
		return (vector(0, 1, 0));
	else if (distance < (cylinder.radius * cylinder.radius) && point.y <= cylinder.min + EPSILON)
		return (vector(0, -1, 0));
	else
		return (vector(point.x, 0, point.z));
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
	else if (shape->type == SHAPE_CYLINDER)
	{
		local_normal = local_normal_at_cylinder(*shape, local_point);
	}
	world_normal = multiply_matrix_by_tuple(shape->transpose_inv, local_normal);
	world_normal.w = 0;
	surface_normal = normalize(world_normal);
	return (surface_normal);
}
