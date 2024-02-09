/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:12:52 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/10 23:16:34 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_max(int this, int that)
{
	if (this > that)
		return (this);
	else
		return (that);
}

size_t	ft_zmax(size_t this, size_t that)
{
	if (this > that)
		return (this);
	else
		return (that);
}
