#ifndef ACTIONS_H
#define ACTIONS_H
#include "consts.h"

void help(std::ostream &stream);
void cipher(char **argv, int v, FILE *input, FILE *output, int action,
            int gost, size_t size);
void gost_(FILE *input, FILE *output, int action, char **argv, int v,
           int gost, size_t size);
void output_(FILE *input, int o, int action, char **argv, int v, int gost,
             size_t size);
void action(char **argv, int gost, int action, int k, int v, int i, int o);

#endif
