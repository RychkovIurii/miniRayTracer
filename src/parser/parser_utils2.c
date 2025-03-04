/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:52:16 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/04 13:29:23 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_error(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
}

int	free_and_return(t_rt *rt, char **array, int ret)
{
	if (array)
		free_array(array);
	free_rt(rt);
	return (ret);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_arrays(char **array1, char **array2)
{
	if (array1)
	{
		free_array(array1);
		*array1 = NULL;
	}
	if (array2)
	{
		free_array(array2);
		*array2 = NULL;
	}
}
