#include "bits.h"

void test_is_power_of_2(size_t *array_of_numbers)
{
	size_t i;
	size_t correct_values[SIZE] = {1, 0, 1, 1, 0, 0, 0, 1, 0, 0};

	printf("Testing is_power_of_2() function ... ");

	for (i = 0; i < SIZE; i++)
	{
		assert(is_power_of_2(array_of_numbers[i]) == correct_values[i]);
	}

	puts("PASSED");
}
