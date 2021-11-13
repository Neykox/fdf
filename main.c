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

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

// make drawer √
// create/push image to window √
// bresenham (add color?)
// point placer

typedef struct s_coor
{
	int		x1;
	int		y1;
	int		z1;
	int		x2;
	int		y2;
	int		z2;
	int		color;
}				t_coor;

// function isoTo2D(pt:Point):Point{
//   var tempPt:Point = new Point(0, 0);
//   tempPt.x = (2 * pt.y + pt.x) / 2;
//   tempPt.y = (2 * pt.y - pt.x) / 2;
//   return(tempPt);
// }

function twoDToIso(pt:Point):Point{
  var tempPt:Point = new Point(0,0);
  tempPt.x = pt.x - pt.y;
  tempPt.y = (pt.x + pt.y) / 2;
  return(tempPt);
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

void	place_point(t_info *info, t_coor coor)
{}

The pseudocode for the loop then looks like this:

for(i, loop through rows)
  for(j, loop through columns)
    x = j * tile width
    y = i * tile height
    tileType = levelData[i][j]
    placetile(tileType, twoDToIso(new Point(x, y)))

void bresenham(t_img *img, t_coor *coor)
{
	int x;
	int y;
	int m_new = 2 * (coor->y2 - coor->y1);//original slope?
	int slope_error_new = m_new - (coor->x2 - coor->x1);

	x = coor->x1;
	y = coor->y1; 
	while (x <= coor->x2)
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
			slope_error_new  -= 2 * (coor->x2 - coor->x1);
		}
		x++;
	}
}

void	clear_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j, i, color);
			j++;
		}
		++i;
	}
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;

    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	get_coor(t_coor *coor, char *line, int i)
{
	while (line[i] == ' ' && line[i])
		i++;
	if (!((line[i] == '-' || line[i] == '+') && line[i] >= '0'
		&& line[i] <= '9' && line[i]))
		return (-1);
	coor->z1 = ft_atoi(&line[i]);
	while ((line[i] == '-' || line[i] == '+') && line[i])
		i++;
	while (line[i] >= '0' && line[i] <= '9' && line[i])
		i++;
	coor->color = 0xffffff;//white #define WHITE_PIXEL 0xffffff
	return (i);
}

int	render(t_info *info, char *line, int fd)
{
	char	line2;
	t_coor coor;
	int i;

	i = 0;
	line2 = NULL;
	coor.x1 = 0;
	// if (info->wd_ptr == NULL)
	// 	return (1);
	clear_background(&info->img, 0x0);//black #define BLACK_PIXEL 0x0
	// render_rect(&data->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
	// render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});
	while (line)
	{
		while (line[i])
		{
			i = get_coor(&coor, line, i);
			if (i == -1)
				return (-1);
			place_point(&info, coor);
			coor.x1++;
		}
		connect_point(&info, line);//axe x
		if (line2 != NULL)
			free(line2);
		line2 = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		if (line2 == NULL)
			return (-1)
		if (line == NULL)
			break;//return (-1);?
		connect_lines(line, line2);//axe y
		coor.y1++;
	}


	mlx_put_image_to_window(info->id, info->wd_ptr, info->img.img_ptr, 0, 0);

	return (0);
}

int	handle_event(int key_sym, t_info *info)
{
	if (key_sym == XK_Escape)
		mlx_destroy_window(info->id, info->wd_ptr);
	return (0);
}

int	main()//int argc, char **argv)
{
	t_info	info;
	// int fd;
	// char *line;

	// fd = open(argv[1], O_RDONLY);
	// line = get_next_line(fd);
	// if (line == NULL)
	// 	return (-1);


	info.id = mlx_init();
	if (info.id == NULL)//|| argc != 2)
		return (-1);

	// read_map(info);//get width/hight

	info.wd_ptr = mlx_new_window(info.id , WINDOW_WIDTH, WINDOW_HEIGHT, "fdf" ); //int size_x, int size_y 1920x1080
	if (info.wd_ptr == NULL)
		return (-1);
	mlx_clear_window(info.id, info.wd_ptr);

	// info.img.img_ptr = mlx_new_image(info.id, WINDOW_WIDTH, WINDOW_HEIGHT);
	// if (info.img.img_ptr == NULL)
	// 	return (-1);
	// info.img.addr = mlx_get_data_addr(info.img.img_ptr, info.img.bpp, info.img.line_len, info.img.endian);
	// if (render(&info, line, fd) == -1)
	//	return (-1);

	// mlx_loop_hook(info.id, &render, &info);
	mlx_key_hook(info.wd_ptr, &handle_event, &info);

	mlx_loop(info.id);

	// mlx_destroy_image(info.id, info.img.img_ptr);
	mlx_destroy_display(info.id);
	// free(info.id);
	// free(info.wd_ptr);
	free(info);
	return (0);
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

// 	// while (1)
// 	// 	;

// 	// if (event(info) == 1)
// 		mlx_destroy_window(id, wd_ptr);
// 	mlx_destroy_display(id);
// 	free(id);
// 	free(wd_ptr);
// 	return (0);
// }

// int	main()
// {
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

// 	// while (1)
// 	// 	;

// 	// if (event(info) == 1)
// 		mlx_destroy_window(info->id, info->wd_ptr);
// 		mlx_destroy_display(info->id);
// 	free(info->id);
// 	free(info->wd_ptr);
// 	free(info);
// 	return (0);
// }
