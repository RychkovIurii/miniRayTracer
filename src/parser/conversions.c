/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:07:53 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/05 13:34:27 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <limits.h>

int	rt_atoi(char *str)
{
	long long int	result;

	result = 0;
	if (*str == '+')
		str++;
	if (!ft_isdigit(*str))
		return (-1);
	if (*str == '0' && *(str + 1) != '\0')
		return (-1);
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + *str - '0';
		if (result > INT_MAX)
			return (-1);
		str++;
	}
	if (*str)
		return (-1);
	return ((int)result);
}

int	handle_sign(char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	double	divisor;
	int		sign;

	result = 0.0;
	fraction = 0.0;
	divisor = 10.0;
	sign = handle_sign(&str);
	while (ft_isdigit(*str))
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			fraction += (*str++ - '0') / divisor;
			divisor *= 10.0;
		}
	}
	return (sign * (result + fraction));
}
