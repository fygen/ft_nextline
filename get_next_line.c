/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayegen <ayegen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 19:47:12 by ayegen            #+#    #+#             */
/*   Updated: 2024/02/20 21:08:39 by ayegen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int file_descriptor, char *current_content)
{
	char	*buffer;
	int		reader;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	reader = 1;
	while (!ft_strchr(current_content, '\n') && reader != 0)
	{
		reader = read(file_descriptor, buffer, BUFFER_SIZE);
		if (reader == -1)
		{
			free(buffer);
			free(current_content);
			return (NULL);
		}
		buffer[reader] = '\0';
		current_content = ft_strjoin(current_content, buffer);
	}
	free(buffer);
	return (current_content);
}

char	*get_line(char *input)
{
	char	*line;
	int		i;

	i = 0;
	if (!input[i])
		return (NULL);
	while (input[i] != '\n' && input[i] != '\0')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (input[i] != '\n' && input[i] != '\0')
	{
		line[i] = input[i];
		i++;
	}
	if (input[i] == '\n')
	{
		line[i] = input[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_part(char *input)
{
	char	*remaining_content;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i] != '\n' && input[i] != '\0')
		i++;
	if (!input[i])
	{
		free(input);
		return (NULL);
	}
	remaining_content = (char *)malloc(sizeof(char) * (ft_strlen(input) - i));
	if (!remaining_content)
		return (NULL);
	i++;
	while (input[i + j] != '\0')
	{
		remaining_content[j] = input[j + i];
		j++;
	}
	remaining_content[j] = '\0';
	free(input);
	return (remaining_content);
}

char	*get_next_line(int file_descriptor)
{
	static char	*current_content;
	char		*line;

	if (file_descriptor < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current_content = read_line(file_descriptor, current_content);
	if (!current_content)
	{
		free(current_content);
		return (NULL);
	}
	line = get_line(current_content);
	current_content = get_next_part(current_content);
	return (line);
}
