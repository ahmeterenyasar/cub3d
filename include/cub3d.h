#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>

# define ERR_USAGE "Usage: ./cub3D <map.cub>"
# define ERR_FILE_EXT "Error: File must have .cub extension"
# define ERR_FILE_OPEN "Error: Cannot open file"
# define ERR_FILE_READ "Error: Cannot read file"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

/* Argument Check Function */
int		validate_arguments(int argc, char **argv);
int		validate_file_extension(char *filename);
int		validate_file_access(char *filename);
void	print_error(char *message);

#endif
