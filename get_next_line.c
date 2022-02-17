/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:29:51 by ialinaok          #+#    #+#             */
/*   Updated: 2022/02/17 23:17:04 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = malloc(sizeof(char));
	*tmp = '\0';
	if (buffer[0] != '\0') // that means there are leftovers
	{
		line = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = line;
		ft_bzero(buffer, BUFFER_SIZE);
	}
	line = read_buffers(fd, buffer, &tmp);
	return (line);
}

char	*read_buffers(int fd, char *buffer, char **tmp)
{
	int		check;
	char	*find_n;
	int		leftovers;
	char	*line = NULL;

	check = read(fd, buffer, BUFFER_SIZE);
	if (check == -1)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	// while (check != -1)
	// {
		// find_n = 
		while (ft_strchr(buffer, '\n')) // that means, if there is no newline in current buffer
		{
			line = ft_strjoin(*tmp, buffer);
			free(*tmp);
			*tmp = line;
			ft_bzero(buffer, BUFFER_SIZE);
			check = read(fd, buffer, BUFFER_SIZE);
			if(check == - 1)
				return NULL;
			buffer[BUFFER_SIZE] = '\0';
			find_n = ft_strchr(buffer, '\n');
		}
		if (find_n != NULL) // so when I DO find a newline character //tmp has a current line of joined buffers
		{
			leftovers = BUFFER_SIZE - full_line(*tmp, buffer, line);
			ft_memcpy(buffer, ++find_n, leftovers);
		}
	// }
	return (*tmp);
}

int	full_line(char *tmp, char *buffer, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i] != '\n')
		i++;
	line = (char *) malloc(ft_strlen(tmp) + i + 1);
	// line now points to a newline space, which is not filled yet
	while (*tmp)
		*line++ = *tmp++;
	j = 0;
	// I want to copy till \n and \n itself too, so i + 1 bytes
	while (j <= i + 1)
	{
		*line++ = buffer[j];
		j++;
	}
	// free(tmp);
	return (i);
}

#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd = 0;
	char	*linea;
	char	*lineb;

	fd = open("test.txt", O_RDONLY);
	linea = get_next_line(fd);
	lineb = get_next_line(fd);
	printf("this is fd: %d\nthis is line a: %s\nthis is line b: %s", fd, linea, lineb);
}

///code graveyard
// char	*read_buffers(int fd);
// char	*cut_line(char *buff_join, int n, char *leftover);

// char	*get_next_line(int fd)
// {
// 	char		*buff_join;
// 	static char	leftover[BUFFER_SIZE + 1];
// 	char		*line;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	buff_join = read_buffers(fd);
// 	int n = 0;
// 	while (buff_join[n] != '\n')
// 		n++;
// 	line = cut_line(buff_join, n, leftover);
// 	free(buff_join);
// 	return (line);
// }

// // this function to read until it finds newline character
// // and return a line merged up
// // orrr maybe it would be useful to save the osition of the newline?

// char	*read_buffers(int fd)
// {
// 	char	buff[BUFFER_SIZE + 1];
// 	int		check;
// 	char	*buff_join;
// 	char	*find_n;

// 	check = read(fd, buff, BUFFER_SIZE);
// 	if (check == -1)
// 		return (NULL);
// 	buff[BUFFER_SIZE] = '\0';
// 	while ((find_n = ft_strchr(buff, '\n')) == NULL)
// 	{
// 		// read another buffer... into what tho, I have to move the buff somewhere
// 		// use strjoin for line and buffer? hmhmhmmm
// 		buff_join = ft_strjoin(buff_join, buff);
// 		if (!buff_join)
// 			return (NULL);
// 		check = read(fd, buff, BUFFER_SIZE);
// 		if (check == -1)
// 			return (NULL);
// 	}
// 		//you know where the line ends, you can save the leftover and return then the line
// 		// but it's not cut yet!!!
// 		buff_join = ft_strjoin(buff_join, buff);
// 		if (!buff_join)
// 			return (NULL);
// 	return (buff_join); // I pass by reference, so I can free it in gnl as well
// }

// // copy the line until the newline character and return it
// char	*cut_line(char *buff_join, int n, char *leftover)
// {
// 	char	line[n];
// 	int		j;
// 	int		i;

// 	j = 0;
// 	while (j < n + 2)
// 	{
// 		line[j] = *buff_join++;
// 		j++;
// 	}
// 	line[j] = '\0';
// 	i = 0;
// 	while (buff_join[j])
// 	{
// 		leftover[i] = buff_join[j];
// 		i++;
// 		j++;
// 	}
// 	return (line);
// }
