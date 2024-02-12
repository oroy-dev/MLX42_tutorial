/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:41:52 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/12 12:42:15 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "pixels.h"
# include "utils.h"
// 
# include "MLX42.h"
# include <math.h>

typedef struct s_cub
{
	mlx_t			*mlx;
	mlx_texture_t	*bg_texture; //background texture
	mlx_image_t		*bg_img; //background image

}	t_cub;

void		draw_line(mlx_image_t *img, t_point start, t_point end, int color);

#endif
