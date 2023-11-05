#include "main.h"

/**
 * get_word_count - Returns the number of words in a string.
 * @str: string
 * @delim: the delimeter to split on
 *
 * Return: Number of words
 */
int get_word_count(const char *str, const char *delim)
{
	int in_word = 0; /* flag to track if we are in a word or not */
	int word_count = 0;
	char *tmp_delim = (char *)delim;

	if (str == NULL || *str == '\0')
		return (0);

	if (delim == NULL)
		tmp_delim = " \t";

	while (*str)
	{
		if (_strchr(tmp_delim, *str))
		{
			in_word = 0; /* not in a word, reset flag */
		}
		else if (!in_word)
		{
			in_word = 1;  /* found the start of a new word */
			word_count++; /* count word */
		}
		str++;
	}

	return (word_count);
}

/**
 * _strchr - locate character in string
 * @s: the string
 * @c: the character to search
 *
 * Description: The _strchr() function returns a pointer to the first
 * occurrence of the character @c in the string @s.
 *
 * Return: a pointer to the matched character or NULL if the character
 * is not found
 */
char *_strchr(const char *s, const char c)
{
	char *tmp_s = (char *)s;

	/* handle empty string */
	if (s == NULL)
		return (NULL);

	while (*tmp_s != '\0')
	{
		if (*tmp_s == c)
			return (tmp_s); /* match found */
		tmp_s++;
	}
	/* return a pointer to the null byte if 'c' is a null byte. */
	if (c == '\0')
		return (tmp_s);

	return (NULL); /* no match found or end of string - return NULL */
}

/**
 * _strstr - locate a substring
 * @haystack: string
 * @needle: substring
 *
 * Description: The strstr() function finds the first occurrence of the
 * substring @needle in the string @haystack. The terminating null bytes('\\0')
 * are not compared.
 *
 * Return: return a pointer to the beginning of the located substring,
 * or NULL if the substring is not found.
 */
char *_strstr(const char *haystack, const char *needle)
{
	size_t i, j;

	for (i = 0; haystack[i]; i++)
	{
		j = 0;
		/* keep searching so long as characters in both strings are equal */
		while (haystack[i + j] == needle[j] && needle[j])
			j++;

		/* end of substring reached - means there was a full match */
		if (needle[j] == '\0')
		{
			return ((char *)&haystack[i]);
		}
	}
	return (NULL); /* no match found */
}

/**
 * _strdup - Duplicates a string.
 * @str: string to duplicate
 *
 * Description: The _strdup() function returns a pointer to a newly allocated
 * space in memory, which contains a copy of the string @str. Memory for the
 * new string is obtained with malloc() and can be freed with free()
 *
 * Return: A pointer to the duplicated string, NULL if it fails
 */
char *_strdup(const char *str)
{
	char *dup_str;
	size_t i = 0;

	if (str == NULL)
		return (NULL); /* handle invalid string */

	dup_str = malloc(_strlen(str) + 1);

	if (dup_str == NULL)
		return (NULL);

	/* duplicate string - a copy process */
	while (str[i])
	{
		dup_str[i] = str[i];
		i++;
	}
	dup_str[i] = '\0';

	return (dup_str);
}

/**
 * _strcpy - copy a string
 * @dest: destination buffer
 * @src: source buffer
 *
 * Description: copies the string pointed to by @src, including the terminating
 * null byte ('\\0'), to the buffer pointed to by @dest. The destination string
 * @dest must be large enough to receive the copy.
 *
 * Return: a pointer to the @dest string
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
