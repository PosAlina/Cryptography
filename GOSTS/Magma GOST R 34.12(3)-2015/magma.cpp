#include "consts.h"
#include "magma_consts.h"
#include "functions.h"

using namespace std;

void expand_key(const uint8_t *key) {
  for(size_t i = 0; i < 24; i++)
    memcpy(K[i], key + (i % 8) * 4, 4);
  for(size_t i = 24; i < 32; i++)
    memcpy(K[i], key + (31 - i) * 4, 4);
}

void destroy_key() {
  for(size_t i = 0; i < 32; i++)
    memset(K[i], 0x00, 4);
}

void t(const vect a, vect output) {
  uint8_t begin_byte, end_byte;
  for (size_t i = 0; i < 4; i++) {
    begin_byte = (a[i] & 0xf0) >> 4;
    begin_byte = Pi[7 - (i * 2)][begin_byte];
    end_byte = a[i] & 0x0f;
    end_byte = Pi[6 - i * 2][end_byte];
    output[i] = (begin_byte << 4) | end_byte;
  }
}

void g(const vect k, const vect a, vect output) {
  vect a_;
  uint32_t output_32;
  add_vector_32(a, k, a_);
  t(a_, a_);
  output_32 = a_[0];
  for(size_t i = 1; i < 4; i++)
    output_32 = (output_32 << 8) + a_[i];
  output_32 = (output_32 << 11)|(output_32 >> 21);
  for(size_t i = 0; i < 4; i++)
    output[3 - i] = output_32 >> (i * 8);
}

void G(const vect k, const vect a, vect output) {
  vect a0, a1, a_;
  for(size_t i = 0; i < 4; i++) {
    a0[i] = a[4 + i];
    a1[i] = a[i];
  }
  g(k, a0, a_);
  add_vector(a1, a_, a_);
  for(size_t i = 0; i < 4; i++) {
    a1[i] = a0[i];
    a0[i] = a_[i];
  }
  for(size_t i = 0; i < 4; i++) {
    output[i] = a1[i];
    output[4 + i] = a0[i];
  }
}

void G_(const vect k, vector a, vector output) {
  vect a0, a1, a_;
  for(size_t i = 0; i < 4; i++) {
    a0[i] = a[4 + i];
    a1[i] = a[i];
  }
  g(k, a0, a_);
  add_vector(a_, a1, a_);
  for(size_t i = 0; i < 4; i++)
    a1[i] = a_[i];
  for(size_t i = 0; i < 4; i++) {
    output[i] = a1[i];
    output[4 + i] = a0[i];
  }
}

void E(const vector a, vector output) {
  G(K[0], a, output);
  for(size_t i = 1; i < 31; i++)
    G(K[i], output, output);
  G_(K[31], output, output);
}

void D(const vector a, vector output) {
  G(K[31], a, output);
  for(size_t i = 30; i > 0; i--)
    G(K[i], output, output);
  G_(K[0], output, output);
}
