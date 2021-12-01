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

#define WINDOW_WIDTH 600//1920
#define WINDOW_HEIGHT 300//1080

// make drawer √
// create/push image to window √
// bresenham (add color?)
// point placer

// function isoTo2D(pt:Point):Point{
//   var tempPt:Point = new Point(0, 0);
//   tempPt.x = (2 * pt.y + pt.x) / 2;
//   tempPt.y = (2 * pt.y - pt.x) / 2;
//   return(tempPt);
// }

// function twoDToIso(pt:Point):Point{
//   var tempPt:Point = new Point(0,0);
//   tempPt.x = pt.x - pt.y;
//   tempPt.y = (pt.x + pt.y) / 2;
//   return(tempPt);
// }

void	place_point(t_img *img, t_coor coor)
{
	int	x;
	int	y;

	x = coor.x1;
	y = coor.y1;
	coor.x1 = x - y;
	coor.y1 = (x + y) / 2;
	img_pix_put(img , coor.x1, coor.y1, coor.color);
}

void	place_point2(t_img *img, int coorx, int coory, int color)
{
	int	x;
	int	y;

	x = coorx;
	y = coory;
	coorx = x - y;
	coory = (x + y) / 2;
	img_pix_put(img , coorx, coory, color);
}

// The pseudocode for the loop then looks like this:

// for(i, loop through rows)
//   for(j, loop through columns)
//     x = j * tile width
//     y = i * tile height
//     tileType = levelData[i][j]
//     placetile(tileType, twoDToIso(new Point(x, y)))

void bresenham2(t_img *img, t_coor *coor)
{
	int x;
	int y;
	int m_new = 2 * (coor->x1 - coor->xold);//original slope?
	int slope_error_new = m_new - (coor->y1 - coor->yold);

	x = coor->xold;
	y = coor->yold;
	// coor->color = 0xff0000;//= red
	while (y <= coor->y1)
	{
		// img_pix_put(img, x, y, coor->color);
		place_point2(img, x, y, coor->color);
	  // cout << "(" << x << "," << y << ")\n";

	  // Add slope to increment angle formed
	  slope_error_new += m_new;

	  // Slope error reached limit, time to
	  // increment y and update slope error.
		if (slope_error_new >= 0)
		{
			x++;
			slope_error_new  -= 2 * (coor->y1 - coor->yold);
		}
		y++;
	}
	// coor->color = 0xffffff;
}

void bresenham(t_img *img, t_coor *coor)
{
	int x;
	int y;
	int m_new = 2 * (coor->y1 - coor->yold);//original slope?
	int slope_error_new = m_new - (coor->x1 - coor->xold);

	x = coor->xold;
	y = coor->yold;
	// coor->color = 0xff0000;//= red
	while (x <= coor->x1)
	{
		// img_pix_put(img, x, y, coor->color);
		place_point2(img, x, y, coor->color);
	  // cout << "(" << x << "," << y << ")\n";

	  // Add slope to increment angle formed
	  slope_error_new += m_new;

	  // Slope error reached limit, time to
	  // increment y and update slope error.
		if (slope_error_new >= 0)
		{
			y++;
			slope_error_new  -= 2 * (coor->x1 - coor->xold);
		}
		x++;
	}
	// coor->color = 0xffffff;
}

// void bresenham(t_img *img, t_coor *coor)
// {
// 	int x;
// 	int y;
// 	int m_new = 2 * (coor->y1 - coor->yold);//original slope?
// 	int slope_error_new = m_new - (coor->x1 - coor->xold);

// 	x = coor->xold;
// 	y = coor->yold;
// 	coor->color = 0xff0000;//= red
// 	while (x <= coor->x1)
// 	{
// 		img_pix_put(img, x, y, coor->color);
// 	  // cout << "(" << x << "," << y << ")\n";

// 	  // Add slope to increment angle formed
// 	  slope_error_new += m_new;

// 	  // Slope error reached limit, time to
// 	  // increment y and update slope error.
// 		if (slope_error_new >= 0)
// 		{
// 			y++;
// 			slope_error_new  -= 2 * (coor->x1 - coor->xold);
// 		}
// 		x++;
// 	}
// 	coor->color = 0xffffff;
// }

