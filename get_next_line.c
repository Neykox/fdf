/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <aleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:47:33 by aleroy            #+#    #+#             */
/*   Updated: 2020/12/07 17:47:35 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2, int i, int c)
{
	char	*ret;
	int		size;

	size = ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1;
	ret = malloc(sizeof(char) * size);
	if (ret == NULL)
		return (NULL);
	while (s1[c])
	{
		ret[i] = s1[c];
		i++;
		c++;
	}
	c = 0;
	while (s2[c])
	{
		ret[i] = s2[c];
		i++;
		c++;
	}
	ret[i] = '\0';
	free(s1);
	return (ret);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*copie;
	char	*str;
	int		i;

	i = 0;
	str = (char *)s1;
	copie = malloc((ft_strlen(str) + 10) * sizeof(char));
	if (copie == NULL)
		return (NULL);
	while (str[i] && str[i] != '\n')
	{
		copie[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		copie[i] = str[i];
		i++;
	}
	copie[i] = '\0';
	return (copie);
}

int	modif_buf_gnl(char *buf)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	j = 0;
	n = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
	{
		n = 1;
		i++;
	}
	while (buf[i])
	{
		buf[j] = buf[i];
		j++;
		i++;
	}
	buf[j] = '\0';
	return (n);
}

char	*gnl2(char *line, char *buf)
{
	char	*line2;

	line2 = ft_strdup_gnl(buf);
	if (line2 == NULL)
		return (NULL);
	if (line == NULL)
		return (line2);
	line = ft_strjoin_gnl(line, line2, 0, 0);
	free (line2);
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	int			ret;
	static char	buf[4096][BUFFER_SIZE + 1];
	char		*line;
	int			test;

	test = 0;
	line = NULL;
	ret = 1;
	if (fd > 4096 || fd <= -1)
		return (NULL);
	while (test != 1)
	{
		if (buf[fd][0] == '\0')
		{
			ret = read(fd, buf[fd], BUFFER_SIZE);
			buf[fd][ret] = '\0';
		}
		if (ret == 0 && line != NULL)
			return (line);
		if (ret == -1 || ret == 0)
			return (NULL);
		line = gnl2(line, buf[fd]);
		test = modif_buf_gnl(buf[fd]);
	}
	return (line);
}
