#include "main.h"

/**
 * _strpbrk - searches a string for any of a set of bytes
 * @s: string
 * @accept: substring
 *
 * Description: The _strpbrk() function locates the first occurrence in the
 * string @s of any of the bytes in the string @accept.
 *
 * Return: A pointer to the byte in @s that matches one of the bytes in
 * @accept, or NULL if no such byte is found.
 */
char *_strpbrk(const char *s, const char *accept)
{
	int i, j;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; accept[j]; j++)
		{
			if (s[i] == accept[j])
				return ((char *)&s[i]); /* match found*/
		}
	}
	return (NULL); /* no match found or end of string - return NULL */
}

#include "main.h"

/**
 * _strspn - get length of a prefix substring
 * @s: string
 * @accept: substring
 *
 * Description: The _strspn() function calculates the length (in bytes) of the
 * initial segment of @s which consists entirely of bytes in @accept.
 *
 * Return: The number of bytes in the initial segment of @s which
 * consist only of bytes from @accept.
 */
size_t _strspn(const char *s, const char *accept)
{
	size_t len = 0;
	int i, map[256] = {0};

	/* handle empty arguments */
	if (s == NULL || accept == NULL)
		return (0);

	/* use a hash map for efficient lookup - assume ASCII */
	for (i = 0; accept[i] != '\0'; i++)
		map[(unsigned char)accept[i]] = 1;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == SPACE) /* search till next word */
			break;
		else if (map[(unsigned char)s[i]])
			len++; /* match found, increment length */
		else
			break; /* no match found */
	}
	return (len);
}
