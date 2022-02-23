/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vheymans <vheymans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:29:51 by ialinaok          #+#    #+#             */
/*   Updated: 2022/02/23 18:28:31 by vheymans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		**line;
	int			check;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char *));
	*line = NULL;
	if (buffer[0] != '\0')
		join_line(line, buffer);
	while (!ft_strchr(*line, '\n'))
	{
		ft_bzero(buffer, BUFFER_SIZE);
		check = read(fd, buffer, BUFFER_SIZE);
		if (check <= 0 && !(**line))
			return (done_reading(line));
		buffer[check] = '\0';
		join_line(line, buffer);
		if (check < BUFFER_SIZE && !ft_strchr(*line, '\n'))
		{
			ft_bzero(buffer, BUFFER_SIZE);
			break ;
		}
	}
	return (*line);
}

void	*done_reading(char **line)
{
	//ft_bzero(buffer, BUFFER_SIZE);
	free(*line);
	free(line);
	return (NULL);
}

void	join_line(char **line, char *buffer)
{
	char	*tmp;
	char	*find_nl;
	int		i;
	int		j;

	i = 0;
	j = 0;
	find_nl = ft_strchr(buffer, '\n');
	tmp = allocate_tmp(line, find_nl, ft_strlen(buffer));
	if (!tmp)
		return ;
	while (line[0][j])
		tmp[i++] = line[0][j++];
	j = 0;
	while (buffer[j] != '\0' && buffer[j] != '\n')
		tmp[i++] = buffer[j++];
	if (buffer[j] == '\n')
	{
		tmp[i++] = buffer[j++];
		move_leftovers(buffer, ++find_nl);
	}
	tmp[i] = '\0';
	free(line[0]);
	line[0] = tmp;
}

char	*allocate_tmp(char **line, char *find_nl, size_t buff_size)
{
	char	*tmp;

	if (find_nl)
		tmp = malloc(ft_strlen(*line) + buff_size - ft_strlen(find_nl) + 1);
	else
		tmp = malloc(ft_strlen(*line) + buff_size + 1);
	return (tmp);
}

void	move_leftovers(char *buffer, char *find_nl)
{
	int	i;

	i = 0;
	while (find_nl[i])
	{
		buffer[i] = find_nl[i];
		i++;
	}
	while (buffer[i])
		buffer[i++] = '\0';
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd = 0;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("line 1: %s", line);
	line = get_next_line(fd);
	printf("line 2: %s", line);
	line = get_next_line(fd);
	printf("line 3: %s", line);
	line = get_next_line(fd);
	printf("line 4: %s", line);
	return (0);
}