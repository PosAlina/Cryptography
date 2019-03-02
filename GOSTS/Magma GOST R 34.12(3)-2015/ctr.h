#ifndef CTR_H
#define CTR_H
#include "consts.h"

void inc_R(vector R);
void C_ctr(vector block, vector R);
void ctr(FILE *input, FILE *output, vector IV, size_t size) ;

#endif
