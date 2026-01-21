/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saba <saba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:58:20 by saba              #+#    #+#             */
/*   Updated: 2025/12/24 18:13:34 by saba             ###   ########.fr       */
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
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	
	
}
