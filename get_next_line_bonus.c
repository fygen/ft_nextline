/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayegen <ayegen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:47:12 by ayegen            #+#    #+#             */
/*   Updated: 2024/02/20 21:07:47 by ayegen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*readline(int fd, char	*readone)
{
	char	*buff;
	int		reader;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	reader = 1;
	while (!ft_strchr(readone, '\n') && reader != 0)
	{
		reader = read(fd, buff, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buff);
			free(readone);
			return (NULL);
		}
		buff[reader] = '\0';
		readone = ft_strjoin(readone, buff);
	}
	free(buff);
	return (readone);
}

char	*putline(char *readone)
{
	char	*str;
	int		i;

	i = 0;
	if (!readone[i])
		return (NULL);
	while (readone[i] != '\n' && readone[i] != '\0')
		i++;
	str = (char *)malloc(sizeof(char) * i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (readone[i] != '\n' && readone[i] != '\0')
	{
		str[i] = readone[i];
		i++;
	}
	if (readone[i] == '\n')
	{
		str[i] = readone[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*nxtline(char *readone)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (readone[i] != '\n' && readone[i] != '\0')
		i++;
	if (!readone[i])
	{
		free(readone);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(readone) - i));
	if (!str)
		return (NULL);
	i++;
	while (readone[i + j] != '\0')
	{
		str[j] = readone[j + i];
		j++;
	}
	str[j] = '\0';
	free(readone);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*readone[10240];
	char		*arr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readone[fd] = readline(fd, readone[fd]);
	if (!readone[fd])
		return (NULL);
	arr = putline(readone[fd]);
	readone[fd] = nxtline(readone[fd]);
	return (arr);
}
