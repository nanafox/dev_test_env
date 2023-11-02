#ifndef MAIN_H
#define MAIN_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* macros */

#define BUFF_SIZE 1024
#define SPACE ' '

/* function macros */

#define isspace(c) ((c) == SPACE)

/* function prototypes */

size_t _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strchr(const char *s, const char c);
int _strcmp(const char *s1, const char *s2);
char **_strtok(const char *str, const char *delim);
char *_strncpy(char *dest, const char *src, size_t n);
int get_word_count(const char *str, const char *delim);
char *handle_comments(char *command);

/* memory handlers */

void free_str(char **str_array);
char *new_word(const char *str, int start, int end);
void *_memcpy(void *dest, const void *src, size_t n);
void *_realloc(void *old_mem_blk, size_t old_size, size_t new_size);

/* a safer way to deallocate dynamic memory */
void _free(void **ptr);
#define safe_free(p) _free((void **)&(p)) /* _free's frontend */

/* a custom implementation of the getline function */
ssize_t _getline(char **lineptr, size_t *n, int fd);

#endif /* MAIN_H */
