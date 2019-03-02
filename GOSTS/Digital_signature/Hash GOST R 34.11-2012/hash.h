#pragma once
#ifndef HASH_H
#define HASH_H

#include "global_consts.h"

void init(struct context *ctx, uint8_t *data, unsigned digest_size);
void update(struct context *ctx, uint8_t *data, size_t data_size);
void finish(struct context *ctx, uint8_t *digest);
void init_H(struct context *ctx);
void last_stage(struct context *ctx, uint8_t *data);
void g_N(uint8_t *N, uint8_t *h, uint8_t *m);
void X_512(uint8_t *a, uint8_t *b, uint8_t *output);
void X(const uint8_t *k, const uint8_t *a, uint8_t *output);
void S(uint8_t *a);
void P(uint8_t *a);
void L(uint8_t *c);
void E(uint8_t *K, uint8_t *m, uint8_t *output);
void K_(uint8_t *K, size_t m);
void padding(uint8_t *data, size_t data_size);
void swap(uint8_t *data, size_t data_size);

#endif
