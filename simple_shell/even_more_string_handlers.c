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

/**
 * _strrchr - locate character in string (reverse)
 * @s: the string
 * @c: the character to search
 *
 * Description: The _strrchr() function returns a pointer to the last
 * occurrence of the character @c in the string @s.
 *
 * Return: a pointer to the matched character or NULL if the character
 * is not found
 */
char *_strrchr(const char *s, int c)
{
	char *tmp_s = (char *)s;
	size_t len = _strlen(tmp_s);

	/* handle empty string */
	if (s == NULL)
		return (NULL);

	while (tmp_s[--len] != '\0')
	{
		if (tmp_s[len] == c)
			return (tmp_s + len); /* match found */
	}
	/* return a pointer to the null byte if 'c' is a null byte. */
	if (c == '\0')
		return (tmp_s);

	return (NULL); /* no match found or end of string - return NULL */
}

/**
 * _strncmp - compare at most n bytes of two strings
 * @s1: the first string to be compared
 * @s2: the second string to be compared
 * @n: the maximum number of bytes to compare
 *
 * Return: 0 if the strings are equal, a negative value if s1 is less than s2,
 *         or a positive value if s1 is greater than s2
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while (*s1 == *s2 && i < n)
	{
		if (*s1 == '\0' || i + 1 == n)
		{
			return (0); /* both strings are equal or reached the end of comparison */
		}
		s1++;
		s2++;
		i++;
	}

	return ((*s1) - (*s2));
}
