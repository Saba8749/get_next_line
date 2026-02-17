/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segribas <segribas@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:58:20 by saba              #+#    #+#             */
/*   Updated: 2026/02/17 15:48:05 by segribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
			free(stash);
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

static char	*update_stash(char *stash, int nl_pos)
{
	char	*new_stash;
	size_t	stash_len;
	size_t	rem_len;

	if (nl_pos == -1)
	{
		free(stash);
		return (NULL);
	}
	stash_len = gnl_strlen(stash);
	rem_len = stash_len - (nl_pos + 1);
	if (rem_len == 0)
	{
		free(stash);
		return (NULL);
	}
	new_stash = gnl_substr(stash, nl_pos + 1, rem_len);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*buffer;
	char		*line;
	int			nl_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	stash[fd] = read_to_stash(fd, stash[fd], buffer);
	if (!stash[fd])
		return (NULL);
	if (*stash[fd] == '\0')
	{
		free(stash[fd]);
		return (stash[fd] = NULL, NULL);
	}
	nl_pos = gnl_find_nl(stash[fd], gnl_strlen(stash[fd]));
	if (nl_pos != -1)
		line = gnl_substr(stash[fd], 0, nl_pos + 1);
	else
		line = gnl_substr(stash[fd], 0, gnl_strlen(stash[fd]));
	stash[fd] = update_stash(stash[fd], nl_pos);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// // test.c
// int main(void)
// {
//     int fd = open("test.txt", O_RDONLY);
//     char *line;

//     while ((line = get_next_line(fd)))
//     {
//         printf("%s", line);
//         free(line);
//     }
//     close(fd);
// }