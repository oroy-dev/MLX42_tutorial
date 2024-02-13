/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 20:10:35 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/12 20:10:03 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_sprite	new_sprite(char *filepath, mlx_t *mlx)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	// load png
	texture = mlx_load_png(filepath);
	if (!texture)
		error();

	// create image from png texture
	img = mlx_texture_to_image(mlx, texture);
	if (!img)
		error();
	
	mlx_delete_texture(texture);
	
	return ((t_sprite){img, mlx});
}

void	destroy_sprite(t_sprite *s)
{
	if (!s)
		error();
	mlx_delete_image(s->mlx, s->sprite_img);
}

static void	add_frame(t_animation *a, t_sprite *s, sprite_slice slice, int mirrored)
{
	mlx_image_t	*frame;
	int			i;
	int			j;

	frame = mlx_new_image(s->mlx, slice.width - (slice.padding_x * 2), \
	slice.height - (slice.padding_y * 2));
	if (!frame)
		error();
	i = 0;
	while (i < slice.height - (slice.padding_y * 2))
	{
		j = 0;
		while (j < slice.width - (slice.padding_x * 2))
		{
			if (mirrored)
				draw_pixel(frame, (slice.height - (slice.padding_y * 2)) - j - 1, i, \
				get_pixel(s->sprite_img, slice.x + j + slice.padding_x, slice.y + i + slice.padding_y));
			else
				draw_pixel(frame, j, i, \
				get_pixel(s->sprite_img, slice.x + j + slice.padding_x, slice.y + i + slice.padding_y));
			j++;
		}
		i++;
	}
	ft_lstadd_back(&a->frames, ft_lstnew(frame));
}

t_animation	*slice_sprite(t_sprite *s, sprite_slice slice, int mirrored, int frames, int delay)
{
	t_animation	*a;
	int			i;

	a = (t_animation*)ft_calloc(sizeof(t_animation), 1);
	if (!a)
		error();
	*a = (t_animation){NULL, delay, 0, 0, mirrored, 0};
	i = 0;
	while (i < frames)
	{
		add_frame(a, s, slice, mirrored);
		slice.x += slice.width;
		if ((t_u32)slice.x >= s->sprite_img->width)
		{
			slice.x = 0;
			slice.y += slice.height;
		}
		i++;
	}
	return (a);
}

// 

/*
the delta time will tell us how much time has passed
between the last frame and the current frame.
Accumulating the time that passes between each frame
will let us know when we are supposed to change the animation.
This method is very good,
because the animation speed is not dependant on the fps
(or the performance) of the program.
The animation will have a fixed frame speed
and will change it's frame at that speed.
*/
void	update_animation(t_animation *a, double delta_time)
{
	if (a)
	{
		a->accumulator += delta_time * 1000;
		if (a->accumulator > a->frame_speed)
		{
			a->accumulator -= a->frame_speed;
			a->current_frame_num++;
			a->current_frame_num %= ft_lstsize(a->frames);
		}
	}
}

/*
The accumulation is counted in miliseconds,
just as our frame speed.
We multiply in order to be in the same order of magnitude (miliseconds),
since the delta time is given in seconds.
Remember 1 seconds = 1000 miliseconds.
*/
