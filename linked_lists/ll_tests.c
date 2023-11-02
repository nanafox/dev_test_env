#include "node.h"
#define SIZE 10

void test_size(Node *list, size_t expected_size)
{
	assert(list_len(list) == expected_size);
}

int main(void)
{
	int numbers[SIZE] = {8, 3, 4, 1, 3, 4, 23, 1, 10, 6};
	Node *list1, *list2;
	int i;

	puts("======================== TEST CASES ========================\n");
	list1 = list2 = NULL;

	printf("Testing size of list while empty ... ");
	test_size(list1, 0);
	test_size(list2, 0);
	puts("PASSED");

	/* let's insert some nodes into list 1 */
	for (i = 0; i < SIZE; i++)
	{
		add_node(&list1, numbers[i]);
	}

	/* let's insert some nodes into list 1 */
	for (i = 0; i < SIZE - 5; i++)
	{
		append_node(&list2, numbers[i]);
	}

	printf("Testing lists after inserting nodes ... ");
	test_size(list1, 10);
	test_size(list2, 5);
	puts("PASSED");

	puts("\nAll test cases passed");

	return (0);
}
