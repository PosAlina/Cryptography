#include "functions.h"
#include "magma.h"
#include "consts.h"

using namespace std;

void C_cbc(vector block, vector R) {
  vector gamma;
  memcpy(gamma, R, BLOCK_SIZE);
  add_block(block, gamma, block);
  E(block, block);
  memcpy(R, block, BLOCK_SIZE);
}

void cbc_encrypt(FILE *input, FILE *output, vector IV, size_t size) {
  vector R;
  memcpy(R, IV, 8);
  size_t new_size = get_new_size(size, 2);
  uint8_t *input_buffer = (uint8_t*) malloc (size);
  if (!(fread(input_buffer, 1, size, input)))
    throw runtime_error("unreadable file");
  procedure(input_buffer, new_size, size);
  size_t block_number = new_size / BLOCK_SIZE;
  vector block;
  for(size_t i = 0; i < block_number; i++) {
	memcpy(block, input_buffer + i * BLOCK_SIZE, BLOCK_SIZE);
    C_cbc(block, R);
	if (!(fwrite(block, 1, BLOCK_SIZE, output)))
      throw runtime_error("unreadable file");
  }
  free(input_buffer);
}

void D_cbc(vector block, vector R) {
  vector gamma1, gamma2;
  memcpy(gamma1, block, BLOCK_SIZE);
  D(block, block);
  memcpy(gamma2, R, BLOCK_SIZE);
  add_block(block, gamma2, block);
  memcpy(R, gamma1, BLOCK_SIZE);
}

void cbc_decrypt(FILE *input, FILE *output, vector IV, size_t size) {
  vector R;
  memcpy(R, IV, 8);
  size_t block_number = size / BLOCK_SIZE;
  vector block;
  uint8_t *output_buffer = (uint8_t*) malloc (size);
  for(size_t i = 0; i < block_number; i++) {
	if (!(fread(block, 1, BLOCK_SIZE, input)))
      throw runtime_error("unreadable file");
    D_cbc(block, R);
	memcpy(output_buffer + i * BLOCK_SIZE, block, BLOCK_SIZE);
  }
  anti_procedure(output_buffer, size);
  if (!(fwrite(output_buffer, 1, size, output)))
    throw runtime_error("unreadable file");
  free(output_buffer);
}

void cbc(FILE *input, FILE *output, vector IV, int action, size_t size) {
  if (action == F_E)
	cbc_encrypt(input, output, IV, size);
  else
	cbc_decrypt(input, output, IV, size);
}
