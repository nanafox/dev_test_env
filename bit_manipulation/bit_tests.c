#include "bits.h"

int main(void)
{
	size_t numbers[SIZE] = {8, 3, 4, 1024, 129, 78, 23, 1, 10, 6};

	puts("======================== TEST CASES ========================\n");

	test_is_power_of_2(numbers);
	test_right_most_set_bit(numbers);
	test_turn_me_on(numbers);
	test_turn_me_off(numbers);

	puts("\nAll test cases passed");

	return (0);
}
