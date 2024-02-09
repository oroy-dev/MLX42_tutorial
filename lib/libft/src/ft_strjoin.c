/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 12:51:35 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/13 13:51:08 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/*
Allocates with malloc, returns new null-terminated string
result of the concatenation of s1 and s2.
If the allocation fails the function returns NULL
**must be freed*
*/
char	*ft_strjoin(const char *s1, const char *s2)
{
	char		*joined;
	char		*start;
	const char	*end1;
	const char	*end2;

	if (!s2)
		return (NULL);
	end1 = s1;
	end2 = s2;
	while (end1 && *end1)
		end1++;
	while (*end2)
		end2++;
	joined = (char *)malloc((end1 - s1) + (end2 - s2) + 1);
	if (!joined)
		return (NULL);
	start = joined;
	while (s1 && *s1)
		*start++ = *s1++;
	while (*s2)
		*start++ = *s2++;
	*start = '\0';
	return (joined);
}

/* using libft's functions

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*joined;
	char	*start;
	size_t	len_s1;
	size_t	len_s2;

	if (!s2)
		return (NULL);
	if (s1)
		len_s1 = ft_strlen(s1);
	else
		len_s1 = 0;
	len_s2 = ft_strlen(s2);
	joined = ft_calloc(len_s1 + len_s2 + 1, sizeof(char));
	if (!joined)
		return (NULL);
	start = joined;
	if (s1)
		ft_strlcpy(start, s1, len_s1 + 1);
	start += len_s1;
	ft_strlcpy(start, s2, len_s2 + 1);
	return (joined);
}
*/

/*
joins s1 and s2 with delimiter in between.
if s1 or delimiter is NULL, it will return NULL.
if s2 is NULL, it will only join s1 and delimiter.
** must be freed *
*/
char	*ft_strjoin_with(char *s1, char *delimiter, char *s2)
{
	char	*first_join;
	char	*joined;

	if (!s1 || !delimiter)
		return (NULL);
	first_join = ft_strjoin(s1, delimiter);
	if (!first_join)
		return (NULL);
	if (s2)
	{
		joined = ft_strjoin(first_join, s2);
		free(first_join);
		if (!joined)
			return (NULL);
	}
	else
	{
		joined = first_join;
	}
	return (joined);
}

/*
joins all strings passed as parameters.
the last parameter must be NULL.
** must be freed *
** if the last param is not NULL... *
tmp->	while ((next = va_arg(args, char *)) != NULL)
*** WIP **
*/
// char	*ft_vstrjoin(char *first, ...)
// {
// 	va_list	args;
// 	char	*str;
// 	char	*next;
// 	int		total_length;

// 	str = ft_strdup(first);
// 	total_length = ft_strlen(str);
// 	va_start(args, first);
// 	next = va_arg(args, char *);
// 	while (next != NULL)
// 	{
// 		total_length += ft_strlen(next);
// 		// str = ft_recalloc(str, total_length + 1);
// 		str = ft_calloc(1, total_length + 1);
// 		ft_strlcat(str, next, total_length + 1);
// 		next = (va_arg(args, char *));
// 	}
// 	va_end(args);
// 	return (str);
// }

/* main to test 'ft_vstrjoin' with all argv

int	main(int argc, char **argv)
{
	int		i;
	char	*joined;

	if (argc < 2)
	{
		ft_printf("Usage: %s <string> [string] [string] ...\n", argv[0]);
		return (0);
	}
	i = 1;
	joined = NULL;
	while (argv[i] != NULL)
	{
		joined = ft_vstrjoin(joined, argv[i], NULL);
		i++;
	}
	ft_printf("Joined string -> [%s]\n", joined);
	free(joined);
	return (0);
}

*/
