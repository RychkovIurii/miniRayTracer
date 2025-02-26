/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:04:05 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/26 15:18:53 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_material(char **element, t_rt *rt)
{
	char	**coordinates;
	char	**colors;
	double	brightness;

	if (rt->scene->light.id != 0)
		return (error("Too many lights in file", 1));
	if (validate_argument_count(element, 4))
		return (error("Invalid number of arguments for light", 1));
	coordinates = validate_coordinates(element[1]);
	if (!coordinates)
		return (error("Invalid coordinates for light point", 1));
	rt->scene->light.position = string_to_point(coordinates);
	brightness = validate_ratio(element[2]);
	if (brightness == -1)
		return (error("Invalid brightness for light [0.0-1.0]", 1));
	rt->scene->light.brightness = brightness;
	colors = validate_color(element[3]);
	if (!colors)
		return (error("Invalid color for light", 1));
	rt->scene->light.color = string_to_color(colors);
	rt->scene->light.id = 1;
	return (0);
}