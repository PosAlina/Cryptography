#include "hash.h"
#include "hash_consts.h"

// Initialization of all known fields with zeros and setting the hash size
void init(struct context *ctx, uint8_t *data, unsigned digest_size) {
	ctx->digest_size = digest_size;
	for (size_t i = 0; i < DIGEST_512_BYTE_SIZE; ++i) {
 		ctx->N[i] = 0x00;
		ctx->Z[i] = 0x00;
		ctx->CONST_512[i] = 0x00;
		ctx->CONST_ZERO[i] = 0x00;
	}
	ctx->CONST_512[DIGEST_512_BYTE_SIZE - 2] = 0x02;
	if (digest_size == DIGEST_256_BIT_SIZE)
		for (size_t i = 0; i < DIGEST_512_BYTE_SIZE; ++i)
			ctx->digest[i] = 0x01;
	else
		for (size_t i = 0; i < DIGEST_512_BYTE_SIZE; ++i)
			ctx->digest[i] = 0x00;
}

// Rewrite new data in the non-empty structure
void update(struct context *ctx, uint8_t *data, size_t data_size) {
	while (data_size > 0) {
		size_t len = DATA_BYTE_SIZE - ctx->data_size; // Free space
		if (len > data_size) // If free part of structure more than data
			len = data_size;
		data_size -= len; // These data did not fit in the structure
		memcpy(ctx->data + ctx->data_size, data, len);
		data += len; // The data rest
		ctx->data_size += len; // The new data lengthes
		if (ctx->data_size == DATA_BYTE_SIZE) { // New data fill in all
			swap(ctx->data, DIGEST_512_BYTE_SIZE);
			g_N(ctx->N, ctx->digest, ctx->data);
			X_512(ctx->N, ctx->CONST_512, ctx->N);
			X_512(ctx->Z, ctx->data, ctx->Z);
			ctx->data_size = 0; // Reset the used data
		}
	}
}

//Save hash in the buffer
void finish(struct context *ctx, uint8_t *digest){
	padding(ctx->data, ctx->data_size);
	g_N(ctx->N, ctx->digest, ctx->data);
	size_t data_size_512 = ctx->data_size << 3;
	ctx->CONST_512[DIGEST_512_BYTE_SIZE - 1] = data_size_512 & 0xff;
	ctx->CONST_512[DIGEST_512_BYTE_SIZE - 2] = (data_size_512 >> 8) & 0xff;
	X_512(ctx->N, ctx->CONST_512, ctx->N);
	X_512(ctx->Z, ctx->data, ctx->Z);
	g_N(ctx->CONST_ZERO, ctx->digest, ctx->N);
	g_N(ctx->CONST_ZERO, ctx->digest, ctx->Z);
	swap(ctx->digest, DIGEST_512_BYTE_SIZE);
	if (ctx->digest_size == DIGEST_256_BIT_SIZE)
		memcpy(digest, ctx->digest + DIGEST_256_BYTE_SIZE, DIGEST_256_BYTE_SIZE);
	else
		memcpy(digest, ctx->digest, DIGEST_512_BYTE_SIZE);
}

void padding(uint8_t *data, size_t data_size) {
	if (data_size < DIGEST_512_BYTE_SIZE) {
		swap(data, data_size);
		for (int i = DIGEST_512_BYTE_SIZE - 1; i >= DIGEST_512_BYTE_SIZE - (int)data_size; --i)
			data[i] = data[i - DIGEST_512_BYTE_SIZE + (int)data_size];
		data[DIGEST_512_BYTE_SIZE - data_size - 1] = 0x01; //First uint8_t after the data end
		for (int i = 0; i < DIGEST_512_BYTE_SIZE - (int)data_size - 1; i++)
			data[i] = 0x00;
	}
}

void g_N(uint8_t *N, uint8_t *h, uint8_t *m) {
	uint8_t output[DIGEST_512_BYTE_SIZE];
	uint8_t out[DIGEST_512_BYTE_SIZE];
	X(h, N, output);
	S(output);
	P(output);
	L(output);
	E(output, m, out);
	X(out, h, out);
	X(out, m, h);
}
 
void X_512(uint8_t *a, uint8_t *b, uint8_t *output) {
	size_t a_ = 0;
	for (int i = DIGEST_512_BYTE_SIZE - 1; i >= 0; --i) {
		a_ = a[i] + b[i] + (a_ >> 8);
		output[i] = a_ & 0xff;
	}
}

// k + a (mod 2)
void X(const uint8_t *k, const uint8_t *a, uint8_t *output) {
	for (int i = 0; i < DIGEST_512_BYTE_SIZE; i++)
		output[i] = k[i] ^ a[i];
}

// Work with Pi_
void S(uint8_t *a) {
	for (size_t i = 0; i < DIGEST_512_BYTE_SIZE; ++i) a[i] = Pi_[a[i]];
}

// Work with Tau_
void P(uint8_t *a) {
	uint8_t permutation[DIGEST_512_BYTE_SIZE];
	for (size_t i = 0; i < DIGEST_512_BYTE_SIZE; ++i) permutation[i] = a[Tau_[i]];
	memcpy(a, permutation, DIGEST_512_BYTE_SIZE);
}

// *A
void L(uint8_t *c) {
	for (size_t i = 0; i < 8; i++) {
		uint64_t a = 0;
		for (size_t j = 0; j < 8; j++)
			for (size_t k = 0; k < 8; k++)
				if (c[i * 8 + j] & (1 << (7 - k)))
					a ^= A_[j * 8 + k];
		for (size_t j = 0; j < 8; j++)
			c[i * 8 + j] = (a & (0xffffffffffffffff << ((7 - j) * 8))) >> (7 - j) * 8;
	}
}

// Encryption
void E(uint8_t *K, uint8_t *m, uint8_t *output) {
	X(m, K, output);
	for (size_t i = 0; i < 12; ++i) {
		S(output);
		P(output);
		L(output);
		K_(K, i);
		X(output, K, output);
	}
}

// Create key
void K_(uint8_t *K, size_t m) {
	X(K, C_[m], K);
	S(K);
	P(K);
	L(K);
}

void swap(uint8_t *data, size_t data_size) {
	uint8_t byte;
	for (size_t i = 0; i < (data_size / 2); i++) {
		byte = data[i];
		data[i] = data[data_size - i - 1];
		data[data_size - i - 1] = byte;
	}
}
