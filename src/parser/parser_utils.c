/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:43:18 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/17 18:27:46 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static int	count_new_length(char *line)
{
	int		i;
	int		new_len;
	int		flag;

	i = 0;
	flag = 0;
	new_len = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
		{
			new_len++;
			flag = 0;
		}
		else if (line[i] == ' ' && flag == 0)
		{
			new_len++;
			flag = 1;
		}
		i++;
	}
	return (new_len);	
}

char	*trim_extra_spaces(char *line)
{
	int		i;
	int		j;
	int		flag;
	char	*trimmed;

	flag = 0;
	trimmed = malloc(sizeof(char) * (count_new_length(line) + 1));
	if (!trimmed)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\n' && line[i + 1] == '\0')
			break;
		if (line[i] != ' ')
		{
			trimmed[j++] = line[i];
			flag = 0;
		}
		else if (line[i] == ' ' && flag == 0)
		{
			trimmed[j++] = line[i];
			flag = 1;
		}
		i++;
	}
	trimmed[j] = '\0';
	return (trimmed);
	//should trailing space be removed??
}

int	count_lines_in_file(int fd)
{
	int	line_count;
	char	*line;

	line_count = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[0] != '\0' && ft_strlen(line) > 0  && line[0] != '\n')
			line_count++;
		free(line);
	}
	return (line_count);
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
	return(fraction);
}

// Are overflow checks needed??

double	ft_atof(char *str)
{
	double	result;
	double	fraction;
	int		sign;

	result = 0;
	fraction = 0;
	sign = 1;
	if (*str != '-' && *str != '+' && !ft_isdigit(*str))
		return (-1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
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

void	print_error(char *message)
{
	printf("Error\n");
	printf("%s\n", message);
}

int	custom_atoi(char *str)
{
	long long int	check;
	long long int	result;
	int				sign;

	result = 0;
	sign = 1;
	if (*str != '-' && *str != '+' && !ft_isdigit(*str))
		return (-1);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		check = result * 10 + *str - '0';
		if (check / 10 != result && sign < 0)
			return (0);
		if (check / 10 != result && sign > 0)
			return (-1);
		result = check;
		str++;
	}
	if (*str)
		return (-1);
	return ((int)(sign * result));
}
