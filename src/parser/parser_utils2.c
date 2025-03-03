/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:52:16 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/03 14:04:20 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_error(char *message)
{
	printf("Error\n");
	printf("%s\n", message);
}

int	free_and_return(t_rt *rt, char **array, int ret)
{
	free_array(array);
	free_rt(rt);
	return (ret);
}

int	print_clean(t_rt *rt, char *message, int ret)
{
	(void)message; //do we need this? unused
	free_rt(rt);
	print_error("Invalid file content");
	return (ret);
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
