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

# define WINDOW_WIDTH 600
# define WINDOW_HEIGHT 300
#define MLX_ERROR 1

int main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (MLX_ERROR);
	win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "My first window!");
	if (win_ptr == NULL)
	{
		free(win_ptr);
		return (MLX_ERROR);
	}
	while (1)
		;
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
}

// int	main()
// {
// 	void	*id;
// 	void	*wd_ptr;
	
// 	id = mlx_init();
// 	if (id == NULL)
// 		return (-1);

// 	// read_map(info);//get width/hight

// 	wd_ptr = mlx_new_window(id , 600, 300, "fdf" ); //int size_x, int size_y
// 	if (wd_ptr == NULL)
// 		return (-1);
// 	mlx_clear_window(id, wd_ptr); //put window in black

// 	while (1)
// 		;

// 	// if (event(info) == 1)
// 		mlx_destroy_window(id, wd_ptr);
// 		mlx_destroy_display(id);
// 	free(id);
// 	free(wd_ptr);
// 	return (0);
// }

// int	main()
// {
// 	// void	*id;
// 	// void	*wd_ptr;
// 	t_info	*info;

// 	info = malloc(sizeof(t_info));
// 	if (info == NULL)
// 		return (-1);
// 	info->id = mlx_init();
// 	if (info->id == NULL)
// 		return (-1);

// 	// read_map(info);//get width/hight

// 	info->wd_ptr = mlx_new_window(info->id , 600, 300, "fdf" ); //int size_x, int size_y
// 	if (info->wd_ptr == NULL)
// 		return (-1);
// 	mlx_clear_window(info->id, info->wd_ptr); //put window in black

// 	while (1)
// 		;

// 	// if (event(info) == 1)
// 		mlx_destroy_window(info->id, info->wd_ptr);
// 		mlx_destroy_display(info->id);
// 	free(info->id);
// 	free(info->wd_ptr);
// 	free(info);
// 	return (0);
// }
