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
 * @s: string
 * @c: character to search
 *
 * Description: The _strchr() function returns a pointer to the first
 * occurrence of the character @c in the string @s.
 *
 * Return: A pointer to the matched character or NULL if the character
 * is not found.
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
