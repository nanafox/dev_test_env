#include "bits.h"

/**
 * num_of_trailing_zeros - returns the number of trailing zeros
 * (efficient)
 * @n: the number to trailing zeros
 *
 * Return: the number of trailing zeros
 */
int num_of_trailing_zeros(size_t n)
{
	int mask, trailing_zeros;

    if (n == 0)
    {
        return (0);
    }

	mask = n & (n - 1);
	trailing_zeros = (int)(log(n ^ (mask)) / log(2));

	return (trailing_zeros);
}
