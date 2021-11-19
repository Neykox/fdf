/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <aleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:48:04 by aleroy            #+#    #+#             */
/*   Updated: 2020/12/07 17:48:06 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>

int		ft_strlen(char *str);

char	*ft_strjoin_gnl(char *s1, char *s2, int i, int c);
char	*ft_strdup_gnl(const char *s1);
int		modif_buf_gnl(char *buf);
char	*gnl2(char *line, char *buf);
char	*get_next_line(int fd);

#endif
