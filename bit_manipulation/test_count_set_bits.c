#include "bits.h"

/**
 * test_count_set_bits - tests the function that implements the logic
 * to return the number of bits set in an integer value
 *
 * @array_of_numbers: an array of numbers to pass to the function
 */
void test_count_set_bits(size_t *array_of_numbers)
{
	int correct_value[SIZE] = {1, 2, 1, 1, 2, 4, 5, 1, 2, 0};
	int i;

	printf("Testing the count_set_bits() function ... ");

	for (i = 0; i < SIZE; i++)
	{
		assert(count_set_bits((int)array_of_numbers[i]) == correct_value[i]);
	}

	puts("PASSED");
}
