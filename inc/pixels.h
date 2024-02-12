/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:51:21 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/12 14:37:38 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXELS_H
# define PIXELS_H

# include "MLX42.h" // mlx_image_t
# include "libft.h" // data type macros (like t_u32 for unsigned int) in libft_utils.h

/* bytes per pixel */
# define PIXEL_SIZE		4

# define ALPHA_MASK		0xFF000000
# define RED_MASK		0x00FF0000
# define GREEN_MASK		0x0000FF00
# define BLUE_MASK		0x000000FF

# define ALPHA_SHIFT	24
# define RED_SHIFT		16
# define GREEN_SHIFT	8
// No shift needed for BLUE

typedef enum
{
	ALPHA_OFFSET = 0,
	RED_OFFSET,
	GREEN_OFFSET,
	BLUE_OFFSET
}	e_color_offset;

# define HEX_BLACK			0x000000
# define HEX_GRAY			0x404040
# define HEX_WHITE			0xFFFFFF
# define HEX_RED			0xFF0000
# define HEX_GREEN			0x00FF00
# define HEX_BLUE			0x0000FF
# define HEX_YELLOW			0xFFFF00
# define HEX_MAGENTA		0xFF00FF //bright on mac
# define HEX_CYAN			0x00FFFF

# define HEX_ORANGE 		0xFF7700 //best orange on mac
# define HEX_ORANGEY		0xED840C //between orange and yellow on mac
# define HEX_PURPLE			0x800080 //weak on MAC
# define HEX_OLILAS			0xA27CF1 //bluish purple on mac
# define HEX_PINK			0xFFC0CB //pale pink on mac
# define HEX_BROWN			0x663300 //weak dark orange on mac

// static t_u32	rgba(t_u32 color);
// static void		set_pixel_color(t_u8 *pixel, t_u32 color);
void			draw_pixel(mlx_image_t *img, t_u32 x, t_u32 y, t_u32 color);

// static t_u32	get_pixel_color(t_u8 *pixel);
t_u32			get_pixel(mlx_image_t *img, t_u32 x, t_u32 y);

#endif
