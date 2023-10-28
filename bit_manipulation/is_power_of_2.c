#include "bits.h"

/**
 * is_power_of_2 - checks whether an unsigned integer n is a power of 2
 * @n: the number to check
 *
 * Return: 1 if @n is a power of 2, 0 otherwise
 */
int is_power_of_2(size_t n)
{
	if (n == 0)
	{
		return (0); /* zero (0) is not a power of 2 */
	}

	return ((n & (n - 1)) == 0);
}
