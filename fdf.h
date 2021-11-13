/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <aleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:52:30 by aleroy            #+#    #+#             */
/*   Updated: 2021/10/08 17:52:31 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// # include <mlx.h>
# include "mlx_linux/mlx.h"
// # include "mlx_linux/libmlx.a"
// # include "mlx_linux/libmlx_Linux.a"

# include <stdlib.h>
# include <X11/keysym.h>

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_info
{
	void	*id;
	void	*wd_ptr;
	t_img	img;
}				t_info;

#endif
