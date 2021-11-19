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

// The pseudocode for the loop then looks like this:

// for(i, loop through rows)
//   for(j, loop through columns)
//     x = j * tile width
//     y = i * tile height
//     tileType = levelData[i][j]
//     placetile(tileType, twoDToIso(new Point(x, y)))

// void bresenham(t_img *img, t_coor *coor)
// {
// 	int x;
// 	int y;
// 	int m_new = 2 * (coor->y2 - coor->y1);//original slope?
// 	int slope_error_new = m_new - (coor->x2 - coor->x1);

// 	x = coor->x1;
// 	y = coor->y1;
// 	coor->color = 0xff0000;//= red
// 	while (x <= coor->x2)
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
// 			slope_error_new  -= 2 * (coor->x2 - coor->x1);
// 		}
// 		x++;
// 	}
// 	coor->color = 0xffffff;
// }

void bresenham(t_img *img, t_coor *coor)
{
	int x;
	int y;
	int m_new = 2 * (coor->y1 - coor->y2);//original slope?
	int slope_error_new = m_new - (coor->x1 - coor->x2);

	x = coor->x2;
	y = coor->y2;
	coor->color = 0xff0000;//= red
	while (x <= coor->x1)
	{
		img_pix_put(img, x, y, coor->color);
	  // cout << "(" << x << "," << y << ")\n";

	  // Add slope to increment angle formed
	  slope_error_new += m_new;

	  // Slope error reached limit, time to
	  // increment y and update slope error.
		if (slope_error_new >= 0)
		{
			y++;
			slope_error_new  -= 2 * (coor->x1 - coor->x2);
		}
		x++;
	}
	coor->color = 0xffffff;
}

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

int	ft_atoi(const char *str)
{
	int		j;
	int		result;
	int		sign;

	j = 0;
	sign = 1;
	result = 0;
	while ((str[j] >= 9 && str[j] <= 13) || str[j] == 32)
		j++;
	if (str[j] == '-')
		sign = -1;
	if (str[j] == '-' || str[j] == '+')
		j++;
	while (str[j] != '\0' && str[j] >= '0' && str[j] <= '9')
	{
		result = (result * 10) + (str[j] - 48);
		j++;
	}
	return (result * sign);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	char	*copie;
	char	*str;
	int		i;

	i = 0;
	str = (char*)s1;
	if (!(copie = (char *)malloc((ft_strlen(str) + 1) * sizeof(char))))
		return (NULL);
	while (str[i])
	{
		copie[i] = str[i];
		i++;
	}
	copie[i] = '\0';
	return (copie);
}

int	get_coor(t_coor *coor, char *line, int i)
{
	while (line[i] == ' ' && line[i])
		i++;
	if (!((line[i] == '-' || line[i] == '+' || (line[i] >= '0'
		&& line[i] <= '9')) && line[i]))
		return (-1);
	coor->z1 = ft_atoi(&line[i]);
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
	int	count;

	i = 0;
	count = 0;
	coor->y2 = coor->y1;
	while (line[i])
	{
		i = get_coor(coor, line, i);
		coor->z2 = coor->z1;
		coor->x2 = coor->x1;
		coor->x1 = coor->x1 + 15;
		if (count == 0)
			i = get_coor(coor, line, i);
		count++;
		// printf("x1 = %d, y1 = %d, z1 = %d\n", coor->x1, coor->y1, coor->z1);
		// printf("x2 = %d, y2 = %d, z2 = %d\n", coor->x2, coor->y2, coor->z2);
		bresenham(img, coor);
	}
}

void	connect_lines(t_img *img, t_coor *coor, char *line, char *line2)
{}

int	render(t_info *info, char *line, int fd) //need to handle /n in line
{
	// free(line);
	// fd++;

	char	*line2;
	t_coor coor;
	int i;

	i = 0;
	line2 = NULL;
	coor.z1 = 0;
	// int row = 0;
	// int col = 0;
	// coor.color = 0xff0000;//= red
	// if (info->wd_ptr == NULL)
	// 	return (1);
	clear_background(&info->img, 0x0);//black #define BLACK_PIXEL 0x0 (purple = 0x9b30ff)
	// render_rect(&data->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
	// render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});
	while (line)
	{
		i = 0;
		while (line[i])
		{
			i = get_coor(&coor, line, i);
			if (i == -1)
				return (-1);
			// place_point(&info->img, coor);
			img_pix_put(&info->img , coor.x1, coor.y1, coor.color);
			// coor.z1++;
			// printf("i = %d, z = %d\n", i, coor.z1);
			// coor.x1 = row * 6;
			coor.x1 = coor.x1 + 15;
			// row++;
		}
		coor.x1 = 0;
		connect_point(&info->img, &coor, line);//axe x
		coor.x1 = 0;
		if (line2 != NULL)
			free(line2);
		line2 = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		if (line2 == NULL)
			return (-1);
		if (line == NULL)
			break;//return (-1);?
		connect_lines(&info->img, &coor, line, line2);//axe y
		// coor.y1 = col * 4;
		coor.y1 = coor.y1 + 15;
		coor.x1 = 0;
		// col++;
		// if (col == 1)
		// 	coor.color = 0x00ff00;
		// else if (col == 2)
		// 	coor.color = 0x0000ff;
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
