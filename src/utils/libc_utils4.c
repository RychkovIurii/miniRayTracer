/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_utils4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henbuska <henbuska@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:11:06 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/03 16:50:24 by henbuska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static size_t	ft_strcounter(char const *s, char c)
{
	size_t	elements;

	elements = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s && *s != c)
		{
			elements++;
			while (*s && *s != c)
				s++;
		}
		while (*s && *s == c)
			s++;
	}
	return (elements);
}

static void	free_back(char **array, size_t i)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free(array);
}

static char	**ft_helper(char const *s, char c, size_t i, char **result)
{
	const char	*start;

	while (*s)
	{
		if (*s && *s != c)
		{
			start = s;
			while (*s && *s != c)
				s++;
			result[i] = (char *)malloc(sizeof(char) * (s - start + 1));
			if (!result[i])
			{
				free_back(result, i);
				return (NULL);
			}
			ft_strlcpy(result[i], start, s - start + 1);
			i++;
		}
		while (*s && *s == c)
			s++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	char		**result;

	i = 0;
	result = (char **)malloc(sizeof(char *) * (ft_strcounter(s, c) + 1));
	if (!result || !s)
		return (NULL);
	return (ft_helper(s, c, i, result));
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
