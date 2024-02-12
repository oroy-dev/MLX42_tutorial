/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 14:48:29 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/12 14:41:24 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixels.h"

/*
sets the alpha channel to 0xFF
(allowing the 0xRRGGBB format for 'draw_pixel()')
*/
static t_u32	rgba(t_u32 color)
{
	t_u32	rgba;

	rgba = (color << 8) | 0xFF;
	return (rgba);
}

/* ************************************************************************** */

/*
places the values of 'color' at the address 'pixel'
encodes four individual bytes into an int
*/
static void	set_pixel_color(t_u8 *pixel, t_u32 color)
{
	*(pixel++) = (t_u8)(color >> 24);
	*(pixel++) = (t_u8)(color >> 16);
	*(pixel++) = (t_u8)(color >> 8);
	*(pixel++) = (t_u8)(color);
}

/*
*/
void	draw_pixel(mlx_image_t *img, t_u32 x, t_u32 y, t_u32 color)
{
	t_u8	*pixel;

	if (img)
	{
		if (x < img->width && y < img->height)
		{
			pixel = &img->pixels[(y * img->width + x) * PIXEL_SIZE];
			set_pixel_color(pixel, rgba(color));
		}
		// error: Pixel is out of bounds
	}
	// error: 'img' is NULL
}

/* ************************************************************************** */

/*
Retrieves the color value from the specified pixel address in ARGB format,
combining four individual bytes back into a t_u32.
*/
static t_u32	get_pixel_color(t_u8 *pixel)
{
	t_u32	a;
	t_u32	r;
	t_u32	g;
	t_u32	b;

    // Extract each color component from the pixel
    a = (t_u32)pixel[ALPHA_OFFSET] << 24;
    r = (t_u32)pixel[RED_OFFSET] << 16;
    g = (t_u32)pixel[GREEN_OFFSET] << 8;
    b = (t_u32)pixel[BLUE_OFFSET];

    // Combine the color components into a single t_u32 color value
	return (a | r | g | b);
}

/*
*/
t_u32	get_pixel(mlx_image_t *img, t_u32 x, t_u32 y)
{
	t_u8	*pixel;

    if (img)
	{
        if (x < img->width && y < img->height)
		{
            pixel = &img->pixels[(y * img->width + x) * PIXEL_SIZE];
            return (get_pixel_color(pixel));
        }
		// error: Pixel is out of bounds
		return (rgba(0x000000));
	}
	// error: 'img' is NULL
	return (rgba(0x000000));
}

// /* ************************************************************************** */
// /* ************************************************************************** */
// /* ************************************************************************** */

// // variations for 'set_pixel'

// /*
// using hexadecimal masks to isolate each color component from the int 'color'
// and then divides by a power of 256
// (equivalent to shifting right by 8 bits)
// */
// static void	set_pixel_v1(t_u8 *pixel, t_u32 color)
// {
// 	*(pixel++) = (t_u8)((color & 0xFF000000) / 0x1000000); // isolate A component
// 	*(pixel++) = (t_u8)((color & 0x00FF0000) / 0x10000); // isolate R component
// 	*(pixel++) = (t_u8)((color & 0x0000FF00) / 0x100); // isolate G component
// 	*(pixel++) = (t_u8)(color & 0x000000FF); // isolate B component
// }

// /*
// using hexadecimal masks, division and modulo
// to extract/isolate each color component
// */
// static void set_pixel_v2(t_u8 *pixel, t_u32 color)
// {
// 	*(pixel++) = (t_u8)((color / 0x1000000) % 0x100); // Isolate A component
// 	*(pixel++) = (t_u8)((color / 0x10000) % 0x100); // Isolate R component
// 	*(pixel++) = (t_u8)((color / 0x100) % 0x100); // Isolate G component
// 	*(pixel++) = (t_u8)(color % 0x100); // Isolate B component
// }

// /*
// using array and loop for component extraction
// abstracts the process of setting each pixel's color component into a loop,
// to show how each part of the color is processed in sequence
// */
// static void set_pixel_v3(t_u8 *pixel, t_u32 color)
// {
// 	t_u32	colorComponents[4] = {
// 		(color & 0xFF000000) / 0x1000000,
// 		(color & 0x00FF0000) / 0x10000,
// 		(color & 0x0000FF00) / 0x100,
// 		(color & 0x000000FF)
// 	};

// 	int	i = 0;
// 	while (i < 4)
// 	{
// 		*(pixel++) = (t_u8)colorComponents[i];
// 		i++;
// 	}
// }

// /*
// Hexadecimal Masks:
// Applying a mask like '0xFF000000'
// isolates a specific byte from the integer color value.
// (like covering all parts of a number we don't want to see,
// leaving only the part we're interested in visible)

// Division and Modulo:

// Division by a power of 0x100 (256) moves the digits down,
// making a higher-order byte into the lowest-order position.
// The modulo operation ensures we only get the last byte of the result,
// which corresponds to a color component.
// */

// /* ************************************************************************** */
// /* ************************************************************************** */

