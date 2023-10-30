#include "../bits.h"

/**
 * test_is_power_of_2 - tests the function that implements the logic
 * to check whether a number is a power of 2 or not
 *
 * @array_of_numbers: an array of numbers to pass to the function
 */
void test_is_power_of_2(size_t *array_of_numbers)
{
	int i;
	int correct_values[SIZE] = {1, 0, 1, 1, 0, 0, 0, 1, 0, 0};

	printf("Testing the is_power_of_2() function ... ");

	for (i = 0; i < SIZE; i++)
	{
		assert(is_power_of_2(array_of_numbers[i]) == correct_values[i]);
	}

	puts("PASSED");
}
