/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segribas <segribas@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:59:42 by saba              #+#    #+#             */
/*   Updated: 2026/02/18 17:07:26 by segribas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
size_t	gnl_strlen(char *s);
int		gnl_find_nl(const char *s, size_t stash_len);
char	*gnl_strjoin(char *s1, char *s2, size_t len2);
char	*gnl_substr(char *s, size_t start, size_t len);

#endif
