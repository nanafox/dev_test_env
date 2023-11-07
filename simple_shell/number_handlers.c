#include "main.h"

/**
 * _itoa - convert integer to string
 *
 * @n: the integer to convert
 * @s: a char array to hold the conversion
 */
void _itoa(size_t n, char *s)
{
	int i = 0;

	do {
		s[i++] = n % 10 + '0'; /* get next digit */
	} while ((n /= 10) > 0);

	s[i] = '\0';

	_reverse(s, i);
}

/**
 * _reverse - reverse string in place
 *
 * @buffer: string to reverse
 * @len: length of the string
 */
void _reverse(char *buffer, size_t len)
{
	size_t i, mid;
	char c;

	if (!buffer)
		return; /* invalid string, nothing to do here */
	mid = len / 2;

	for (i = 0; i < mid; i++)
	{
		c = buffer[i];

		/* swap values */
		buffer[i] = buffer[len - i - 1];
		buffer[len - i - 1] = c;
	}
}
