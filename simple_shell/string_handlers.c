#include "main.h"

/**
 * _strtok - splits a string into words.
 * @str: The string to split
 * @delim: the delimeter to split on
 *
 * Return: a pointer to an array of strings (words) on success, NULL otherwise.
 */
char **_strtok(const char *str, const char *delim)
{
	char **str_array;
	int word_count, word_start, word_end; /* keeps track of words */
	int len, index, i;
	char *tmp_delim = (char *)delim;

	if (delim == NULL)
		tmp_delim = " ";

	word_count = get_word_count(str, tmp_delim);
	if (word_count == 0)
		return (NULL); /* no valid words */

	str_array = malloc((word_count + 1) * sizeof(char *));
	if (str_array == NULL)
		return (NULL); /* memory allocation failed */

	word_start = index = 0;
	len = _strlen(str);

	for (i = 0; i < len; i++)
	{
		if ((!_strchr(tmp_delim, str[i]) && _strchr(tmp_delim, str[i + 1])) ||
			str[i + 1] == '\0')
		{
			word_end = i + 1;
			str_array[index] = new_word(str, word_start, word_end);

			/* memory allocation for new word failed, clean up and leave */
			if (str_array[index] == NULL)
				return (free_str(str_array), NULL);
			index++;
		}
		else if (!_strchr(tmp_delim, str[i]) && !_strchr(tmp_delim, str[i + 1]))
			continue; /* still in a word, keep counting */
		else
			word_start = i + 1;
	}
	/* terminate the array */
	str_array[index] = NULL;
	return (str_array);
}

/**
 * _strcmp - compare two strings
 * @s1: string 1
 * @s2: string 2
 *
 * Return: 0 if @s1 and @s2 are equal, a negative value if @s1 is
 * less than @s2, a positive value if @s1 is greater than @s2
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return (0); /* Both strings are equal */
		}
		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * _strcat - concatenate two strings
 * @dest: destination string buffer
 * @src: source string buffer
 *
 * Description: The _strcat() function appends the @src string to the @dest
 * string, overwriting the terminating null byte ('\\0') at the end of dest,
 * and then adds a terminating null byte.
 *
 * Return: a pointer to the resulting string dest
 */
char *_strcat(char *dest, const char *src)
{
	int len, i;

	len = _strlen(dest);

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[len++] = src[i];
	}
	dest[len] = '\0';

	return (dest);
}

/**
 * _strncpy - copy a string
 * @dest: destination string buffer
 * @src: source string buffer
 * @n: number of bytes to write
 *
 * Description: Copy @n bytes from the string @s to @dest. If there is no null
 * byte among the first @n bytes of @s, the string in @dest will not be
 * null-terminated.
 *
 * Return: a pointer to the destination string @dest
 */
char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}

	while (i < n)
	{
		/* ensure exactly n bytes are written */
		dest[i] = '\0';
		i++;
	}

	return (dest);
}

/**
 * _strlen - returns the length of a string
 * @s: string
 *
 * Return: length of string
 */
size_t _strlen(const char *s)
{
	int i = 0;

	if (s == NULL)
	{
		return (0);
	}

	while (s[i] != '\0')
	{
		i++;
	}

	return (i);
}
