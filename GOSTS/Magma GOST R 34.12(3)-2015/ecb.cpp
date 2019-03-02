#include "functions.h"
#include "magma.h"
#include "consts.h"

using namespace std;

void ecb_encrypt(FILE *input, FILE *output, size_t size) {
  size_t new_size = get_new_size(size, 2);
  uint8_t *input_buffer = (uint8_t*) malloc (size);
  if (!(fread(input_buffer, 1, size, input)))
    throw runtime_error("unreadable input file");
  procedure(input_buffer, new_size, size);
  size_t block_number = new_size / BLOCK_SIZE;
  vector block;
  for(size_t i = 0; i < block_number; i++) {
    memcpy(block, input_buffer + i * BLOCK_SIZE, BLOCK_SIZE);
    E(block, block);
    if (!(fwrite(block, 1, BLOCK_SIZE, output)))
      throw runtime_error("unknown output file");
  }
  free(input_buffer);
}

void ecb_decrypt(FILE *input, FILE *output, size_t size) {
  size_t block_number = size / BLOCK_SIZE;
  vector block;
  uint8_t *output_buffer = (uint8_t*) malloc (size);
  for(size_t i = 0; i < block_number; i++) {
    if (!(fread(block, 1, BLOCK_SIZE, input)))
      throw runtime_error("unreadable file");
    D(block, block);
    memcpy(output_buffer + i * BLOCK_SIZE, block, BLOCK_SIZE);
  }
  anti_procedure(output_buffer, size);
  if (!(fwrite(output_buffer, 1, size, output)))
    throw runtime_error("unreadable file");
  free(output_buffer);
}

void ecb(FILE *input, FILE *output, int action, size_t size) {
  if (action == F_E)
	ecb_encrypt(input, output, size);
  else
	ecb_decrypt(input, output, size);
}
