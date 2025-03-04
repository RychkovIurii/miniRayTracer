/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:45:07 by henbuska          #+#    #+#             */
/*   Updated: 2025/03/04 20:47:49 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

static char	*allocate_trimmed_string(char *line)
{
	char	*trimmed;

	trimmed = malloc(sizeof(char) * (count_new_length(line) + 1));
	if (!trimmed)
	{
		print_error("Memory allocation failed");
		return (NULL);
	}
	return (trimmed);
}

static int	should_copy(char c, int *flag)
{
	if (c == '\n')
		return (0);
	if (c != ' ')
	{
		*flag = 0;
		return (1);
	}
	if (*flag == 0)
	{
		*flag = 1;
		return (1);
	}
	return (0);
}

char	*trim_extra_spaces(char *line)
{
	int		i;
	int		j;
	int		flag;
	char	*trimmed;

	i = 0;
	j = 0;
	flag = 0;
	trimmed = allocate_trimmed_string(line);
	if (!trimmed)
		return (NULL);
	while (line[i])
	{
		if (should_copy(line[i], &flag))
			trimmed[j++] = line[i];
		i++;
	}
	while (j > 0 && trimmed[j - 1] == ' ')
		j--;
	trimmed[j] = '\0';
	return (trimmed);
}
