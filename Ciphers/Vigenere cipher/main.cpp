#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "globals.h"
#include "vigenere_functions.h"
#include "vigenere_encrypt.h"
#include "vigenere_decrypt.h"

using namespace std;

int main (int argc, char **argv) {
  unsigned int output, language;
  int ind_ar;
  if ((output = Arguments(argc, argv)) == 2)
	exit(1);
  setlocale(LC_ALL, "");
  if ((language = Language(argc, argv)) == 2)
    exit(1);
  if ((ind_ar = Argc_int(argc, argv)) == 0) {
    cerr << "Error: Not name of the file." << endl;
    exit(1);
  }
  FILE *input = fopen(argv[ind_ar], "r");
  if ((!ind_ar) || (input == NULL)) {
    cerr << "Error: Input file is not open." << endl;
    exit(1);
  }
  wchar_t *text = (wchar_t *) malloc (2 * sizeof(wchar_t));
  wchar_t *keyword = (wchar_t *) malloc (2 * sizeof(wchar_t));
  try {
    unsigned int action = Action(input);
    unsigned int keyword_length = Keyword_length(input);
	keyword = (wchar_t *) realloc (keyword, 2 * keyword_length * sizeof(wchar_t));
    keyword = Keyword(input, keyword_length, language);
	unsigned int text_length = Text_length(input);
	text = (wchar_t *) realloc (text, 2 * text_length * sizeof(wchar_t));
    text = Text(input, text_length, language);
    Main_program(action, output, text_length, keyword_length, language, keyword, text);
	free(keyword);
	free(text);
    fclose(input);
  } catch (const int exception) {
	free(keyword);
	free(text);
    fclose(input);
	Exception_output(exception);
    exit(1);
  }
  return 0;
}
