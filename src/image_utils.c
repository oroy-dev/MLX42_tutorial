/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:37:05 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/26 12:51:19 by cdumais          ###   ########.fr       */
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

int	get_rgba(int r, int g, int b, int a)
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

/* ************************************************************************** */
static int	ft_signum(int start, int end)
{
	if (start < end)
		return (1);
	if (start > end)
		return (-1);
	return (0);
}

static t_point	get_direction(t_point start, t_point end)
{
	t_point	direction;

	direction.x = ft_signum(start.x, end.x);
	direction.y = ft_signum(start.y, end.y);
	return (direction);
}

static t_point	get_distance(t_point start, t_point end)
{
	t_point	distance;

	distance.x = ft_abs(end.x - start.x);
	distance.y = ft_abs(end.y - start.y);
	return (distance);
}

static int	calculate_initial_error(t_point distance)
{
	if (distance.x > distance.y)
		return (distance.x / 2);
	else
		return (-distance.y / 2);
}

/*
bresenham's line algorithm
*/
void	bres_line(mlx_image_t *img, t_point start, t_point end, int color)
{
	t_point	direction;
	t_point	distance;
	int		error;
	int		error_tmp;
	
	direction = get_direction(start, end);
	distance = get_distance(start, end);
	error = calculate_initial_error(distance);
	while (TRUE)
	{
		draw_pixel(img, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		error_tmp = error;
		if (error_tmp > -distance.x)
		{
			error -= distance.y;
			start.x += direction.x;
		}
		if (error_tmp < distance.y)
		{
			error += distance.x;
			start.y += direction.y;
		}
	}
}

/* ************************************************************************** */

static void	draw_circle_coords(mlx_image_t *img, t_point center, t_point current, int color)
{
	int	x;
	int	y;

	x = current.x;
	y = current.y;
	bres_line(img, (t_point){center.x + x, center.y + y}, (t_point){center.x - x, center.y + y}, color);
	bres_line(img, (t_point){center.x + x, center.y - y}, (t_point){center.x - x, center.y - y}, color);
	bres_line(img, (t_point){center.x + y, center.y + x}, (t_point){center.x - y, center.y + x}, color);
	bres_line(img, (t_point){center.x + y, center.y - x}, (t_point){center.x - y, center.y - x}, color);
}

/*
using bresenham's midpoint algorithm
*/
void	draw_circle(mlx_image_t *img, t_point center, int radius, int color)
{
	int	x;
	int	y;
	int	decision;

	x = 0;
	y = radius;
	decision = 3 - 2 * radius;
	while (y >= x)
	{
		// for each pixel, draw all eight pixels
		draw_circle_coords(img, center, (t_point){x, y}, color);
		x++;

		// check for decision param and correspondingly update d, x, y
		if (decision > 0)
		{
			y--;
			decision = decision + 4 * (x - y) + 10;
		}
		else
			decision = decision + 4 * x + 6;
		draw_circle_coords(img, center, (t_point){x, y}, color);
	}
}
