/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:07:53 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/02 16:45:42 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"
#include <limits.h>

int	rt_atoi(char *str)
{
	long long int	result;
	int				sign;

	result = 0;
	sign = 1;
	if (*str != '-' && *str != '+' && !ft_isdigit(*str))
		return (-1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			return (-1);
		str++;
	}
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

static double	handle_fraction(char *str)
{
	double	fraction;
	double	divisor;

	divisor = 10.0;
	fraction = 0;
	while (*str && ft_isdigit(*str))
	{
		fraction = fraction + (*str - '0') / divisor;
		divisor *= 10.0;
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (fraction);
}

static int	handle_sign(char **str)
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
	int		sign;

	result = 0;
	fraction = 0;
	if (*str != '-' && *str != '+' && !ft_isdigit(*str))
		return (-1);
	sign = handle_sign(&str);
	while (*str && ft_isdigit(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		fraction = handle_fraction(str);
	}
	if (fraction == -1)
		return (-1);
	return (sign * (result + fraction));
}
