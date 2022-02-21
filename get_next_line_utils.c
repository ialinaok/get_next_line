/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apielasz <apielasz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:42:46 by ialinaok          #+#    #+#             */
/*   Updated: 2022/02/18 22:45:41 by apielasz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

size_t	ft_strlen(char const *s)
{
	size_t	n;

	n = 0;
	while (s[n])
		n++;
	return (n);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	char	*ptr;

	if (!s1 || !s2)
		return (NULL);
	newstr = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!newstr)
		return (NULL);
	ptr = newstr;
	while (*s1)
		*newstr++ = *s1++;
	while (*s2)
		*newstr++ = *s2++;
	*newstr = '\0';
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*put;

	put = s;
	while (n > 0)
	{
		*put++ = '\0';
		n--;
	}
}

char	*ft_strchr(char const *str, int c)
{
	char	*ptr;

	ptr = (char *) str;
	while (*ptr)
	{
		if (*ptr == c)
			return (ptr);
		ptr++;
	}
	if (*ptr == c) // this is in case c == '\0', it's not needed for gnl but whatever
		return (ptr);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*put_dest;
	const char		*put_src;

	put_dest = dest;
	put_src = src;
	while (n > 0 && (dest != NULL || src != NULL))
	{
		// printf("\nfrom memcpy dst: %s", put_dest);
		// printf("\nfrom memcpy src: %s", put_src);
		*put_dest++ = *put_src++;
		n--;
	}
	return (dest);
}
