#include "libft/libft.h"

void	free(void *ptr)
{
	UNUSED(ptr);
	ft_putstr("free called!\n");
}

void	*malloc(size_t size)
{
	UNUSED(size);
	ft_putstr("malloc called!\n");
	return 0;
}

void	*realloc(void *ptr, size_t size)
{
	UNUSED(ptr);
	UNUSED(size);
	ft_putstr("realloc called!\n");
	return 0;
}
