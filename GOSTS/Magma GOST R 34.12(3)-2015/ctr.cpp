#include "functions.h"
#include "magma.h"
#include "consts.h"

using namespace std;

void inc_R(vector R) {
  size_t i = BLOCK_SIZE - 1;
  while (R[i] == 0xff) {
    R[i] = 0x00;
    i--;
  }
  R[i] += 0x01;
}

void C_ctr(vector block, vector R) {
  vector gamma;
  E(R, gamma);
  add_block(block, gamma, block);
  inc_R(R);
}

void ctr(FILE *input, FILE *output, vector IV, size_t size) {
  vector R;
  memset(R, 0x00, 8);
  memcpy(R, IV, 4);
  size_t block_number = size / BLOCK_SIZE;
  vector block;
  for(size_t i = 0; i < block_number; i++) {
    if (!(fread(block, 1, BLOCK_SIZE, input)))
      throw runtime_error("unreadable file");
    C_ctr(block, R);
	if (!(fwrite(block, 1, BLOCK_SIZE, output)))
      throw runtime_error("unreadable file");
  }
}
