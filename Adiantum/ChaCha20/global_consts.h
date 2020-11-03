#pragma once
#ifndef GLOBAL_CONSTS_H
#define GLOBAL_CONSTS_H

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include "inttypes.h"

#define DATA_BYTE_SIZE 64
#define DIGEST_512_BYTE_SIZE 64
#define DIGEST_512_BIT_SIZE 512
#define DIGEST_256_BYTE_SIZE 32
#define DIGEST_256_BIT_SIZE 256

using namespace std;

//The readed data processed in this iteration and the hash
struct context {
	uint8_t data[DATA_BYTE_SIZE]; //The buffer
	size_t data_size; //Number of data in the buffer
	uint8_t digest[DIGEST_512_BYTE_SIZE]; //The hash
	size_t digest_size; //The hash length
//Constants
	uint8_t N[DIGEST_512_BYTE_SIZE];
	uint8_t Z[DIGEST_512_BYTE_SIZE];
	uint8_t CONST_512[DIGEST_512_BYTE_SIZE];
	uint8_t	CONST_ZERO[DIGEST_512_BYTE_SIZE];
};
#endif
