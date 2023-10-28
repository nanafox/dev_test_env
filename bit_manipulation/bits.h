#ifndef BITS_H
#define BITS_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

#define BOUNDARY 63
#define SIZE 10

/* functions to brainstorm and write code for */
int is_power_of_2(size_t n);
int right_most_set_bit(size_t n);
int count_set_bits(size_t n);
int turn_me_on(size_t *n, size_t index);
int turn_me_off(size_t *n, size_t index);
int num_of_trailing_zeros(size_t n);

/* test case function prototypes */
void test_is_power_of_2(size_t *array_of_numbers);
void test_right_most_set_bit(size_t *array_of_numbers);
void test_count_set_bits(size_t *array_of_numbers);
void test_turn_me_on(size_t *array_of_numbers);
void test_turn_me_off(size_t *array_of_numbers);
void test_num_of_trailing_zeros(size_t *array_of_numbers);

#endif /* BITS_H */
