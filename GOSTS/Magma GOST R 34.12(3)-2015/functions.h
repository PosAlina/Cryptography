#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "consts.h"

void add_vector(const vect a, const vect b, vect output);
void add_block(const vector a, const vector b, vector output);
void add_vector_32(const vector a, const vector b, vector output);
size_t get_size(FILE *f);
size_t get_new_size(size_t size, int numb_proc);
void procedure(uint8_t *P, size_t new_size, size_t size);
void anti_procedure(uint8_t *P, size_t &size);
void get_key(char *argv, main_key key, int gost);
void get_IV_32(char **argv, int v, vect IV);
void get_IV_64(char **argv, int v, vector IV);

#endif
