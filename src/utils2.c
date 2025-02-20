/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:26:53 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/20 11:31:09 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	while (n--)
		*temp++ = 0;
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	temp_src = (unsigned char *)src;
	temp_dst = (unsigned char *)dst;
	while (n > 0)
	{
		*temp_dst = *temp_src;
		n--;
		temp_dst++;
		temp_src++;
	}
	return (dst);
}