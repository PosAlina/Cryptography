#include "functions.h"
#include "magma.h"
#include "consts.h"

using namespace std;

void C_ofb(vector block, vector R) {
  vector gamma;
  memcpy(gamma, R, BLOCK_SIZE);
  E(gamma, gamma);
  add_block(block, gamma, block);
  memcpy(R, gamma, BLOCK_SIZE);
}

void ofb(FILE *input, FILE *output, vector IV, size_t size) {
  vector R;
  memcpy(R, IV, 8);
  size_t block_number = size / BLOCK_SIZE;
  vector block;
  for(size_t i = 0; i < block_number; i++) {
    if (!(fread(block, 1, BLOCK_SIZE, input)))
      throw runtime_error("unreadable file");
    C_ofb(block, R);
	if (!(fwrite(block, 1, BLOCK_SIZE, output)))
      throw runtime_error("unreadable file");
  }
}
