#include "bits.h"

/**
 * test_right_most_set_bit - tests the function that implements the logic
 * to return the right most set bit in an integer value
 *
 * @array_of_numbers: an array of numbers to pass to the function
 */
void test_right_most_set_bit(size_t *array_of_numbers)
{
	size_t correct_value[SIZE] = {4, 1, 2, 10, 1, 2, 1, 1, 2, 2};
	size_t i;

	printf("Testing thre")
	for (i = 0; i < SIZE; i++)
	{
		assert(right_most_set_bit(array_of_numbers[i]) == correct_value[i]);
	}
}
