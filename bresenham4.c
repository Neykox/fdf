/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 17:49:49 by user42            #+#    #+#             */
/*   Updated: 2022/01/03 17:49:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf4.h"

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

void	bresenham_new(t_info *info, t_coor *coor)
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
		img_pix_put(info, &info->img, coor->xold, coor->yold, coor->color);
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
