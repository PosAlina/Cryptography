#ifndef CONSTS_H
#define CONSTS_H
#include <stdint.h>
#include <stdlib.h>
#include <cstring>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <typeinfo>

#define F_GOST 1
#define F_ACTION 2
#define F_K 3
#define F_V 4
#define F_I 5
#define F_O 6

#define F_ECB 1
#define F_CTR 2
#define F_OFB 3
#define F_CBC 4
#define F_CFB 5
#define F_MAC 6

#define F_E 1
#define F_D 2

#define BLOCK_SIZE 8
#define KEY_SIZE 32
#define BUF_SIZE 1024
#define B_N 0x000000000000001b

typedef uint8_t vector[BLOCK_SIZE];
typedef uint8_t vect[4];
typedef vect keys[KEY_SIZE];
typedef uint8_t main_key[KEY_SIZE];

#endif
