#include "consts.h"
#include "functions.h"
#include "magma.h"

using namespace std;

void mac_key(vector K1, vector K2, vector R) {
  vector zero;
  for(size_t i = 0; i < BLOCK_SIZE; i++)
    zero[i] = 0x00;
  E(zero, R);
  if (R[0] & 0x80) {
    *K1 = ((*R) & 0xfffffffffffffffe) + B_N;
    if (K1[0] & 0x80)
      *K2 = ((*K1) & 0xfffffffffffffffe) + B_N;
    else
      *K2 = (*K1) & 0xfffffffffffffffe;
  }
  else {
    *K1 = (*R) & 0xfffffffffffffffe;
    if (K1[0] & 0x80)
      *K2 = ((*K1) & 0xfffffffffffffffe) + B_N;
    else
      *K2 = (*K1) & 0xfffffffffffffffe;
  }
}

void C_mac(vector block, vector K_, vector C, int flag_mac) {
  add_block(block, C, C);
  E(C, C);
  if (!flag_mac) {
	add_block(block, C, block);
	add_block(block, K_, block);
	E(block, block);
  }
}

void mac(FILE *input, FILE *output, size_t size) {
  vector K1, K2, R, C;
  for (size_t i = 0; i < BLOCK_SIZE; i ++)
    C[i] = 0x00;
  size_t new_size = get_new_size(size, 3);
  mac_key(K1, K2, R);
  uint8_t *input_buffer = (uint8_t*) malloc (size);
  if (!(fread(input_buffer, 1, size, input)))
    throw runtime_error("unreadable file");
  if (size != new_size)
    procedure(input_buffer, new_size, size);
  size_t block_number = new_size / BLOCK_SIZE;
  vector block;
  for(size_t i = 0; i < block_number; i++) {
	memcpy(block, input_buffer + i * BLOCK_SIZE, BLOCK_SIZE);
    if ((i == (block_number - 1)) && (size != new_size))
	  C_mac(block, K2, C, (block_number - i - 1));
    else
	  C_mac(block, K1, C, (block_number - i - 1));
  }
  if (!(fwrite(block, 1, BLOCK_SIZE, output)))
    throw runtime_error("unreadable file");
  free(input_buffer);
}
