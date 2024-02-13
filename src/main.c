/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:43:54 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/12 21:48:50 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	error(void)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR);
	exit(FAILURE);
}

t_game	init_game(char *title)
{
	mlx_t			*mlx;
	mlx_texture_t	*texture;
	mlx_image_t		*img;
	mlx_image_t		*foreground_img;
	t_animation		*animation;
	t_sprite		sprite;

	// start mlx
	mlx = mlx_init(TUTO_WIDTH, TUTO_HEIGHT, title, FALSE);
	if (!mlx)
		error();

	// try to load the file
	texture = mlx_load_png("./img/menu_bg.png");
	if (!texture)
		error();

	// convert the texture to a displayable image
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		error();
	mlx_delete_texture(texture);

	// sprite and animation
	sprite = new_sprite("./img/select_sprite_sheet.png", mlx);
	animation = slice_sprite(&sprite, \
	(sprite_slice){0, 0, 128, 32, 0, 0}, FALSE, 5, 120);
	destroy_sprite(&sprite);

	// foreground
	foreground_img = mlx_new_image(mlx, TUTO_WIDTH, TUTO_HEIGHT);
	if (!foreground_img)
		error();

	return ((t_game){mlx, img, foreground_img, animation});
}

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
// 

/*
*/
void	update(void *ptr)
{
  t_game		*game;
  mlx_image_t	*frame;
  
  game = (t_game *)ptr;
  frame = (mlx_image_t *)ft_lstget(\
  game->select_animation->frames, \
  game->select_animation->current_frame_num)->content;
  if (!frame)
	error();
  put_img_to_img(game->foreground, frame, 256, 160); //coordinates of the button
  update_animation(game->select_animation, game->mlx->delta_time);
}

/* hooks and loop
*/
void	game_loop(t_game *game)
{
	mlx_loop_hook(game->mlx, update, game);
	mlx_loop(game->mlx);
}

void bait(void*ptr){(void)ptr;}; //need to understand this ?

/*
*/
int main(void)
{
	t_game	game;
	// ft_memset(&game, 0, sizeof(game));

	game = init_game("Color Game");
	
	// display the image
	if (mlx_image_to_window(game.mlx, game.bg_img, 0, 0) < SUCCESS)
		error();
	if (mlx_image_to_window(game.mlx, game.foreground, 0, 0) < SUCCESS)
		error();
 
	game_loop(&game);

	ft_lstclear(&game.select_animation->frames, bait);
	free(game.select_animation);
	mlx_delete_image(game.mlx, game.bg_img);
	mlx_delete_image(game.mlx, game.foreground);
	mlx_terminate(game.mlx);
	return (SUCCESS);
}
