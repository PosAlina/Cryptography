#ifndef CBC_H
#define CBC_H
#include "consts.h"

void C_cbc(vector block, vector R);
void cbc_encrypt(FILE *input, FILE *output, vector IV, size_t size);
void D_cbc(vector block, vector R);
void cbc_decrypt(FILE *input, FILE *output, vector IV, size_t size);
void cbc(FILE *input, FILE *output, vector IV, int action, size_t size);

#endif