// // variations for '*(pixel++)'
// /*
// Dereferences the pointer to write a value
// and then increments the pointer to the next position in memory.
// */

// /*
// Direct Index Access:
// Avoids the post-increment operator
// explicitly uses indices to access and set each byte of the pixel
// */
// static void	set_pixel_explicit_v1(t_u8 *pixel, t_u32 color)
// {
// 	pixel[0] = (t_u8)(color >> 24); // Alpha component
// 	pixel[1] = (t_u8)(color >> 16); // Red component
// 	pixel[2] = (t_u8)(color >> 8); // Green component
// 	pixel[3] = (t_u8)(color); // Blue component
// }

// /*
// Increment Pointer Manually:
// Separates the pointer increment from the dereference operation for clarity.
// */
// static void	set_pixel_explicit_v2(t_u8 *pixel, t_u32 color)
// {
// 	*pixel = (t_u8)(color >> 24); // Alpha component
// 	pixel += 1; // Move to the next byte

// 	*pixel = (t_u8)(color >> 16); // Red component
// 	pixel += 1;

// 	*pixel = (t_u8)(color >> 8); // Green component
// 	pixel += 1;

// 	*pixel = (t_u8)(color); // Blue component
// 	// No need to move the pointer after the last assignment
// }

// /*
// Using Separate Function Calls:
// using a function that sets a single byte
// */
// static void	set_byte(t_u8 *pixel, t_u8 value)
// {
// 	*pixel = value;
// }

// static void	set_pixel_explicit_v3(t_u8 *pixel, t_u32 color)
// {
// 	set_byte(pixel, (t_u8)(color >> 24)); // Alpha component
// 	set_byte(pixel + 1, (t_u8)(color >> 16)); // Red component
// 	set_byte(pixel + 2, (t_u8)(color >> 8)); // Green component
// 	set_byte(pixel + 3, (t_u8)(color)); // Blue component
// }

// /* ************************************************************************** */
// /* ************************************************************************** */

// // #define ALPHA_MASK	0xFF000000
// // #define RED_MASK	0x00FF0000
// // #define GREEN_MASK	0x0000FF00
// // #define BLUE_MASK	0x000000FF

// // #define ALPHA_SHIFT	24
// // #define RED_SHIFT	16
// // #define GREEN_SHIFT	8
// // // No shift needed for BLUE

// // typedef enum
// // {
// // 	ALPHA_OFFSET = 0,
// // 	RED_OFFSET,
// // 	GREEN_OFFSET,
// // 	BLUE_OFFSET
// // }	e_color_offset;

// /*
// isolates a color channel
// Takes the color, applies the mask,
// performs the shift (right shift for extraction),
// and returns the isolated value.
// */
// static t_u8	isolate_channel(t_u32 color, int mask, int shift)
// {
//     return ((t_u8)((color & mask) >> shift));
// }

// static void	set_pixel_with_macros(t_u8 *pixel, t_u32 color)
// {
//     *(pixel + ALPHA_OFFSET) = isolate_channel(color, ALPHA_MASK, ALPHA_SHIFT);
//     *(pixel + RED_OFFSET) = isolate_channel(color, RED_MASK, RED_SHIFT);
//     *(pixel + GREEN_OFFSET) = isolate_channel(color, GREEN_MASK, GREEN_SHIFT);
//     *(pixel + BLUE_OFFSET) = isolate_channel(color, BLUE_MASK, 0);
// }

// /* ************************************************************************** */
// /* ************************************************************************** */

// // MLX42's 'mlx_put_pixel'

// /*
// // BUG: Linux may experience a red hue instead due to endianness
// void mlx_draw_pixel(uint8_t* pixel, uint32_t color)
// {
// 	*(pixel++) = (uint8_t)(color >> 24);
// 	*(pixel++) = (uint8_t)(color >> 16);
// 	*(pixel++) = (uint8_t)(color >> 8);
// 	*(pixel++) = (uint8_t)(color & 0xFF);
// }

// void mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
// {
// 	MLX_NONNULL(image);
// 	MLX_ASSERT(x < image->width, "Pixel is out of bounds");
// 	MLX_ASSERT(y < image->height, "Pixel is out of bounds");

// 	uint8_t* pixel = &image->pixels[(y * image->width + x) * BPP];
// 	mlx_draw_pixel(pixel, color);
// }
// */

// /* ************************************************************************** */
// /* ************************************************************************** */

// // pulgamecanica's 'get_pixel()'

// /*
// static int get_rgba(int r, int g, int b, int a)
// {
// 	return (r << 24 | g << 16 | b << 8 | a);
// }

// t_u32	mlx_get_pixel(mlx_image_t *img, t_u32 x, t_u32 y)
// {
// 	t_u8	*pixel;

// 	if (x > image->width || y > img->height)
// 		return (0xFF000000);
//   pixel = img->pixels + (y * img->width + x) * PIXEL_SIZE;
//   return (get_rgba(*(pixel), *(pixel + 1), *(pixel + 2), *(pixel + 3)));
// }
// */
