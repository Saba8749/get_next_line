/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segribas <segribas@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:58:20 by saba              #+#    #+#             */
/*   Updated: 2026/01/29 18:53:34 by segribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	static char *stash;
	char		*buffer;
	int			bytes_read;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	bytes_read = 1;
	
	while(bytes_read > 0 && gnl_find_nl(stash, gnl_strlen(stash))== -1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		
		if(bytes_read == -1)
		{
			free(buffer);
			return(NULL);
		}
		if(bytes_read == 0)
		break;
		if(bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			stash = gnl_strjoin(stash, buffer, bytes_read);
			if(!stash)
			{
				free(buffer);
				return(NULL);
			}
		}
	}
	
}
