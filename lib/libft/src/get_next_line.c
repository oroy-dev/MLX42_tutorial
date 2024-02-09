/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdumais <cdumais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:14:07 by cdumais           #+#    #+#             */
/*   Updated: 2023/11/27 11:39:43 by cdumais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	join_buffers(char **line, char *buffer)
{
	char	*temp;
	size_t	line_len;
	char	*buffer_end;

	line_len = ft_strlen(*line);
	if (ft_strlen(buffer) <= 0)
		return (0);
	buffer_end = ft_strchr(buffer, '\n');
	if (!buffer_end)
		buffer_end = ft_strchr(buffer, '\0');
	else
		buffer_end++;
	temp = *line;
	*line = ft_calloc(line_len + (buffer_end - buffer) + 1, 1);
	if (!line)
		return (0);
	ft_strlcpy(*line, temp, line_len + 1);
	ft_strlcat(*line, buffer, line_len + (buffer_end - buffer) + 1);
	ft_strlcpy(buffer, buffer_end, ft_strlen(buffer_end) + 1);
	free(temp);
	if (ft_strchr(*line, '\n'))
		return (1);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	input_buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	bytes_read = 1;
	while (bytes_read > 0 && !join_buffers(&line, input_buffer))
	{
		bytes_read = read(fd, input_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			if (line)
				free(line);
			return (NULL);
		}
		input_buffer[bytes_read] = '\0';
	}
	return (line);
}

char	*get_next_line_bonus(int fd)
{
	static char	fd_states[OPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	buffer = fd_states[fd];
	line = NULL;
	bytes_read = 1;
	while (bytes_read > 0 && !join_buffers(&line, buffer))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			if (line)
				free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
	}
	return (line);
}

// 

// static void	update_str(char **str, char *newline_pos)
// {
// 	char	*tmp;

// 	tmp = ft_strdup(newline_pos + 1);
// 	free(*str);
// 	*str = tmp;
// 	if (**str == '\0')
// 	{
// 		free(*str);
// 		*str = NULL;
// 	}
// }

// static char	*extract_line(char **str)
// {
// 	char	*line;
// 	size_t	len;
// 	char	*newline_pos;

// 	if (!*str)
// 		return (NULL);
// 	newline_pos = ft_strchr(*str, '\n');
// 	if (newline_pos)
// 	{
// 		len = newline_pos - *str;
// 		line = ft_substr(*str, 0, len);
// 		update_str(str, newline_pos);
// 	}
// 	else
// 	{
// 		line = ft_strdup(*str);
// 		free(*str);
// 		*str = NULL;
// 	}
// 	return (line);
// }

// static int	read_to_buffer(int fd, char **str, char *buffer)
// {
// 	int		bytes_read;
// 	char	*new_str;
// 	size_t	old_len;

// 	bytes_read = read(fd, buffer, BUFFER_SIZE);
// 	if (bytes_read > 0)
// 	{
// 		buffer[bytes_read] = '\0';
// 		if (*str)
// 			old_len = ft_strlen(*str);
// 		else
// 			old_len = 0;
// 		new_str = ft_recalloc(*str, old_len + bytes_read + 1);
// 		if (!new_str)
// 			return (-1);
// 		*str = new_str;
// 		ft_strlcat(*str, buffer, old_len + bytes_read + 1);
// 	}
// 	return (bytes_read);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*str = NULL;
// 	char		buffer[BUFFER_SIZE + 1];
// 	int			bytes_read;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (NULL);
// 	bytes_read = 1;
// 	while (bytes_read > 0)
// 	{
// 		if (ft_strchr(str, '\n'))
// 			break ;
// 		bytes_read = read_to_buffer(fd, &str, buffer);
// 		if (bytes_read == -1)
// 			return (NULL);
// 	}
// 	if (bytes_read < 0)
// 		return (NULL);
// 	return (extract_line(&str));
// }

/* ************************************************************************** */

/* testing get_next_line from stdin to outfile.txt in append mode

int	main(void)
{
	int		fd;
	char	*line;
	char	*output_file = "output.txt";

	fd = open(output_file, WRITE | CREATE | APPEND, 0644);
	if (fd == ERROR)
	{
		perror("Error opening file");
		return (FAILURE);
	}

	ft_printf("Enter text (CTRL+D to stop):\n");
	while (LOOP)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		ft_putendl_fd(line, fd);
		free(line);
	}
	close(fd);
	return (0);
}
*/

/* testing get_next_line on a file

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	
	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error: could not open file %s\n", argv[1]);
		return (0);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}
*/
