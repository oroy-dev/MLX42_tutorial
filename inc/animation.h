/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 19:22:06 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/25 19:28:55 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include "libft.h"
# include "MLX42.h"

typedef struct s_animation
{
	t_list		*frames;
	int			frame_speed; //speed of animation in milliseconds
	double		accumulator; //to control the speed
	int			current_frame_num; //which frame is selected
	int			mirrored;
	long int	updated_at; //when was the last update
	long int	frame_count;
}				t_animation;

typedef struct sprite_splice
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	padding_x;
	int	padding_y;
}		sprite_slice;

typedef struct s_sprite
{
	mlx_image_t	*sprite_img;
	mlx_t		*mlx;
}				t_sprite;


t_sprite	new_sprite(char *filepath, mlx_t *mlx);
void		destroy_sprite(t_sprite *s);
t_animation	*slice_sprite(t_sprite *s, sprite_slice slice, int mirrored, int frames, int frame_speed);
void		update_animation(t_animation *a, double delta_time);

#endif
