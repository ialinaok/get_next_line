/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 11:35:41 by apielasz          #+#    #+#             */
/*   Updated: 2022/02/18 22:30:24 by apielasz         ###   ########.fr       */
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
char	*full_line(char *tmp, char *buffer);
void	join_line(char **tmp, char *buffer);
void	move_leftovers(char *buffer, char *find_nl);

#endif