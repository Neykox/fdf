/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:58:23 by user42            #+#    #+#             */
/*   Updated: 2021/12/16 15:58:26 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf2.h"

// void	isometric(float *x, float *y, int z)
// {
// 	float pre_x;
// 	float pre_y;

// 	pre_x = *x;
// 	pre_y = *y;
// 	// *x = pre_x - pre_y;
// 	// *y = (pre_x + pre_y) / 2;
// 	*x = (pre_x - pre_y) * cos(0.8);//cos(30)
// 	*y = (pre_x + pre_y) * sin(0.8) - z;//sin(30)
// 	http://www.gandraxa.com/isometric_projection.xml
// }

// void	iso_coor2(float *coorx, float *coory, int z)
// {
// 	float	x;
// 	float	y;

// 	x = *coorx;
// 	y = *coory;
// 	//send iso or 2d coor?
// 	// *coorx = (x - y) * cos(0.8);//cos(30)
// 	// *coory = (x + y) * sin(0.8) - z;//sin(30)
// 	*coorx = x * cos(0.4636 * -1) - y * sin(1.1071 * -1);
// 	*coory = x * sin(0.4636 * -1) + y * cos(1.1071 * -1) - z;
// }

// void	iso_coor2(float x, float y, float *coorx, float *coory, int z)
// {
// 	//send iso or 2d coor?
// 	*coorx = x * cos(0.4636 * -1) - y * sin(1.1071 * -1);
// 	*coory = x * sin(0.4636 * -1) + y * cos(1.1071 * -1) - z;
// }

void	iso_coor2(int x, int y, int *coorx, int *coory, int z)
{
	//send iso or 2d coor?
	*coorx = x * cos(0.4636 * -1) - y * sin(1.1071 * -1);
	// printf("coorx = %d\n", *coorx);
	*coory = x * sin(0.4636 * -1) + y * cos(1.1071 * -1) - z;
	// printf("coory = %d\n", *coory);
}

// void	iso_coor(int x, int y, int *coorx, int *coory, int z)// z / 2     check  for z's sign
// {
// 	//modify 2d y like 2d x?
// 	// *coorx = (x - z) / sqrt(2);
// 	// *coory = (x + 2 * y + z) / sqrt(6);

// 	y = y - z;
// 	*coorx = x - y;
// 	*coory = (x + y) / 2;
// 	// z++;

// 	//send iso or 2d coor?
// 	// *coorx = (x - y) * cos(0.8);//cos(30)
// 	// *coory = (x + y) * sin(0.8) - z;//sin(30)
// 	// *coorx = x * cos(0.4636 * -1) - y * sin(1.1071 * -1);
// 	// *coory = x * sin(0.4636 * -1) + y * cos(1.1071 * -1) - z;
// }

// void	place_point3(t_img *img, int coorx, int coory, int color)
// {
// 	img_pix_put(img , coorx, coory, color);
// }

void	clear_background(t_info *info, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < info->wd_height)
	{
		i = 0;
		while (i < info->wd_width)
		{
			img_pix_put(&info->img, i, j, color);
			i++;
		}
		j++;
	}
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	// if (*(int *)pixel == 0xff0000 || *(int *)pixel == 0x00ff00)
	// {
	// 	color = 0xffffff;
	// }
	// else if (*(int *)pixel == 0x0000ff)
	// {
	// 	color = 0xffa500;
	// }
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
	*z = ft_atoi(&line[i]) * coor->tile_size;
	while ((line[i] == '-' || line[i] == '+') && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9' && line[i])
		i++;
	while ((line[i] == ',' || line[i] == ' ' || line[i] == '\n') && line[i])
		i++;
	coor->color = 0xffffff;//white #define WHITE_PIXEL 0xffffff
	return (i);
}

void	connect_point(t_info *info, t_coor *coor, char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	coor->color = 0xff0000;//= red
	coor->_2dyold = coor->_2dy1;
	while (line[i])
	{
		if (count == 1)
			coor->zold = coor->z1;
		i = get_coor(coor, line, i, &coor->z1);
		if (count == 0)
			coor->zold = coor->z1;

		coor->_2dxold = coor->_2dx1;
		coor->_2dx1 = coor->_2dx1 + info->tile_size;
		if (count == 0)
			i = get_coor(coor, line, i, &coor->z1);
		count = 1;

		if (coor->z1 != 0 || coor->zold != 0)
			coor->color = 0x00ff00;//green
		else
			coor->color = 0xff0000;//red

		iso_coor2(coor->_2dx1, coor->_2dy1, &coor->x1, &coor->y1, coor->z1);
		iso_coor2(coor->_2dxold, coor->_2dyold, &coor->xold, &coor->yold, coor->zold);
		// img_pix_put(&info->img, coor->x1, coor->y1, coor->color);
		// img_pix_put(&info->img, coor->xold, coor->yold, coor->color);
		// bresenham3(&info->img, coor);
		bresenham_new(&info->img, coor);
	}
}

void	connect_lines(t_info *info, t_coor *coor, char *line, char *line2)// de line2 vers line
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && line2[j])
	{
		j = get_coor(coor, line, j, &coor->zold);
		i = get_coor(coor, line2, i, &coor->z1);
		coor->_2dxold = coor->_2dx1;

		if (coor->z1 != 0 || coor->zold != 0)
			coor->color = 0x00ff00;//green
		else
			coor->color = 0x0000ff;//0x9b30ff;//purple

		iso_coor2(coor->_2dx1, coor->_2dy1, &coor->x1, &coor->y1, coor->z1);
		iso_coor2(coor->_2dxold, coor->_2dyold, &coor->xold, &coor->yold, coor->zold);
		// img_pix_put(&info->img, coor->x1, coor->y1, 0x0000ff);
		// img_pix_put(&info->img, coor->xold, coor->yold, 0x9b30ff);
		bresenham_new(&info->img, coor);

		coor->_2dx1 = coor->_2dx1 + info->tile_size;
	}
}

int	render(t_info *info, char **line) //need to handle /n in line
{
	t_coor coor;
	int i;
	int start = info->wd_height / 2;//int isox = (Width / 2) - (tileLength / 2) + x - y;
	info->tile_size = 10;
	

	// xC = ScreenWidth / 2
	// yC = ScreenHeight / 2

	i = 0;
	coor.tile_size = info->tile_size;
	coor.x1 = 0;
	coor.y1 = 0;//(coor.x1 + coor.y1) / 2
	coor.z1 = 0;
	coor.xold = 0;
	coor.yold = 0;
	coor.zold = 0;
	coor._2dx1 = start;
	coor._2dy1 = info->wd_width;
	coor._2dxold = 0;
	coor._2dyold = 0;
	clear_background(info, 0x0);

	while (line[i])
	{
		connect_point(info, &coor, line[i]);//axe x
		i++;
		if (line[i] == NULL)
			break;//return (-1);?

		coor._2dyold = coor._2dy1;
		coor._2dy1 = coor._2dy1 + info->tile_size;
		coor._2dx1 = start;
		connect_lines(info, &coor, line[i - 1], line[i]);//axe y//inverse i et i - 1
		coor._2dx1 = start;
	}


	mlx_put_image_to_window(info->id, info->wd_ptr, info->img.img_ptr, 0, 0);
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

int	destroyer(t_info *info, char **line)
{
	int	i;

	i = 0;
	while (line && line[i] != NULL)
	{
		free(line[i]);
		i++;
	}
	if (line != NULL)
		free(line);
	mlx_destroy_image(info->id, info->img.img_ptr);
	mlx_destroy_display(info->id);
	free(info->id);
	free(info->wd_ptr);
	return (-1);
}

char	**prep_line(int fd, char *buf)
{
	char *line;
	char *tmp;

	line = NULL;
	tmp = NULL;
	if (buf == NULL)
		return (NULL);
	// printf("buf = %s",buf);
	while (buf != NULL)
	{
		if (line == NULL)
			tmp = ft_strdup(buf);
		else
			tmp = ft_strjoin(line, buf);
		// printf("tmp = %s", tmp);
		if (tmp == NULL)
			return (NULL);
		if (line != NULL)
			free(line);
		line = ft_strdup(tmp);
		// printf("line = %s", line);
		free(tmp);
		free(buf);
		if (line == NULL)
			return (NULL);
		buf = get_next_line(fd);
		// printf("buf = %s",buf);
	}
	return (ft_split(line, '\n'));
}

int	get_z(char *line, int i, int *z)
{
	int	temp;

	while (line[i] == ' ' && line[i])
		i++;
	if (!((line[i] == '-' || line[i] == '+' || (line[i] >= '0'
		&& line[i] <= '9')) && line[i]))
		return (-1);
	temp = ft_atoi(&line[i]);
	if (temp > *z)
		*z = temp;
	while ((line[i] == '-' || line[i] == '+') && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9' && line[i])
		i++;
	while ((line[i] == ',' || line[i] == ' ' || line[i] == '\n') && line[i])
		i++;
	return (i);
}

// Let's call the row axis "r" and the column axis "c", and consider the first picture, where the extent along the r axis is 5 and the extent along the c axis is 3.
// The unit increment along the r axis, relative to the drawing plane, is at angle +30 = (cos 30°, sin 30°) = (sqrt(3)/2, 0.5), and the unit increment along the c axis is at -30 = (cos 30°, -sin 30°) = (sqrt(3)/2, -0.5).
// You need to consider the two diagonals of your isometric rectangle. In the first picture, those diagonals are D1 = [+5*U along the r axis and +3*U along the c axis] and D2 = [+5*U along the r axis and -3*U along the c axis], where U is the tile length in the isometric plane. When transformed into the drawing plane, this becomes D1 = ((5+3)*sqrt(3)/2*U, (5-3)/2*U) = (4*sqrt(3)*U, 1*U) and D2 = ((5-3)*sqrt(3)/2*U, (5+3)/2*U) = (sqrt(3)*U, 4*U). The screen width and height, therefore, are the maximum of the two extents = 4*sqrt(3)*U, 4*U.
// This can be generalized: if there are Nr rows and Nc columns, and the tile length is U, the extent of the diagonals of the rectangle in the drawing plane are D1 = ((Nr+Nc)*sqrt(3)/2*U, (Nr-Nc)/2*U) and D2 = ((Nr-Nc)*sqrt(3)/2*U, (Nr+Nc)/2*U), and the screen width and height, therefore, are:

// Width = info->tile_size*(info->wd_width+info->wd_height)*sqrt(3)/2
// Height = info->tile_size*(info->wd_width+info->wd_height)/2

void	get_tile_size(t_info *info, int z)//width * tile_size * 2//not just z but z * tile_size
{
	int	i;
	int tmp_height;
	int tmp_width;

	info->tile_size = 15;//not bellow 1?
	i = 0;
	info->wd_width = info->wd_width + 2;
	if (z < 0)
		z = z * -1;
	info->wd_height = info->wd_height + z;//try with -z ???
	while (i == 0)
	{
		if (info->tile_size * (info->wd_width + info->wd_height) * sqrt(3)/2 > 800//1920
			|| info->tile_size * (info->wd_width + info->wd_height) / 2 > 600)//1080)
			info->tile_size--;
		else
		{
			tmp_width = info->tile_size * (info->wd_width + info->wd_height) * sqrt(3) / 2;
			tmp_height = info->tile_size * (info->wd_width + info->wd_height) / 2;
			i = 1;
		}
		if (info->tile_size == 1)
		{
			tmp_width = info->tile_size * (info->wd_width + info->wd_height) * sqrt(3) / 2;
			tmp_height = info->tile_size * (info->wd_width + info->wd_height) / 2;
			i = 1;
		}
	}
	info->wd_width = tmp_width;
	info->wd_height = tmp_height;

	// info->wd_width = 1000;
	// info->wd_height = 800;
}

// void	get_tile_size(t_info *info, int z)//width * tile_size * 2//not just z but z * tile_size
// {
// 	int	i;

// 	info->tile_size = 15;//not bellow 1?
// 	i = 0;
// 	info->wd_width = info->wd_width + 2;
// 	if (z < 0)
// 		z = z * -1;
// 	while (i == 0)
// 	{
// 		if (info->wd_width * info->tile_size + 100 > 800//1920
// 			|| (info->wd_height + z) * info->tile_size > 600)//1080)
// 			info->tile_size--;
// 		else
// 		{
// 			info->wd_width = info->wd_width * info->tile_size + 100;
// 			info->wd_height = (info->wd_height + z) * info->tile_size;
// 			i = 1;
// 		}
// 		if (info->tile_size == 1)
// 		{
// 			info->wd_width = info->wd_width * info->tile_size + 100;
// 			info->wd_height = (info->wd_height + z) * info->tile_size;
// 			i = 1;
// 		}
// 	}
// }

int	get_wd_size(t_info *info, char **line)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	info->wd_width = 0;
	info->z = -2147483648;
	while (line[i])
	{
		l = 0;
		j = 0;
		while (line[i][j])
		{
			j = get_z(line[i], j, &info->z);
			if (j == -1)
				return (-1);
			l++;
		}
		i++;
		if (l > info->wd_width)
			info->wd_width = l;//add +2 in tile_size
	}
	info->wd_height = i + 1;
	get_tile_size(info, info->z);
	printf("wd_height = %d, wd_width = %d\n", info->wd_height, info->wd_width);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int fd;
	char **line;

	if (argc != 2)
	{
		printf("error argc\n");
		return (-1);
	}
	fd = open(argv[1], O_RDONLY);
	line = prep_line(fd, get_next_line(fd));
	if (line == NULL)
	{
		printf("error line\n");
		return (-1);
	}


	if (get_wd_size(&info, line) == -1)
	{
		printf("error wd size\n");
		return (-1);
	}
	printf("highest z = %d\n", info.z);

	info.id = mlx_init();
	if (info.id == NULL)
	{
		printf("error id\n");
		return (-1);
	}
	

	// read_map(info);//get width/hight

	info.wd_ptr = mlx_new_window(info.id , info.wd_width, info.wd_height, "fdf" ); //int size_x, int size_y 1920x1080
	if (info.wd_ptr == NULL)
	{
		printf("error wd_ptr\n");
		return (-1);
	}
	// mlx_clear_window(info.id, info.wd_ptr);

	info.img.img_ptr = mlx_new_image(info.id, info.wd_width, info.wd_height);
	if (info.img.img_ptr == NULL)
	{
		printf("error img_ptr\n");
		return (-1);
	}
	info.img.addr = mlx_get_data_addr(info.img.img_ptr, &info.img.bpp, &info.img.line_len, &info.img.endian);
	if (render(&info, line) == -1)
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

