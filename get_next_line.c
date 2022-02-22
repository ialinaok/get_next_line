/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:29:51 by ialinaok          #+#    #+#             */
/*   Updated: 2022/02/18 22:44:40 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <fcntl.h>
#include <stdio.h>

// char	*get_next_line(int fd)
// {
// 	static char buffer[BUFFER_SIZE + 1];
// 	char	*tmp;
// 	int	check;

// 	if (fd < 0)
// 		return NULL;
// 	tmp = malloc(sizeof(char));
// 	while (!ft_strchr(buffer, '\n'))
// 	{
// 		if (*buffer)
// 			join_line(&tmp, buffer);
// 		check = read(fd, buffer, BUFFER_SIZE);
// 		if (check <= 0 && !(*tmp))
// 		{
// 			free(tmp);
// 			return (NULL);
// 		}
// 		buffer[BUFFER_SIZE] = '\0';
// 		if (!ft_strchr(buffer, '\n') && check < BUFFER_SIZE)
// 		{
// 			free(tmp);
// 			return (NULL);
// 		}
// 	}
// 	join_line(&tmp, buffer);
// 	move_leftovers(buffer);
// 	return (tmp);
// }

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*tmp;
	int			check;

	buffer[BUFFER_SIZE] = '\0';
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tmp = malloc(sizeof(char));
	*tmp = '\0';
	if (buffer[0] != '\0') // that means there are leftovers
	{
		// printf("\nleftovers: %s", buffer);
		join_line(&tmp, buffer);
		// printf("\ntmp w leftovers: %s", tmp);
	}
	while (!ft_strchr(tmp, '\n'))
	{
		ft_bzero(buffer, BUFFER_SIZE);
		check = read(fd, buffer, BUFFER_SIZE);
		// printf("\n   read return: %d", check);
		if(check <= 0 && !*(tmp))
		{
			ft_bzero(buffer, BUFFER_SIZE);
			// printf("\n.....%s", buffer);
			free(tmp);
			return (NULL);
		}
		buffer[check] = '\0';
		// printf("\nbuffer in gnl: %s", buffer);
		
		join_line(&tmp, buffer);
		// move_leftovers(buffer);
		// printf("\ntmp in gnl: %s", tmp);
		if (check < BUFFER_SIZE && !ft_strchr(tmp, '\n'))
		{		
			// printf("\n......tmp in gnl: %s", tmp);
			ft_bzero(buffer, BUFFER_SIZE);
			// printf("\n=====%s", buffer);
			break;
		}
	}
	// move_leftovers(buffer);
	return (tmp);
}

void	join_line(char **tmp, char *buffer)
{
	char	*line;
	char	*find_nl;
	int		i;
	int		j;
	if(!*tmp || !buffer)
		return ;
	i = 0;
	j = 0;
	find_nl = ft_strchr(buffer, '\n');
	if (find_nl)
		line = malloc(ft_strlen(*tmp) + BUFFER_SIZE - ft_strlen(find_nl) + 1);
	else
		line = malloc(ft_strlen(*tmp) + BUFFER_SIZE + 1);
	if (!line)
		return ;
	while (tmp[0][j])
		line[i++] = tmp[0][j++];
	j = 0;
	while (buffer[j] != '\0' && buffer[j] != '\n')
		line[i++] = buffer[j++];
	if (buffer[j] == '\n')
	{
		line[i++] = buffer[j++];
		move_leftovers(buffer, ++find_nl);
		// printf("\nthis is findnl: %s", find_nl);
	}
	line[i] = '\0';
	free((void *)tmp[0]);
	// printf("\nline: %s", line);
	tmp[0] = line;
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
		buffer[i++] = '\0'; // it's not necessary, only one null is needed
}

// void	move_leftovers(char *buffer)
// {
// 	int	bufflen;
// 	int	linelen;
// 	int	leftovers;
// 	int	i;

// 	bufflen = ft_strlen(buffer);
// 	linelen = bufflen - ft_strlen(ft_strchr(buffer, '\n') + 1);
// 	leftovers = bufflen - linelen;
// 	i = 0;
// 	while (buffer[linelen])
// 		buffer[i++] = buffer[linelen++];
// 	ft_bzero(&buffer[leftovers], linelen);
// }

// void	join_line(char **tmp, char *buffer)
// {
// 	char	*line;
// 	char	*find_nl;
// 	int		i = 0;
// 	int		j = 0;
// 	// int		leftlen;

// 	if (!*tmp || !buffer) //I don't think it's necessary as we'll alwaysgive valid input
// 		return ;
// 	find_nl = ft_strchr(buffer, '\n');
// 	if (find_nl)
// 	{
// 		// leftlen = ft_strlen(find_nl);
// 		line = malloc(ft_strlen(*tmp) + BUFFER_SIZE - ft_strlen(find_nl) + 1);
// 		while (tmp[0][j])
// 			line[i++] = tmp[0][j++];
// 		j = 0;
// 		while (buffer[j] != '\n')
// 			line[i++] = buffer[j++];
// 		line[i++] = buffer[j];
// 		line[i] = '\0';
// 		free((void *)tmp[0]);
// 		tmp[0] = line;
// 			// printf("\nthis is buffer if nl before move: %s", buffer);
// 			// printf("\nthis is tmp if nl before move: %s", *tmp);
// 		// ft_memcpy(buffer, ++find_nl, leftlen);
// 			// printf("\nthis is buffer if nl after move: %s", buffer);
// 			// printf("\nthis is tmp if nl after move: %s", *tmp);
// 	}
// 	if (!find_nl)
// 	{
// 		line = malloc(ft_strlen(*tmp) + BUFFER_SIZE + 1);
// 		while (tmp[0][j])
// 			line[i++] = tmp[0][j++];
// 		j = 0;
// 		while (buffer[j] != '\0')
// 			line[i++] = buffer[j++];
// 		line[i] = '\0';
// 		free((void *)tmp[0]);
// 		tmp[0] = line;
// 	}
// }

// char	*get_next_line(int fd)
// {
// 	static char	buffer[BUFFER_SIZE + 1];
// 	char		*line;
// 	char		*tmp;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	tmp = malloc(sizeof(char));
// 	*tmp = '\0';
// 	if (buffer[0] != '\0') // that means there are leftovers
// 	{
// 		line = ft_strjoin(tmp, buffer);
// 		free(tmp);
// 		tmp = line;
// 		ft_bzero(buffer, BUFFER_SIZE);
// 	}
// 	line = read_buffers(fd, buffer, &tmp);
// 	printf("\nbuffer in gnl: %s", buffer);
// 	return (line);
// }

// void	read_buffers(int fd, char *buffer)
// {
// 	int		check;
// 	char	*find_nl;

// 	check = read(fd, buffer, BUFFER_SIZE);
// 	if (check == -1)
// 		return ;
// 	find_nl = ft_strchr(buffer);
// 	if (find_nl)
// 	{
		
// 	}
// }

// char	*read_buffers(int fd, char *buffer, char **tmp)
// {
// 	int		check;
// 	char	*find_n;
// 	int		leftovers = 0;
// 	char	*line;

// 	check = read(fd, buffer, BUFFER_SIZE);
// 	if (check == -1)
// 		return (NULL);
// 	// printf("\nthis is buffer 1: %s", buffer);
// 	// printf("\nthis is tmp 1: %s", *tmp);
// 	buffer[BUFFER_SIZE] = '\0';
// 	// while ()
// 	// {
// 		// find_n = 
// 		while (!ft_strchr(buffer, '\n')) // that means, if there is no newline in current buffer
// 		{

// 			line = ft_strjoin(*tmp, buffer);
// 			free(*tmp);
// 			*tmp = line;
// 			ft_bzero(buffer, BUFFER_SIZE);
// 			check = read(fd, buffer, BUFFER_SIZE);
// 			if(check == - 1)
// 				return NULL;
// 			buffer[BUFFER_SIZE] = '\0';
// 			find_n = ft_strchr(buffer, '\n');
// 			// printf("\nthis is buffer: %s", buffer);
// 			// printf("\nthis is tmp: %s", *tmp);
// 		}
// 		if (ft_strchr(buffer, '\n')) // so when I DO find a newline character //tmp has a current line of joined buffers
// 		{
// 			line = full_line(*tmp, buffer);
// 			// printf("\nthis is line: %s", line);
// 			find_n++;
// 			printf("\nthis is buffer if nl before move: %s", buffer);
// 			printf("\nthis is tmp if nl before move: %s", *tmp);
// 			int i = 0;
// 			while (buffer[i] != '\n')
// 				i++;
// 			leftovers = BUFFER_SIZE - i;
// 			ft_memcpy(buffer, find_n, leftovers);
// 			printf("\nthis is buffer if nl after move: %s", buffer);
// 			printf("\nthis is tmp if nl after move: %s", *tmp);
// 			return (line);
// 		}
// 	// }
// 	return (line);
// }

// char	*full_line(char *tmp, char *buffer)
// {
// 	int	i;
// 	int	j;
// 	char	*line;
// 	char	*saveline;

// 	i = 0;
// 	while (buffer[i] != '\n')
// 		i++;
// 	line = (char *) malloc(ft_strlen(tmp) + i + 1);
// 	saveline = line;
// 	// line now points to a newline space, which is not filled yet
// 	while (*tmp)
// 		*line++ = *tmp++;
// 	j = 0;
// 	// I want to copy till \n and \n itself too, so i + 1 bytes
// 	while (j <= i)
// 	{
// 		*line++ = buffer[j];
// 		j++;
// 	}
// 	*line = '\0';
// 	// free(tmp);
// 	return (saveline);
// }

// int	main(void)
// {
// 	int	fd = 0;
// 	char	*linea;
// 	char	*lineb;
// 	char	*linec;
// 	char	*lined;

// 	fd = open("test.txt", O_RDONLY);
// 	linea = get_next_line(fd);
// 	printf("\nthis is line a: %s", linea);
// 	lineb = get_next_line(fd);
// 	printf("\nthis is line b: %s", lineb);
// 	linec = get_next_line(fd);
// 	printf("\nthis is line c: %s", linec);
// 	lined = get_next_line(fd);
// }

///code graveyard

// char	*join_line(char **tmp, char *buffer)
// {
// 	char	*line;
// 	char	*find_nl;

// 	if (!*tmp || !buffer)
// 		return ;
// 	find_nl = ft_strchr(buffer, '\n');
// 	if (find_nl)
// 	{
// 		line = malloc(ft_strlen(*tmp) + BUFFER_SIZE - ft_strlen(find_nl) + 1);
// 		while (**tmp)
// 			*line++ = **tmp++;
// 		while (*buffer != '\n')
// 			*line++ = *buffer++;
// 		*line++ = *buffer++;
// 		*line = '\0';
// 	}
// 	else
// 	{
// 		line = malloc(ft_strlen(*tmp) + BUFFER_SIZE + 1);
// 		while (**tmp)
// 			*line++ = **tmp++;
// 		*line = '\0';
// 	}
// 	return (line);
// }

// void	join_line(char **tmp, char *buffer)
// {
// 	char	*line;
// 	int		i;
// 	int		nl_index;

// 	if (!*tmp || !buffer)
// 		return;
// 	i = 0;
// 	nl_index = -1;
// 	while (buffer[i]) // here I'm just searching for newline index
// 	{
// 		if (buffer[i] == '\n')
// 		{
// 			nl_index = i;
// 			break;
// 		}
// 		i++;
// 	}
// 	if (nl_index != -1)
// 	{
// 		line = malloc(ft_strlen(*tmp) + nl_index + 1);


// 	}
// 	else
// 	{

// 	}
// }

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
