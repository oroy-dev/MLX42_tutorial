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
# include "animation.h"
# include "dinos.h"
# include <math.h>

# define ESC 256

# define PIXEL_SIZE		4

# define TUTO_WIDTH		640
# define TUTO_HEIGHT	360
# define SELECTION_LEN	2
# define DIFFICULTY_LEN	3
# define COLOR_SELECTION_LEN 3

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

enum color_selection
{
	RED_SELECT,
	GREEN_SELECT,
	BLUE_SELECT
};

typedef struct s_game
{
	mlx_t					*mlx;
	mlx_image_t				*menu_bg_img;
	mlx_image_t				*game_bg_img;
	mlx_image_t				*foreground;
	mlx_image_t				*difficulty_imgs[DIFFICULTY_LEN];
	t_animation				*select_animation;
	t_animation				*small_select_animation;
	t_list					*random_dinos;
	enum menu_selection		menu_selection;
	enum game_status		game_status;
	enum game_difficulty	game_difficulty;
	enum color_selection	color_selection;
	int						selected_colors[COLOR_SELECTION_LEN];
}							t_game;

void	draw_pixel(mlx_image_t *img, int x, int y, int color);
int		get_pixel(mlx_image_t* img, t_u32 x, t_u32 y);
void	put_img_to_img(mlx_image_t *dst, mlx_image_t *src, int x, int y);

void	error(void);
void	bait(void *ptr);


#endif
