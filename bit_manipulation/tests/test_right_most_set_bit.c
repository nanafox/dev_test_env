#include "../bits.h"

/**
 * test_right_most_set_bit - tests the function that implements the logic
 * to return the right most set bit in an integer value
 *
 * @array_of_numbers: an array of numbers to pass to the function
 */
void test_right_most_set_bit(size_t *array_of_numbers)
{
	int correct_value[SIZE] = {3, 0, 2, 10, 0, 1, 0, 0, 1, -1};
	int i;

	printf("Testing the right_most_set_bit() function ... ");

	for (i = 0; i < SIZE; i++)
	{
		assert((int)right_most_set_bit(array_of_numbers[i]) == correct_value[i]);
	}

	puts("PASSED");
}
