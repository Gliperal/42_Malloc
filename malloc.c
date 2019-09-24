#include <unistd.h>

# define UNUSED(x) (void)x

void	free(void *ptr)
{
	UNUSED(ptr);
	write(1, "free called!\n", 13);
}

void	*malloc(size_t size)
{
	UNUSED(size);
	write(1, "malloc called!\n", 15);
	return 0;
}

void	*realloc(void *ptr, size_t size)
{
	UNUSED(ptr);
	UNUSED(size);
	write(1, "realloc called!\n", 16);
	return 0;
}
