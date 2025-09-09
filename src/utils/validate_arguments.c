/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayasar <ayasar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:55:58 by ayasar            #+#    #+#             */
/*   Updated: 2025/09/09 15:33:54 by ayasar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	print_error(char *message)
{
	if (message)
		write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

int	validate_file_extension(char *filename)
{
	int	len;
	
	if (!filename)
		return (0);
	
	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	
	if (ft_strcmp(filename + len - 4, ".cub") != 0)
		return (0);
	
	return (1);
}

int	validate_file_access(char *filename)
{
	int	fd;
	
	if (!filename)
		return (0);
	
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	
	close(fd);
	return (1);
}

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		print_error(ERR_USAGE);
		return (0);
	}

	if (!validate_file_extension(argv[1]))
	{
		print_error(ERR_FILE_EXT);
		return (0);
	}

	if (!validate_file_access(argv[1]))
	{
		print_error(ERR_FILE_OPEN);
		return (0);
	}
	
	printf("File validation successful: %s\n", argv[1]);
	return (1);
}
