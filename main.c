#include "include/cub3d.h"

int	main(int argc, char **argv)
{
	/* Validate arguments and file */
	if (!validate_arguments(argc, argv))
		return (EXIT_FAILURE);
	
	printf("File validation successful: %s\n", argv[1]);
	
	/* TODO: Parse the .cub file */
	/* TODO: Initialize graphics */
	/* TODO: Start game loop */
	
	return (EXIT_SUCCESS);
}
