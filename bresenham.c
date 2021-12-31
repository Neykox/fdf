/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleroy <aleroy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 22:30:00 by aleroy            #+#    #+#             */
/*   Updated: 2021/12/12 22:30:02 by aleroy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf2.h"

// public void line(int x,int y,int x2, int y2, int color) {
//     int w = x2 - x ;
//     int h = y2 - y ;
//     int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
//     if (w<0) dx1 = -1 ; else if (w>0) dx1 = 1 ;
//     if (h<0) dy1 = -1 ; else if (h>0) dy1 = 1 ;
//     if (w<0) dx2 = -1 ; else if (w>0) dx2 = 1 ;
//     int longest = Math.abs(w) ;
//     int shortest = Math.abs(h) ;
//     if (!(longest>shortest)) {
//         longest = Math.abs(h) ;
//         shortest = Math.abs(w) ;
//         if (h<0) dy2 = -1 ; else if (h>0) dy2 = 1 ;
//         dx2 = 0 ;            
//     }
//     int numerator = longest >> 1 ;
//     for (int i=0;i<=longest;i++) {
//         putpixel(x,y,color) ;
//         numerator += shortest ;
//         if (!(numerator<longest)) {
//             numerator -= longest ;
//             x += dx1 ;
//             y += dy1 ;
//         } else {
//             x += dx2 ;
//             y += dy2 ;
//         }
//     }
// }

void	bresenham_new(t_img *img, t_coor *coor)//int x,int y,int x2, int y2, int color)
{
	int width = coor->x1 - coor->xold;
	int height = coor->y1 - coor->yold;

	int dx1 = 0;
	int dy1 = 0;
	int dx2 = 0;
	int dy2 = 0;
	if (width < 0)
	{
		dx1 = -1;
	}
	else if (width > 0)
	{
		dx1 = 1;
	}
	if (height < 0)
	{
		dy1 = -1;
	}
	else if (height > 0)
	{
		dy1 = 1;
	}
	if (width < 0)
	{
		dx2 = -1;
	}
	else if (width > 0)
	{	
		dx2 = 1;
	}


	int longest = abs(width);
	int shortest = abs(height);
	if (!(longest > shortest))
	{
		longest = abs(height);
		shortest = abs(width);
		if (height < 0)
			dy2 = -1;
		else if (height > 0)
			dy2 = 1;
		dx2 = 0 ;
	}

	int numerator = longest / 2;
	int i = 0;
	// if (coor->z1 != 0 || coor->zold != 0)
	// 	{
	// 		printf("\033[0;32mx1 = %d, y1 = %d, z1 = %d\n", coor->x1, coor->y1, coor->z1);
	// 		printf("xold = %d, yold = %d, zold = %d\n\033[0m", coor->xold, coor->yold, coor->zold);
	// 	}
	// 	else
	// 	{
	// 		printf("x1 = %d, y1 = %d, z1 = %d\n", coor->x1, coor->y1, coor->z1);
	// 		printf("xold = %d, yold = %d, zold = %d\n", coor->xold, coor->yold, coor->zold);
	// 	}
	while (i <= longest)
	{
		img_pix_put(img, coor->xold, coor->yold, coor->color);
		numerator += shortest ;
		if (!(numerator < longest))
		{
			numerator -= longest;
			coor->xold += dx1;
			coor->yold += dy1;
		}
		else
		{
			coor->xold += dx2;
			coor->yold += dy2;
		}
		// if (coor->z1 != 0 || coor->zold != 0)
		// 	coor->color += 2;
		i++;
	}
}

void	rev_coor(t_img *img, t_coor *coor)
{
	t_coor preped;

	preped.tile_size = coor->tile_size;
	preped.x1 = coor->xold ;//+ coor->tile_size * 2;
	preped.y1 = coor->yold;
	preped.z1 = coor->zold;
	preped.xold = coor->x1;
	preped.yold = coor->y1;
	preped.zold = coor->z1;
	preped.color = coor->color;
	bresenham_new(img, &preped);
	// bresenham(img, coor);

	// coor->y1 = coor->y1 - coor->z1;
	// coor->yold = coor->yold - coor->zold;
	// bresenham2(img, coor);
}

void bresenham2(t_img *img, t_coor *coor)
{
	// printf("x1 = %d, y1 = %d, z1 = %d\n", coor->x1, coor->y1, coor->z1);
	// printf("xold = %d, yold = %d, zold = %d\n", coor->xold, coor->yold, coor->zold);
	int x;
	int y;
	int m_new = 2 * (coor->x1 - coor->xold);//original slope?
	// printf("m_new = %d\n", m_new);
	int slope_error_new = m_new - (coor->y1 - coor->yold);
	// printf("slope_error_new = %d\n", slope_error_new);

	x = coor->xold;
	y = coor->yold;
	// coor->color = 0xff0000;//= red
	while (y <= coor->y1)
	{
		img_pix_put(img, x, y, coor->color);

	  // Add slope to increment angle formed
	  slope_error_new += m_new;
	  // printf("slope_error_new + m_new = %d\n", slope_error_new);

	  // Slope error reached limit, time to
	  // increment y and update slope error.
		if (slope_error_new >= 0)
		{
			x++;
			slope_error_new  -= 2 * (coor->y1 - coor->yold);
			// printf("in if slope_error_new = %d\n", slope_error_new);
		}
		y++;
		// printf("x = %d, y = %d\n", x, y);
	}
	// coor->color = 0xffffff;
}

void bresenham4(t_img *img, t_coor *coor)
{
	// printf("x1 = %d, y1 = %d, z1 = %d\n", coor->x1, coor->y1, coor->z1);
	// printf("xold = %d, yold = %d, zold = %d\n", coor->xold, coor->yold, coor->zold);
	int x;
	int y;
	int m_new = 2 * (coor->x1 - coor->xold);//original slope?
	// printf("m_new = %d\n", m_new);
	int slope_error_new = m_new - (coor->y1 - coor->yold);
	// printf("slope_error_new = %d\n", slope_error_new);

	x = coor->xold;
	y = coor->yold;
	// coor->color = 0xff0000;//= red
	while (y <= coor->y1)
	{
		img_pix_put(img, x, y, coor->color);//repasse dans iso first?

	  // Add slope to increment angle formed
	  slope_error_new += m_new;
	  // printf("slope_error_new + m_new = %d\n", slope_error_new);

	  // Slope error reached limit, time to
	  // increment y and update slope error.
		if (slope_error_new <= 0)
		{
			x--;
			slope_error_new  -= 2 * (coor->y1 - coor->yold);
			// printf("in if slope_error_new = %d\n", slope_error_new);
		}
		y++;
		// printf("x = %d, y = %d\n", x, y);
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
	while (x <= coor->x1)
	{
		img_pix_put(img, x, y, coor->color);

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
}

void bresenham3(t_img *img, t_coor *coor)
{
	// printf("x1 = %d, y1 = %d, z1 = %d\n", coor->x1, coor->y1, coor->z1);
	// printf("xold = %d, yold = %d, zold = %d\n", coor->xold, coor->yold, coor->zold);
	int x;
	int y;
	int m_new = 2 * (coor->yold - coor->y1);//original slope?
	int slope_error_new = m_new - (coor->xold - coor->x1);

	x = coor->x1;
	y = coor->y1;// - coor->zold;
	// coor->color = 0xff0000;//= red
	while (x <= coor->xold)
	{
		img_pix_put(img, x, y, coor->color);

	  // Add slope to increment angle formed
	  slope_error_new += m_new;

	  // Slope error reached limit, time to
	  // increment y and update slope error.
		// if (slope_error_new >= 0)
		// {
		// 	y++;
		// 	slope_error_new  -= 2 * (coor->xold - coor->x1);
		// }
		if (slope_error_new <= 0)
		{
			y--;
			slope_error_new  -= 2 * (coor->xold - coor->x1);
		}
		x++;
	}
	// printf("x = %d, y = %d\n\n", x, y);
	// coor->color = 0xffffff;
}

// void bresenham2(t_img *img, t_coor *coor)
// {
// 	int x;
// 	int y;
// 	int m_new = 2 * (coor->x1 - coor->xold);//original slope?
// 	int slope_error_new = m_new - (coor->y1 - coor->z1 - coor->yold - coor->zold);

// 	x = coor->xold;
// 	y = coor->yold - coor->zold;
// 	// coor->color = 0xff0000;//= red
// 	while (y <= coor->y1 - coor->z1)
// 	{
// 		// img_pix_put(img, x, y, coor->color);
// 		place_point2(img, x, y, coor->color);
// 	  // cout << "(" << x << "," << y << ")\n";

// 	  // Add slope to increment angle formed
// 	  slope_error_new += m_new;

// 	  // Slope error reached limit, time to
// 	  // increment y and update slope error.
// 		if (slope_error_new >= 0)
// 		{
// 			x++;
// 			slope_error_new  -= 2 * (coor->y1 - coor->z1 - coor->yold - coor->zold);
// 		}
// 		y++;
// 	}
// 	// coor->color = 0xffffff;
// }

// void bresenham(t_img *img, t_coor *coor)
// {
// 	int x;
// 	int y;
// 	int m_new = 2 * (coor->y1 - coor->z1 - coor->yold - coor->zold);//original slope?
// 	int slope_error_new = m_new - (coor->x1 - coor->xold);

// 	x = coor->xold;
// 	y = coor->yold - coor->zold;// - coor->zold;
// 	// coor->color = 0xff0000;//= red
// 	while (x <= coor->x1)
// 	{
// 		// img_pix_put(img, x, y, coor->color);
// 		place_point2(img, x, y, coor->color);
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
// 	// coor->color = 0xffffff;
// }
