#include "bits.h"

/**
 * test_num_of_trailing_zeros - tests the function that implements the logic
 * to return the number of trailing zeros in an integer value
 *
 * @array_of_numbers: an array of numbers to pass to the function
 */
void test_num_of_trailing_zeros(size_t *array_of_numbers)
{
	int correct_value[SIZE] = {3, 0, 2, 9, 0, 1, 0, 0, 1, 0};
	int i;

	printf("Testing the num_of_trailing_zeros() function ... ");

	for (i = 0; i < SIZE; i++)
	{
		assert(num_of_trailing_zeros((int)array_of_numbers[i]) == correct_value[i]);
	}

	puts("PASSED");
}
