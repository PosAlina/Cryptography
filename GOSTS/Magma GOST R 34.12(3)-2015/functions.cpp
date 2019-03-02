#include "consts.h"

using namespace std;

void add_vector(const vect a, const vect b, vect output) {
  for (int i = 0; i < 4; i++)
    output[i] = a[i]^b[i];
}

void add_block(const vector a, const vector b, vector output) {
  for (int i = 0; i < BLOCK_SIZE; i++)
    output[i] = a[i]^b[i];
}

void add_vector_32(const vect a, const vect b, vect output) {
  unsigned a_ = 0;
  for (int i = 3; i >= 0; i--) {
    a_ = a[i] + b[i] + (a_ >> 8);
    output[i] = a_ & 0xff;
  }
}

size_t get_size(FILE *f) {
  size_t size;
  fseek(f, 0, SEEK_END);
  size = ftell(f);
  fseek(f, 0, SEEK_SET);
  return size;
}

size_t get_new_size(size_t size, int numb_proc) {
  if ((numb_proc == 3) && (!(size % BLOCK_SIZE)))
    return size;
  return (size + (BLOCK_SIZE - (size % BLOCK_SIZE)) % 8);
}

void procedure(uint8_t *P, size_t new_size, size_t size) {
  P = (uint8_t*)realloc(P, new_size);
  P[size] = 0x80;
  for(size_t i = size + 1; i < new_size; i++)
    P[i] = 0x00;
}

void anti_procedure(uint8_t *P, size_t &size) {
  size_t i = size;
  while(P[i] == 0x00) {
	if ((size - i) > 8)
	  return;
	i--;
  }
  if (!(size - i))
	return;
  if (P[i] == 0x80)
	size = i - 1;
}

void get_key(char *argv, main_key key, int gost) {
  for (size_t i = 0; i < KEY_SIZE; i++)
    key[i] = 0x00;
  FILE *key_file = fopen(argv, "rb");
    size_t size = get_size(key_file);
  if (!key_file)
	throw runtime_error("error name of key file");
  if (gost == F_MAC) {
    if (size > (KEY_SIZE))
      size = KEY_SIZE;
    if (!(fread(key, 1, size, key_file)))
      throw runtime_error("unreadable key file");
  }
  else {
    if (size != (KEY_SIZE))
      throw out_of_range("key in file");
    if (!(fread(key, 1, KEY_SIZE, key_file)))
      throw runtime_error("unreadable key file");
  }
  fclose(key_file);
}

void get_IV_32(char **argv, int v, vect IV) {
  if (!v) {
    IV = 0;
	return;
  }
  FILE *IV_file = fopen(argv[v], "rb");
  if (!IV_file)
	throw runtime_error("error name of IV file");
  if (get_size(IV_file) != 4)
	throw out_of_range("IV in file");
  if (!(fread(IV, 1, 4, IV_file)))
    throw runtime_error("unreadable file");
  fclose(IV_file);
}

void get_IV_64(char **argv, int v, vector IV) {
  if (!v) {
    IV = 0;
	return;
  }
  FILE *IV_file = fopen(argv[v], "rb");
  if (!IV_file)
	throw runtime_error("error name of IV file");
  if (get_size(IV_file) != 8)
	throw out_of_range("IV in file");
  if (!(fread(IV, 1, 8, IV_file)))
    throw runtime_error("unreadable file");
  fclose(IV_file);
}


