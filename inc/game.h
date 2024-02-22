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
# include <math.h>

# define ESC 256

# define PIXEL_SIZE		4

# define TUTO_WIDTH		640
# define TUTO_HEIGHT	360
# define SELECTION_LEN	2
# define DIFFICULTY_LEN	3

enum game_status
{
	MENU,
	PLAYING
};

enum menu_selection
{
	SELECT_PLAY,
	SELECT_DIFFICULTY
};

enum game_difficulty
{
	EASY,
	MEDIUM,
	HARD
};

typedef struct s_animation
{
	t_list		*frames;
	int			frame_speed; //speed of animation in milliseconds
	double		accumulator; //to control the speed
	int			current_frame_num; //which frame is selected
	int			mirrored;
	long int	updated_at; //when was the last update
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
}		sprite_slice;

typedef struct s_sprite
{
	mlx_image_t	*sprite_img;
	mlx_t		*mlx;
}	t_sprite;

typedef struct s_game
{
	mlx_t					*mlx;
	mlx_image_t				*menu_bg_img;
	mlx_image_t				*game_bg_img;
	mlx_image_t				*foreground;
	mlx_image_t				*difficulty_imgs[DIFFICULTY_LEN];
	t_animation				*select_animation;
	enum menu_selection		menu_selection;
	enum game_status		game_status;
	enum game_difficulty	game_difficulty;
}							t_game;

void	draw_pixel(mlx_image_t *img, int x, int y, int color);
int		get_pixel(mlx_image_t* img, t_u32 x, t_u32 y);
void	put_img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y);


t_sprite	new_sprite(char *filepath, mlx_t *mlx);
void		destroy_sprite(t_sprite *s);
t_animation	*slice_sprite(t_sprite *s, sprite_slice slice, int mirrored, int frames, int frame_speed);
void		update_animation(t_animation *a, double delta_time);


void	error(void);


#endif
