/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segribas <segribas@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:58:20 by saba              #+#    #+#             */
/*   Updated: 2026/01/30 20:09:49 by segribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *stash, char *buffer)
{
	int	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && gnl_find_nl(stash, gnl_strlen(stash)) == -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = gnl_strjoin(stash, buffer, bytes_read);
		if (!stash)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	char 		*line;
	int			nl_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	stash = read_to_stash(fd, stash, buffer);
	if (!stash || *stash == '\0')
		return (NULL);
	nl_pos = gnl_find_nl(stash, gnl_strlen(stash));

	if (nl_pos != -1)
	{
		line = gnl_substr(stash, 0, nl_pos + 1);
	}
	else
	{
		line = gnl_substr(stash, 0, gnl_strlen(stash));
	}
}

