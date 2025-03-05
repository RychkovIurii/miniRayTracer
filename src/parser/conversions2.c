/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:47:18 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/05 13:30:06 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static	int	parse_fraction(char **str, double *fraction, int *error)
{
	double	divisor;
	int		has_fraction;

	divisor = 10.0;
	has_fraction = 0;
	(*str)++;
	if (!ft_isdigit(**str))
	{
		*error = 1;
		return (0);
	}
	while (**str && ft_isdigit(**str))
	{
		has_fraction = 1;
		*fraction += (**str - '0') / divisor;
		divisor *= 10.0;
		(*str)++;
	}
	return (has_fraction);
}

static int	parse_number(char **str, double *result, double *frac, int *error)
{
	int		has_digits;

	has_digits = 0;
	while (**str && ft_isdigit(**str))
	{
		has_digits = 1;
		*result = *result * 10.0 + (**str - '0');
		(*str)++;
	}
	if (**str == '.')
	{
		if (!parse_fraction(str, frac, error))
			return (0);
	}
	if (!has_digits || (**str != '\0' && !ft_isdigit(**str)))
	{
		*error = 1;
		return (0);
	}
	return (has_digits);
}

double	ft_atof_error(char *str, int *error)
{
	double	result;
	double	fraction;
	int		sign;

	*error = 0;
	result = 0.0;
	fraction = 0.0;
	if (!str || *str == '\0')
	{
		*error = 1;
		return (0);
	}
	sign = handle_sign(&str);
	if (*str == '0')
	{
		if (*(str + 1) != '.' && *(str + 1) != '\0')
		{
			*error = 1;
			return (0);
		}
	}
	if (!parse_number(&str, &result, &fraction, error))
		return (0);
	return (sign * (result + fraction));
}
