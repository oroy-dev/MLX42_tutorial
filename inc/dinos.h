/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinos.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:58:06 by cdumais           #+#    #+#             */
/*   Updated: 2024/02/22 18:00:26 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DINOS_H
# define DINOS_H

#include <stdbool.h>
#include "MLX42.h"
#include "libft.h"

enum dino_action
{
	IDLE = 1,
	RUNNING = 2,
	EXPLODING = 3,
	JUMPING = 4
};

typedef struct s_dino
{
	int					x;
	int					y;
	enum dino_action	dino_action;
	bool				mirrored;
	t_list				*actions; //list of all the dino actions, 8 total animations
}						t_dino;

void	destroy_dino(void *ptr);
t_dino	*create_dino(char *filepath, mlx_t *mlx);

#endif
