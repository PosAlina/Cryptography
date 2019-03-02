#ifndef MAGMA_H
#define MAGMA_H
#include "consts.h"

void expand_key(const uint8_t *key);
void destroy_key();
void t(const vect a, vect output);
void g(const vect k, const vector a, vector output);
void G(const vect k, const vector a, vector output);
void G_(const vect k, const vector a, vector output);
void E(const vector a, vector output);
void D(const vector a, vector output);

#endif
