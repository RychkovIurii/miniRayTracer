/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 16:06:32 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/02 16:10:42 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

size_t	ft_strlen(const char	*str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s) + 1;
	while (s_len)
	{
		s_len--;
		if (s[s_len] == (char)c)
			return ((char *)(s + s_len));
	}
	return (NULL);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		(void)write(fd, &s[i], 1);
		i++;
	}
	(void)write(fd, "\n", 1);
}
