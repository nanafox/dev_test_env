#ifndef MAIN_H
#define MAIN_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

/* macros */

#define BUFF_SIZE 1024
#define SPACE ' '
#define CMD_NOT_FOUND 127

/* function macros */

#define isspace(c) ((c) == SPACE)

/* function prototypes */

size_t _strlen(const char *s);
char *_strdup(const char *str);
char *handle_comments(char *command);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strchr(const char *s, const char c);
int _strcmp(const char *s1, const char *s2);
char **_strtok(const char *str, const char *delim);
char *_strncpy(char *dest, const char *src, size_t n);
int get_word_count(const char *str, const char *delim);
char *_strstr(const char *haystack, const char *needle);
char *_strpbrk(const char *s, const char *accept);
size_t _strspn(const char *s, const char *accept);

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

/* environment variables */

extern char **environ;

/**
 * struct _path - builds a linked list of the PATH variable in an environment
 * variable
 * @pathname: each path name in the PATH variable
 * @next: a pointer to the next node
 */
typedef struct _path
{
	char *pathname;
	struct _path *next;
} path_t;

void _printenv(void);
void free_list(path_t **head);
char *_getenv(const char *name);
path_t *build_path(path_t **head);
void print_path(path_t *list);

/* parsers and executors */

int parse_line(char *line, path_t *path_list);
int execute_command(char *pathname, char *argv[]);
int parse_and_execute(char **commands, path_t *path_list);
int handle_with_path(path_t *path_list, char **sub_command);
int print_cmd_not_found(char **sub_command, char **commands, size_t index);
int handle_file_as_input(char *filename, path_t *path_list);

#endif /* MAIN_H */
