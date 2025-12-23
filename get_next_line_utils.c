/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saba <saba@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:11:16 by saba              #+#    #+#             */
/*   Updated: 2025/12/23 20:00:01 by saba             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t gnl_strlen(char *s)
{
	size_t len;
	
	if (!s)
		return(0);
	len = 0;
	while(s[len])
		len++;
	return(len);
}
int gnl_find_nl(const char *s, size_t stash_len)
{
	size_t i;
	if (!s)
		return (-1);
	i = 0;
	while(i < stash_len)
	{
		if(s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

