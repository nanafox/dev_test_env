#include "bits.h"

/**
 * right_most_set_bit - returns the right-most set bit in a number
 * (efficient)
 * @n: the number to find right most bit of
 *
 * Return: the index (starting from zero) of right-most set bit in @n,
 * else -1 if @n is 0 (zero)
 */
int right_most_set_bit(size_t n)
{
	int mask, index;

	if (n == 0)
	{
		return (-1);
	}

	mask = n & (n - 1);
	index = (int)(log(n ^ (mask)) / log(2));

	return (index);
}
