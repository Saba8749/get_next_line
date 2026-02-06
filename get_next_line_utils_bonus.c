/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segribas <segribas@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 18:11:16 by saba              #+#    #+#             */
/*   Updated: 2026/02/06 21:08:24 by segribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	gnl_memcpy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}

size_t	gnl_strlen(char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	gnl_find_nl(const char *s, size_t stash_len)
{
	size_t	i;

	if (!s)
		return (-1);
	i = 0;
	while (i < stash_len)
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*gnl_strjoin(char *s1, char *s2, size_t len2)
{
	size_t	len1;
	char	*new;

	if (s2 == NULL || len2 == 0)
		return (s1);
	if (s1 == NULL)
		len1 = 0;
	else
		len1 = gnl_strlen(s1);
	new = malloc(len1 + len2 + 1);
	if (!new)
	{
		free(s1);
		return (NULL);
	}
	gnl_memcpy(new, s1, len1);
	gnl_memcpy(new + len1, s2, len2);
	new[len1 + len2] = '\0';
	free(s1);
	return (new);
}

char	*gnl_substr(char *s, size_t start, size_t len)
{
	size_t	s_len;
	size_t	out_len;
	char	*out;

	s_len = gnl_strlen(s);
	if (start >= s_len)
		out_len = 0;
	else
	{
		if (len > (s_len - start))
			out_len = s_len - start;
		else
			out_len = len;
	}
	out = malloc(out_len + 1);
	if (!out)
		return (NULL);
	if (out_len == 0)
		out[0] = '\0';
	else
		gnl_memcpy(out, s + start, out_len);
	out[out_len] = '\0';
	return (out);
}
