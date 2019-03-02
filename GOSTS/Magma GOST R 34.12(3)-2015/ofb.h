#ifndef OFB_H
#define OFB_H
#include "consts.h"

void C_ofb(vector block, vector R);
void ofb(FILE *input, FILE *output, vector IV, size_t size);

#endif
