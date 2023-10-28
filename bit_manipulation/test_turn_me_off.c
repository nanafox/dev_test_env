#include "bits.h"

/**
 * test_turn_me_off - tests the function that implements the logic
 * to set a bit off at a given index
 *
 * @array_of_numbers: an array of numbers to pass to the function
 */
void test_turn_me_off(size_t *array_of_numbers)
{
	int indices[SIZE] = {2, 9, 0, 67, 3, 8, 1, 4, 32, 7};
	size_t correct_values[SIZE] = {8, 3, 4, 1024, 129, 78, 23, 1, 10, 0};
	int return_values[SIZE] = {1, 1, 1, -1, 1, 1, 1, 1, 1, 1};
	int i;

	printf("Testing the turn_me_off() function ... ");

	for (i = 0; i < SIZE; i++)
	{
		assert(turn_me_off(&array_of_numbers[i], indices[i]) == return_values[i]);
		assert(array_of_numbers[i] == correct_values[i]);
	}

	puts("PASSED");
}
