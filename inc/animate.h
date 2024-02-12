/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:58:05 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/12 14:35:14 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATE_H
# define ANIMATE_H

# include "cub3d.h"
# include "libft.h"
# include "pixels.h"
# include "MLX42.h"

typedef struct s_animation
{
	t_list		*frames;
	int			frame_speed; //speed of animation in milliseconds
	double		accumulator; //to control the speed
	int			current_frame_num; //which frame is selected
	int			mirrored;
	long int	frame_count;
}	t_animation;

typedef struct sprite_splice
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	padding_x;
	int	padding_y;
}	sprite_slice;

typedef struct s_sprite
{
	mlx_image_t	*sprite_img;
	mlx_t		*mlx;
}	t_sprite;

/* SPRITES */
t_sprite	new_sprite(char *filepath, mlx_t *mlx);
t_animation	*slice_sprite(t_sprite *s, sprite_slice slice, int mirrored, int frames, int delay);
void		destroy_sprite(t_sprite *s);

#endif // ANIMATE_H
