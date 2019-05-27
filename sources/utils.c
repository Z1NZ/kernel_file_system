#include "utils.h"

void	*memcpy(void *dest, const void *src, uint16 n)
{
	size_t		i = -1;
	char		*dest_cpy;
	const char	*src_cpy;

	dest_cpy = (char *)dest;
	src_cpy = (const char *)src;
	while(++i < n)
		dest[i] = src[i];
	return (dest);
}
