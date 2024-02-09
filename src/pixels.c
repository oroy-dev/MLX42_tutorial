/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:48:29 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/08 17:40:59 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
place the values of 'color' at the address 'pixel'
*/
static void	set_pixel(unsigned char *pixel, int color)
{
	*(pixel++) = (unsigned char)(color >> 24);
	*(pixel++) = (unsigned char)(color >> 16);
	*(pixel++) = (unsigned char)(color >> 8);
	*(pixel++) = (unsigned char)(color);
}

/*
sets the alpha channel to 0xFF
*/
static int	rgba(int color)
{
	int	rgba;

	rgba = (color << 8) | 0xFF;
	return (rgba);
}

void	draw_pixel(mlx_image_t *img, int x, int y, int color)
{
	unsigned char	*pixel;

	if (img)
		if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		{	
			pixel = &img->pixels[(y * img->width + x) * PIXEL_SIZE];
			set_pixel(pixel, rgba(color));
		}	
}

// 

void	draw_line(mlx_image_t *img, t_point start, t_point end, int color)
{
	t_point	step;
	int		max;

	step.x = end.x - start.x;
	step.y = end.y - start.y;
	max = ft_max(ft_abs(step.x), ft_abs(step.y));
	step.x /= max;
	step.y /= max;
	while ((int)(start.x - end.x) || (int)(start.y - end.y))
	{
		draw_pixel(img, start.x, start.y, color);
		start.x += step.x;
		start.y += step.y;
	}
}
