#include "bits.h"

/**
 * test_turn_me_on - tests the function that implements the logic
 * to set a bit on at a given index
 *
 * @array_of_numbers: an array of numbers to pass to the function
 */
void test_turn_me_on(size_t *array_of_numbers)
{
	int indices[SIZE] = {2, 9, 0, 67, 3, 8, 1, 4, 32, 7};
	size_t correct_values[SIZE] = {12, 515, 5, 1024, 137, 334, 23, 17, 11, 128};
	int return_values[SIZE] = {1, 1, 1, -1, 1, 1, 1, 1, 1, 1};
	int i;

	printf("Testing the turn_me_on() function ... ");

	for (i = 0; i < SIZE; i++)
	{
		assert(turn_me_on(&array_of_numbers[i], indices[i]) == return_values[i]);
		assert(array_of_numbers[i] == correct_values[i]);
	}

	puts("PASSED");
}