void	clear_background(t_img *img, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < WINDOW_HEIGHT)
	{
		i = 0;
		while (i < WINDOW_WIDTH)
		{
			img_pix_put(img, i, j, color);
			i++;
		}
		// color++;
		j++;
	}
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	get_coor(t_coor *coor, char *line, int i, int *z)
{
	while (line[i] == ' ' && line[i])
		i++;
	if (!((line[i] == '-' || line[i] == '+' || (line[i] >= '0'
		&& line[i] <= '9')) && line[i]))
		return (-1);
	// coor->z1 = ft_atoi(&line[i]);
	*z = ft_atoi(&line[i]);
	while ((line[i] == '-' || line[i] == '+') && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9' && line[i])
		i++;
	while ((line[i] == ',' || line[i] == ' ' || line[i] == '\n') && line[i])
		i++;
	coor->color = 0xffffff;//white #define WHITE_PIXEL 0xffffff
	return (i);
}

void	connect_point(t_img *img, t_coor *coor, char *line)
{
	int	i;
	int	temp;
	int temp2;
	int	count;

	i = 0;
	count = 0;
	coor->color = 0xff0000;//= red
	temp = coor->yold;
	temp2 = coor->zold;
	coor->yold = coor->y1;
	while (line[i])
	{
		i = get_coor(coor, line, i, &coor->z1);
		coor->zold = coor->z1;
		coor->xold = coor->x1;
		coor->x1 = coor->x1 + 15;
		if (count == 0)
			i = get_coor(coor, line, i, &coor->z1);
		count = 1;
		// printf("x1 = %d, y1 = %d, z1 = %d\n", coor->x1, coor->y1, coor->z1);
		// printf("xold = %d, yold = %d, zold = %d\n", coor->xold, coor->yold, coor->zold);
		coor->color = 0xff0000;//red
		bresenham(img, coor);
	}
	coor->yold = temp;
	coor->zold = temp2;
}

void	connect_lines(t_img *img, t_coor *coor, char *line, char *line2)// de line2 vers line
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && line2[j])
	{
		j = get_coor(coor, line2, j, &coor->zold);
		i = get_coor(coor, line, i, &coor->z1);
		coor->xold = coor->x1;
		// printf("x1 = %d, y1 = %d, z1 = %d\n", coor->x1, coor->y1, coor->z1);
		// printf("xold = %d, yold = %d, zold = %d\n", coor->xold, coor->yold, coor->zold);
		coor->color = 0x9b30ff;//purple
		bresenham2(img, coor);
		coor->x1 = coor->x1 + 15;
	}
}

int	render(t_info *info, char *line, int fd) //need to handle /n in line
{
	char	*line2;
	t_coor coor;
	int i;

	i = 0;
	line2 = NULL;
	coor.x1 = WINDOW_WIDTH / 3;
	coor.y1 = 0;//(coor.x1 + coor.y1) / 2
	coor.z1 = 0;
	coor.xold = 0;
	coor.yold = 0;
	coor.zold = 0;
	// coor.color = 0xff0000;//= red
	// if (info->wd_ptr == NULL)
	// 	return (1);
	clear_background(&info->img, 0x0);//black #define BLACK_PIXEL 0x0 (purple = 0x9b30ff)
	while (line)
	{
		i = 0;
		while (line[i])
		{
			i = get_coor(&coor, line, i, &coor.z1);
			if (i == -1)
				return (-1);
			place_point(&info->img, coor);
			// img_pix_put(&info->img , coor.x1, coor.y1, coor.color);
			printf("render z = %d\n", coor.z1);
			// coor.x1 = row * 6;
			coor.x1 = coor.x1 + 15;
		}
		coor.x1 = WINDOW_WIDTH / 3;
		connect_point(&info->img, &coor, line);//axe x
		if (line2 != NULL)
			free(line2);
		line2 = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		if (line2 == NULL)
			return (-1);
		if (line == NULL)
		{
			// free(line);
			break;//return (-1);?
		}

		coor.yold = coor.y1;
		coor.y1 = coor.y1 + 15;
		coor.x1 = WINDOW_WIDTH / 3;
		connect_lines(&info->img, &coor, line, line2);//axe y
		coor.x1 = WINDOW_WIDTH / 3;
		// coor.y1 = col * 4;
		// if (col == 1)
		// 	coor.color = 0x00ff00;
		// else if (col == 2)
		// 	coor.color = 0x0000ff;
	}


	mlx_put_image_to_window(info->id, info->wd_ptr, info->img.img_ptr, 0, 0);
	if (line2 != NULL)
			free(line2);

	return (0);
}

int	handle_event(int key_sym, t_info *info)
{
	if (key_sym == XK_Escape)
	{
		mlx_destroy_window(info->id, info->wd_ptr);
		info->wd_ptr = NULL;
	}
	return (0);
}

int	handle_no_event()
{
	return (0);
}

int	destroyer(t_info *info, char *line)
{
	if (line != NULL)
		free(line);
	mlx_destroy_image(info->id, info->img.img_ptr);
	mlx_destroy_display(info->id);
	free(info->id);
	free(info->wd_ptr);
	return (-1);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int fd;
	char *line;

	if (argc != 2)
	{
		printf("error argc\n");
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
	{
		printf("error line\n");
		return (-1);
	}

	info.id = mlx_init();
	if (info.id == NULL)
	{
		printf("error id\n");
		return (-1);
	}
	

	// read_map(info);//get width/hight

	info.wd_ptr = mlx_new_window(info.id , WINDOW_WIDTH, WINDOW_HEIGHT, "fdf" ); //int size_x, int size_y 1920x1080
	if (info.wd_ptr == NULL)
	{
		printf("error wd_ptr\n");
		return (-1);
	}
	// mlx_clear_window(info.id, info.wd_ptr);

	info.img.img_ptr = mlx_new_image(info.id, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (info.img.img_ptr == NULL)
	{
		printf("error img_ptr\n");
		return (-1);
	}
	info.img.addr = mlx_get_data_addr(info.img.img_ptr, &info.img.bpp, &info.img.line_len, &info.img.endian);
	if (render(&info, line, fd) == -1)
	{
		printf("error render\n");
		return (destroyer(&info, line));
	}

	// mlx_loop_hook(info.id, &render, &info);
	mlx_loop_hook(info.id, &handle_no_event, &info);
	mlx_key_hook(info.wd_ptr, &handle_event, &info);

	mlx_loop(info.id);

	// mlx_destroy_image(info.id, info.img.img_ptr);
	// mlx_destroy_display(info.id);
	// free(info.id);
	// free(info.wd_ptr);
	destroyer(&info, line);
	// free(info);
	return (0);
}
