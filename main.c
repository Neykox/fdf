/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <aleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 17:52:15 by aleroy            #+#    #+#             */
/*   Updated: 2021/10/08 17:52:18 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int	event(t_info *info)
// {}

int	main()
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (info == NULL)
		return (-1);
	info->id = mlx_init();
	if (info->id == NULL)
		return (-1);

	info->wd_ptr = mlx_new_window(info->id , 10, 10, "fdf" ); //int size_x, int size_y
	if (info->wd_ptr == NULL)
		return (-1);
	// mlx_clear_window(info->id, info->wd_ptr); //put window in black

	// if (event(info) == 1)
		// mlx_destroy_window(info->id, info->wd_ptr);
	free(info);
	return (0);
}
