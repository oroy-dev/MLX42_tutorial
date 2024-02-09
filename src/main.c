/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:43:54 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/08 19:56:39 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define WWIDTH 640
#define HHEIGHT 360

static void	error(void)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR);
	exit(FAILURE);
}

t_cub	init_cub(char *title)
{
	t_cub	cub;
	
	ft_memset(&cub, 0, sizeof(cub));

	// start mlx
	cub.mlx = mlx_init(WWIDTH, HHEIGHT, title, FALSE);
	if (!cub.mlx)
		error();
	
	// try to load the file
	cub.bg_texture = mlx_load_png("./img/menu_bg.png");
	if (!cub.bg_texture)
		error();
	
	// convert the texture to a displayable image
	cub.bg_img = mlx_texture_to_image(cub.mlx, cub.bg_texture);
	if (!cub.bg_img)
		error();

	// display the image
	if (mlx_image_to_window(cub.mlx, cub.bg_img, 0, 0) < SUCCESS)
		error();

	return (cub);
}

void	cub_loop(t_cub *cub)
{
	// hooks

	mlx_loop(cub->mlx);
}

int main(void)
{
	t_cub	cub;

	cub = init_cub("Color Game");

	cub_loop(&cub);

	mlx_delete_image(cub.mlx, cub.bg_img);
	mlx_delete_texture(cub.bg_texture);
	mlx_terminate(cub.mlx);
	return (0);
}
