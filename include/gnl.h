/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 17:40:42 by irychkov          #+#    #+#             */
/*   Updated: 2025/03/02 16:14:01 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl
{
	char	*stack;
	int		fd;
}			t_gnl;

char	*get_next_line(int fd);
ssize_t	ft_strlen_buf(const char	*str);
char	*ft_extract_line(char *stack);
char	*free_stuff(char **ptr);
char	*ft_strlcat_buf(char *stack, char *buffer, ssize_t bytes_read);
char	*ft_strdup_buf(const char *s1);

#endif
