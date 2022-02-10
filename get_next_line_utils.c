/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialinaok <ialinaok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:42:46 by ialinaok          #+#    #+#             */
/*   Updated: 2022/02/11 00:15:21 by ialinaok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

size_t  ft_strlen(char const *s)
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
	while (*s2 != )
		*newstr++ = *s2++;
	*newstr = '\0';
	return (ptr);
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

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	size_t	src_len;
	int		n;

	src_len = ft_strlen(src);
	n = src_len;
	if (src_len + 1 < dst_size)
	{
		while ((n + 1) != 0)
		{
			*dst++ = *src++;
			n--;
		}
	}
	if ((src_len >= dst_size) && (dst_size != 0))
	{
		while ((dst_size - 1) != 0)
		{
			*dst++ = *src++;
			dst_size--;
		}
		dst[dst_size - 1] = '\0';
	}
	return (src_len);
}