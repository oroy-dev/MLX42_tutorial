/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:37:05 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/12 21:41:06 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
in case the dst image is smaller
*/
static int	pixel_is_valid(mlx_image_t* img, uint32_t x, uint32_t y)
{
	// return (x < img->width && y < img->height && get_pixel(img, x, y) != 0);
	return (x < img->width && y < img->height && get_pixel(img, x, y) != 0);
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
