/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segribas <segribas@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:58:20 by saba              #+#    #+#             */
/*   Updated: 2026/02/18 16:39:50 by segribas         ###   ########.fr       */
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
	static char	*stash;
	char		*buffer;
	char		*line;
	int			nl_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	stash = read_to_stash(fd, stash, buffer);
	if (!stash)
		return (NULL);
	if (*stash == '\0')
	{
		free(stash);
		return (stash = NULL, NULL);
	}
	nl_pos = gnl_find_nl(stash, gnl_strlen(stash));
	if (nl_pos != -1)
		line = gnl_substr(stash, 0, nl_pos + 1);
	else
		line = gnl_substr(stash, 0, gnl_strlen(stash));
	stash = update_stash(stash, nl_pos);
	return (line);
}

// // test.c
// #include "get_next_line.h"
// #include <fcntl.h>
// #include <stdio.h>

// int main(void)
// {
//     int fd = open("test.txt", O_RDONLY);
// 	// int fd = 0;
//     char *line;

//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }
//     close(fd);
//     return (0);
// }
