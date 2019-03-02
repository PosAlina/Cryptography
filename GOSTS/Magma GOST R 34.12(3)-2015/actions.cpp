#include "functions.h"
#include "magma.h"
#include "consts.h"
#include "ecb.h"
#include "ctr.h"
#include "ofb.h"
#include "cbc.h"
#include "cfb.h"
#include "mac.h"

using namespace std;

void help(ostream& stream) {
  stream << "Format output:\nmagma [-h|--help]\nmagma [--ecb|--ctr|--ofb|";
  stream << "--cbc|--cfb] {-e|-d} -k <key file> [options]\nmagma --mac -k ";
  stream << "<key file> [options]\n\n\nDescriptions of flags:\n-h | --help – ";
  stream << "вывести описание флагов в stdout.\nРежимы работы, по умолчанию ";
  stream << "используется режим ECB:\n--ecb – ГОСТ Р 34.13-2015, пункт 5.1\n";
  stream << "--ctr – ГОСТ Р 34.13-2015, пункт 5.2\n--ofb – ГОСТ Р 34.13-2015,";
  stream << "пункт 5.3\n--cbc – ГОСТ Р 34.13-2015, пункт 5.4\n--cfb – ГОСТ Р ";
  stream << "34.13-2015, пункт 5.5\n--mac – ГОСТ Р 34.13-2015, пункт 5.6\n\n";
  stream << "-e – произвести зашифрование.\n-d – произвести расшифрование.\n";
  stream << "-k <key file> – файл с бинарным ключом.\n\n[options]:\n";
  stream << "-i <input file> – входной файл. По умолчанию читать с stdin до EOF";
  stream << "-o <output file> – выходной файл. По умолчанию выводить в stdout";
  stream << "-v <iv file> – файл с бинарным значением IV.\n";
  stream << "               Используется с режимами CTR (32 бита),\n";
  stream << "               OFB, CBC, CFB (64z бита, z ∈ N).\n";
  stream << "               По умолчанию IV=0 минимально допустимой длины.\n";
  stream << "-output - дополнительный вывод.\n";
}

void cipher(char **argv, int v, FILE *input, FILE *output, int action,
            int gost, int size) {
  if (gost == F_CTR) {
	vect IV;
	get_IV_32(argv, v, IV);
	ctr(input, output, IV, size);
	return;
  }
  vector IV;
  get_IV_64(argv, v, IV);
  switch(gost) {
    case F_OFB:
	  ofb(input, output, IV, size);
	  break;
	case F_CBC:
	  cbc(input, output, IV, action, size);
	  break;
	case F_CFB:
	  cfb(input, output, IV, action, size);
  }
}

void gost_(FILE *input, FILE *output, int action, char **argv, int v,
           int gost, int size) {
  switch(gost) {
    case F_MAC:
	  mac(input, output, size);
	  break;
    case F_ECB:
    case 0:
	  ecb(input, output, action, size);
	  break;
	default:
	  cipher(argv, v, input, output, action, gost, size);
  }
}

void output_(FILE *input, int o, int action, char **argv, int v,
             int gost, int size) {
  if (o) {
    FILE *output = fopen(argv[o], "wb");
    gost_(input, output, action, argv, v, gost, size);
    fclose(output);
  }
  else {
    FILE *output = NULL; 
    output = freopen(NULL, "wb", stdout);
    gost_(input, output, action, argv, v, gost, size);
    fclose(output);
  }
}

void action(char **argv, int gost, int action, int k, int v, int i, int o) {
  main_key key;
  get_key(argv[k], key, gost);
  expand_key(key);
  if (i) {
    FILE *input = fopen(argv[i], "rb");
    output_(input, o, action, argv, v, gost, get_size(input));
    fclose(input);
  }
  else {
    FILE *input = NULL; 
    input = freopen(NULL, "rb", stdin);
    output_(input, o, action, argv, v, gost, get_size(input));
    fclose(input);
  }
  destroy_key();
}
