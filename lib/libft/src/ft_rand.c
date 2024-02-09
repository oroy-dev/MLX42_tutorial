/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:59:36 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/13 21:03:02 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
Linear congruential generator (LCG)
'seed' initialized using the adress of local variable 'var'
provides a different starting point between each program run
the seed is updated at each call to ft_rand
*/
int	ft_rand(int min, int max)
{
	static unsigned long	seed;
	int						var;
	int						range;
	int						random_int;

	if (seed == 0)
		seed = (unsigned long)&var;
	seed = seed * LCG_MULT + LCG_INCR;
	range = max - min + 1;
	random_int = ((seed / LCG_DIV) % range) + min;
	return (random_int);
}

/* testing ft_rand

int	main(int argc, char **argv)
{
    int random_int;
    int min;
    int max;

    if (argc != 3)
    {
        ft_printf("Usage: %s min max\n", argv[0]);
        return (0);
    }
    min = ft_atoi(argv[1]);
    max = ft_atoi(argv[2]);
    random_int = ft_rand(min, max);
    ft_printf("Randomized value : %d\n", random_int);
    return (0);
}
*/

/* loop to test even distribution (edit result throug cli)

int main(void)
{
	int	i;
	int	random;
	
	i = 0;
	while (i < 500)
	{
		random = ft_rand(0, 100);
		ft_printf("%d\n", random);
		i++;
	}
	return (0);
}
*/
