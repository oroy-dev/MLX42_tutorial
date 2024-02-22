/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:43:54 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/22 18:30:54 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "dinos.h"

void	error(void)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR);
	exit(FAILURE);
}

/*
void bait(void*ptr){(void)ptr;};
*/
void	bait(void *ptr)
{
	(void)ptr;
}

/* ************************************************************************** */

mlx_image_t	*load_png(char *filepath, mlx_t *mlx)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	// try to load the file
	texture = mlx_load_png(filepath);
	if (!texture)
		error();
	
	// convert texture to a displayable image
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		error();
	if (mlx_image_to_window(mlx, img, 0, 0) == -1)
		error();
	mlx_delete_texture(texture);
	return (img);
}

/* ************************************************************************** */

t_game	init_game(char *title)
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*img2;
	mlx_image_t		*foreground_img;
	mlx_image_t		*difficulty_imgs[DIFFICULTY_LEN];
	t_animation		*animation;
	t_sprite		sprite;

	// start mlx
	mlx = mlx_init(TUTO_WIDTH, TUTO_HEIGHT, title, false);
	if (!mlx)
		error();

	// load background and menu images
	img = load_png("./img/menu_bg.png", mlx);
	img2 = load_png("./img/game_bg.png", mlx);

	// disable game background for now
	img2->instances[0].enabled = false;
	difficulty_imgs[0] = load_png("./img/menu_easy.png", mlx);
	difficulty_imgs[1] = load_png("./img/menu_medium.png", mlx);
	difficulty_imgs[2] = load_png("./img/menu_hard.png", mlx);

	// sprite and animation
	sprite = new_sprite("./img/select_sprite_sheet.png", mlx);
	animation = slice_sprite(&sprite, \
	(sprite_slice){0, 0, 128, 32, 0, 0}, FALSE, 5, 120);
	destroy_sprite(&sprite);

	// foreground
	foreground_img = mlx_new_image(mlx, TUTO_WIDTH, TUTO_HEIGHT);
	if (!foreground_img)
		error();

	return ((t_game){mlx, img, img2, foreground_img, \
	{difficulty_imgs[0], difficulty_imgs[1], difficulty_imgs[2]}, \
	animation, NULL, SELECT_PLAY, MENU, EASY});
}

/* ************************************************************************** */

void	init_dinos(t_game *game)
{
	ft_lstadd_back(&game->random_dinos, ft_lstnew(create_dino("./img/dino_doux.png", game->mlx)));
	ft_lstadd_back(&game->random_dinos, ft_lstnew(create_dino("./img/dino_mort.png", game->mlx)));
	ft_lstadd_back(&game->random_dinos, ft_lstnew(create_dino("./img/dino_tard.png", game->mlx)));
	ft_lstadd_back(&game->random_dinos, ft_lstnew(create_dino("./img/dino_vita.png", game->mlx)));
}

/* ************************************************************************** */

// to put in libft?
t_list	*ft_lstget(t_list *lst, int index)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	if (tmp == NULL)
		return (NULL);
	if (tmp->next == NULL)
		return (tmp);
	while (tmp != NULL)
	{
		if (i >= index)
			return (tmp);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

void	ft_lstiter_param(t_list *lst, void (*f)(void *, void *), void *ptr)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		f(tmp->content, ptr);
		tmp = tmp->next;
	}
}

/* ************************************************************************** */

void	update(void *ptr)
{
	static int	fps;
	static int	menu_selection_coords[SELECTION_LEN][SELECTION_LEN] = {{256, 160}, {256, 256}};
	t_game		*game;
	mlx_image_t	*frame;

	game = (t_game *)ptr;
	fps = 1000 / game->mlx->delta_time;
	printf("\e[1;1H\e[2Jfps [%d] %d\n", fps, game->game_difficulty);
	
	// clean the foreground
	ft_memset(game->foreground->pixels, 0xFF000000, \
	game->foreground->width * game->foreground->height * PIXEL_SIZE);

	if (game->game_status == MENU)
	{
		// paint the select animation on the foreground
		frame = (mlx_image_t *)ft_lstget(\
		game->select_animation->frames, \
		game->select_animation->current_frame_num)->content;
		if (!frame)
			error();
		put_img_to_img(game->foreground, frame, \
		menu_selection_coords[game->menu_selection][0], \
		menu_selection_coords[game->menu_selection][1]);
		update_animation(game->select_animation, game->mlx->delta_time); // !!

		// logic for the menu
		int	i = 0;
		while (i < DIFFICULTY_LEN)
		{
			game->difficulty_imgs[i]->instances[0].enabled = false;
			i++;
		}
		game->difficulty_imgs[game->game_difficulty]->instances[0].enabled = true;
		
		if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
			game->menu_selection = SELECT_DIFFICULTY;
		if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
			game->menu_selection = SELECT_PLAY;
	}
	
	// if (game->status == SCORE)
	// {
	// 	// update the dinos!
	// 	ft_lstiter_param(game->random_dinos, update_dinos, game);
	// }
	// else if (game->game_status == PLAYING)
	// {
	// 	// put the number (amount) of each color selection
	// }
}

void	key_update(mlx_key_data_t data, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (data.key == ESC)
		mlx_close_window(game->mlx);
	
	if (game->game_status == MENU && data.action == MLX_RELEASE)
	{
		if (data.key == MLX_KEY_ENTER)
		{
			int	i = 0;
			while (i < DIFFICULTY_LEN)
			{
				game->difficulty_imgs[i]->instances[0].enabled = false;
				i++;
			}
			game->menu_bg_img->instances[0].enabled = false;
			game->game_bg_img->instances[0].enabled = true;
			game->game_status = PLAYING;
		}
	}
	else if (game->game_status == MENU && game->menu_selection == SELECT_DIFFICULTY && data.action == MLX_PRESS)
	{
		if (data.key == MLX_KEY_LEFT)
		{
			game->game_difficulty--;
			if ((int)game->game_difficulty == -1)
			game->game_difficulty = DIFFICULTY_LEN -1;
		}
		else if (data.key == MLX_KEY_RIGHT)
		{
			game->game_difficulty++;
			game->game_difficulty %= DIFFICULTY_LEN;
		}
	}
}

int main(void)
{
	t_game	game;
	
	game = init_game("Color Game");
	init_dinos(&game);
	
	if (mlx_image_to_window(game.mlx, game.foreground, 0, 0) == -1)
		error();

	mlx_loop_hook(game.mlx, update, &game);
	mlx_key_hook(game.mlx, key_update, &game);
	mlx_loop(game.mlx);

	ft_lstclear(&game.select_animation->frames, bait);
	free(game.select_animation);

	// Free random dinos
	ft_lstclear(&game.random_dinos, destroy_dino);
	free(game.random_dinos);
	
	mlx_terminate(game.mlx);
	return (SUCCESS);
}


/*
We should use an enum to represent the dino actions, but the enum should start at 1 instead of 0.
This will help up later to gather the index for the correct animation. Each animation has a "mirrored" version.
The dino can be running to the left or to the right, each action can be to the left or right (mirrored).
In total it's 8 animations. (iddle, running, exploding, jumping, iddle mirrored, running mirrored, exploding mirrored & jumping mirrored)
*/




