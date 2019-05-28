#include "utils.h"

void	*memcpy(void *dest, const void *src, int n)
{
	int		i = -1;
	char		*dest_cpy;
	const char	*src_cpy;

	dest_cpy = (char *)dest;
	src_cpy = (const char *)src;
	while(++i < n)
		dest_cpy[i] = src_cpy[i];
	return (dest);
}

int	strlen(char * str)
{
	unsigned int	i = 0;
	while (str && str[i])
		i++;
	return i;
}
