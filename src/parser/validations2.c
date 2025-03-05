/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validations2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:41:55 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/05 13:45:52 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	invalid_file_content(t_rt *rt)
{
	if (rt->scene->camera.id == 0)
		return (error("Camera missing from file", 1));
	if (rt->scene->ambient.id == 0 && rt->scene->light.id == 0)
		return (error("Light source missing from file", 1));
	if (rt->scene->ambient.id != 0 && rt->scene->light.id == 0
		&& rt->scene->ambient.ratio == 0)
		return (error("At least one non-zero light source is required", 1));
	if (rt->scene->light.id != 0 && rt->scene->ambient.id == 0
		&& rt->scene->light.brightness == 0)
		return (error("At least one non-zero light source is required", 1));
	if (rt->scene->ambient.id != 0 && rt->scene->light.id != 0
		&& rt->scene->ambient.ratio == 0 && rt->scene->light.brightness == 0)
		return (error("At least one non-zero light source is required", 1));
	return (0);
}
