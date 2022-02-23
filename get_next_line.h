/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:00:56 by ialinaok          #+#    #+#             */
/*   Updated: 2022/02/23 12:57:12 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(char const *str);
void	ft_bzero(void *s, size_t n);
char	*ft_strchr(char const *str, int c);
void	join_line(char **line, char *buffer);
void	move_leftovers(char *buffer, char *find_nl);
char	*done_reading(char **line, char *buffer);
char	*allocate_tmp(char **line, char *find_nl);
char	*get_next_line(int fd);

#endif