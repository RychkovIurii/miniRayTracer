/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:45:07 by henbuska          #+#    #+#             */
/*   Updated: 2025/02/27 15:40:58 by henbuska         ###   ########.fr       */
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
			break ;
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
