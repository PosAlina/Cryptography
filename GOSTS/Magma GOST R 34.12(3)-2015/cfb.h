#ifndef CFB_H
#define CFB_H
#include "consts.h"

void C_cfb(vector block, vector R);
void cfb_encrypt(FILE *input, FILE *output, vector IV, size_t size);
void cfb_decrypt(FILE *input, FILE *output, vector IV, size_t size);
void cfb(FILE *input, FILE *output, vector IV, int action, size_t size);

#endif
