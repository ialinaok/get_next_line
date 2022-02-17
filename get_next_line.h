/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:35:41 by apielasz          #+#    #+#             */
/*   Updated: 2022/02/17 23:01:23 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(char const *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_bzero(void *s, size_t n);
char	*ft_strchr(char const *str, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*get_next_line(int fd);
char	*read_buffers(int fd, char *buffer, char **tmp);
int		full_line(char *tmp, char *buffer, char *line);

#endif