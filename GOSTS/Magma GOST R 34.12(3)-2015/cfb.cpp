#include "functions.h"
#include "magma.h"
#include "consts.h"

using namespace std;

void C_cfb(vector block, vector R) {
  vector gamma;
  memcpy(gamma, R, BLOCK_SIZE);
  E(gamma, gamma);
  add_block(block, gamma, block);
  memcpy(R, block, BLOCK_SIZE);
}

void cfb_encrypt(FILE *input, FILE *output, vector IV, size_t size) {
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
    C_cfb(block, R);
	if (!(fwrite(block, 1, BLOCK_SIZE, output)))
      throw runtime_error("unreadable file");
  }
  free(input_buffer);
}

void cfb_decrypt(FILE *input, FILE *output, vector IV, size_t size) {
  vector R;
  memcpy(R, IV, 8);
  size_t block_number = size / BLOCK_SIZE;
  vector block;
  uint8_t *output_buffer = (uint8_t*) malloc (size);
  for(size_t i = 0; i < block_number; i++) {
	if (!(fread(block, 1, BLOCK_SIZE, input)))
      throw runtime_error("unreadable file");
    C_cfb(block, R);
	memcpy(output_buffer + i * BLOCK_SIZE, block, BLOCK_SIZE);
  }
  anti_procedure(output_buffer, size);
  if (!(fwrite(output_buffer, 1, size, output)))
    throw runtime_error("unreadable file");
  free(output_buffer);
}

void cfb(FILE *input, FILE *output, vector IV, int action, size_t size) {
  if (action == F_E)
	cfb_encrypt(input, output, IV, size);
  else
	cfb_decrypt(input, output, IV, size);
}
