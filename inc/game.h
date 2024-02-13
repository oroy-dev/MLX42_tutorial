/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GAME.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:41:52 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/12 18:58:59 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "libft.h"
# include "MLX42.h"
# include "pixels.h"
# include <math.h>

# define TUTO_WIDTH		640
# define TUTO_HEIGHT	360

/*
2d vector (x, y)
*/
typedef struct s_point
{
	float	x;
	float	y;
}	t_point;

/* ************************************************************************** */

/* to be in animate.h
*/
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

/* ************************************************************************** */

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*bg_img; //menu background image
	mlx_image_t		*foreground;
	t_animation		*select_animation;
	// int				fps;
}	t_game;


/* animation.c
*/
t_sprite	new_sprite(char *filepath, mlx_t *mlx);
t_animation	*slice_sprite(t_sprite *s, sprite_slice slice, int mirrored, int frames, int delay);
void		destroy_sprite(t_sprite *s);
// 
void		update_animation(t_animation *a, double delta_time);


void	put_img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y);

void	error(void);

void	draw_line(mlx_image_t *img, t_point start, t_point end, int color);

#endif
