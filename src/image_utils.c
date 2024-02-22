/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:37:05 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/22 17:12:53 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	set_pixel(unsigned char *pixel, int color)
{
	*(pixel++) = (unsigned char)(color >> 24);
	*(pixel++) = (unsigned char)(color >> 16);
	*(pixel++) = (unsigned char)(color >> 8);
	*(pixel++) = (unsigned char)(color & 0xFF);
}

void	draw_pixel(mlx_image_t *img, int x, int y, int color)
{
	unsigned char	*pixel;

	if (img)
		if (x >= 0 && x < (int)img->width && y >= 0 && y < (int)img->height)
		{	
			pixel = &img->pixels[(y * img->width + x) * PIXEL_SIZE];
			set_pixel(pixel, color);
		}	
}

/* ************************************************************************** */

static int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_pixel(mlx_image_t* img, t_u32 x, t_u32 y)
{
	t_u8	*pixelstart;
	
	if (x > img->width || y > img->height)
    	return (0xFF000000);
	pixelstart = img->pixels + (y * img->width + x) * PIXEL_SIZE;
	
	return (get_rgba(*(pixelstart), *(pixelstart + 1),
    * (pixelstart + 2), *(pixelstart + 3)));
}

/* ************************************************************************** */

/*
in case the dst image is smaller
*/
static int	pixel_is_valid(mlx_image_t* img, t_u32 x, t_u32 y)
{
	return (x < img->width && y < img->height);
}

/*
copy an image to another image
*/
void	put_img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y)
{
	int	i;
	int	j;
	
	i = 0;
	while (i < (int)src->width)
	{
		j = 0;
		while (j < (int)src->height)
		{
			if (pixel_is_valid(src, i, j))
				draw_pixel(dst, x + i, y + j, get_pixel(src, i, j));
			j++;
		}
		i++;
	}
}
