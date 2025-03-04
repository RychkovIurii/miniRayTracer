/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:43:33 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/04 20:47:15 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	parse_element(char **element, t_rt *rt)
{
	if (ft_strcmp(element[0], "A") == 0)
		return (parse_ambient(element, rt));
	else if (ft_strcmp(element[0], "C") == 0)
		return (parse_camera(element, rt));
	else if (ft_strcmp(element[0], "L") == 0)
		return (parse_light(element, rt));
	else if (ft_strcmp(element[0], "sp") == 0)
		return (parse_sphere_bonus(element, rt));
	else if (ft_strcmp(element[0], "pl") == 0)
		return (parse_plane_bonus(element, rt));
	else if (ft_strcmp(element[0], "cy") == 0)
		return (parse_cylinder_bonus(element, rt));
	else if (ft_strcmp(element[0], "co") == 0)
		return (parse_cone_bonus(element, rt));
	else
	{
		ft_putendl_fd("Invalid element identifier", 2);
		return (1);
	}
	return (0);
}
