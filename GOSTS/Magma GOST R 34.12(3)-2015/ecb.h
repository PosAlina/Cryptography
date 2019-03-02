#ifndef ECB_H
#define ECB_H

void ecb_encrypt(FILE *input, FILE *output, size_t size);
void ecb_decrypt(FILE *input, FILE *output, size_t size);
void ecb(FILE *input, FILE *output, int action, size_t size);

#endif
