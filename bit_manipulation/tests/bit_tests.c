#include "../bits.h"

/**
 * main - driver code to test your functions
 *
 * Return: 0
 */
int main(void)
{
	size_t numbers[SIZE] = {8, 3, 4, 1024, 129, 78, 23, 1, 10, 0};
	size_t turn_off[SIZE] = {12, 515, 5, 1024, 137, 334, 23, 17, 11, 128};

	puts("======================== TEST CASES ========================\n");

	test_is_power_of_2(numbers);
	test_num_of_trailing_zeros(numbers);
	test_count_set_bits(numbers);
	test_right_most_set_bit(numbers);
	test_turn_me_on(numbers);
	test_turn_me_off(turn_off);

	puts("\nAll test cases passed");

	return (0);
}
