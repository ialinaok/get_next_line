/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:29:51 by ialinaok          #+#    #+#             */
/*   Updated: 2022/02/10 23:29:25 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buff_join;
	static char	*leftover;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff_join = read_buffers(fd);
	int i = 0;
	while (buff_join[i] != '\n')
		i++;
	line = cut_line(buff_join, i);
	leftover = get_leftover(buff_join, i);
	free(buff_join);
}

// this function to read until it finds newline character
// and return a line merged up
// orrr maybe it would be useful to save the osition of the newline?

char	*read_buffers(int fd)
{
	char	*buff[BUFFER_SIZE + 1];
	int		check;
	char	*buff_join;
	char	*find_n;

	*buff_join = '\0';
	check = read(fd, buff, BUFFER_SIZE);
	if (check == -1)
		return (NULL);
	buff[BUFFER_SIZE] = '\0';
	while ((find_n = ft_strchr(buff, '\n') == NULL)
	{
		// read another buffer... into what tho, I have to move the buff somewhere
		// use strjoin for line and buffer? hmhmhmmm
		buff_join = ft_strjoin(buff_join, buff);
		check = read(fd, buff, BUFFER_SIZE);
		if (check == -1)
			return (NULL);
	}
	else
	{
		//you know where the line ends, you can save the leftover and return then the line
		// but it's not cut yet!!!
		line = ft_strjoin(buff_join, buff);
	}
	return (buff_join) // I pass by reference, so I can free it in gnl as well
}

// copy the line until the newline character and return it
char	*cut_line(char *buff_join, int i)
{
	char	line[i + 2]; // one for the newline, and one for null char
	int		j;

	j = 0;
	while (j < i + 2)
	{
		line[j] = *buff_join++;
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*get_leftover(char *buff_join, int i)
{
	char	leftover[ft_strlen(buff_join) - i];
	int		j;

	j = i;
	while ()
}