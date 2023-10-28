#include "bits.h"

/**
 * count_set_bits - counts the number of set bits in a number
 * @n: the number to count set bit
 *
 * Return: the number of set bits
 */
int count_set_bits(size_t n)
{
	int count = 0;

	while (n > 0)
	{
		n &= n - 1;
		count++;
	}

	return (count);
}
