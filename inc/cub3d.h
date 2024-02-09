/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:41:52 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/08 19:49:58 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "MLX42.h"
# include "utils.h"
# include <math.h>

typedef struct s_point
{
	float	x;
	float	y;
}			t_point;

typedef struct s_cub
{
	mlx_t			*mlx;
	mlx_texture_t	*bg_texture; //background texture
	mlx_image_t		*bg_img; //background image

}				t_cub;



// pixels.c
// 
void		draw_pixel(mlx_image_t *img, int x, int y, int color);
void		draw_line(mlx_image_t *img, t_point start, t_point end, int color);

#endif
