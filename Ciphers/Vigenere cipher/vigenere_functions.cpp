#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "globals.h"
#include "consts.h"
#include "vigenere_encrypt.h"
#include "vigenere_decrypt.h"

using namespace std;

unsigned int Arguments(int argc, char **argv) {
  if (argc < 2) {
    cerr << "Error: Please, input the name of correct file" << endl;
	cerr << "as an input parameter to this program." << endl;
    return 2;
  }
  unsigned int output = 0;
  for (int i = 1; i < argc; i++)
    if (!strcmp(argv[i], "-output")) {
      output = 1;
	  break;
	}
  return output;
}

unsigned int Language (int argc, char **argv) {
  unsigned int language = 0;
  if (argc > 2) {
    if (!strcmp(argv[1], "-lang-russian")) {
      language = 1;
    }
    else {
      if (!strcmp(argv[1], "-lang")) {
        if (!strcmp(argv[2], "-russian")) {
          language = 1;
        }
        else {
          cerr << "Error: flag for language" << endl;
          language = 2;
        }
      }
      else {
		int i;
        for (i = 1; i < argc; i++) {
          if (!strcmp(argv[i], "-lang-russian"))
          language = 1;
          else {
            if ((!strcmp(argv[i], "-lang")) && (i < (argc - 1)))
            if (!strcmp(argv[i + 1], "-russian"))
              language = 1;
          }
        }
      }
    }
  }
  return language;
}

int Argc_int(int argc, char **argv) {
  int i;
  for(i = 1; i < argc; i++) {
    if ((!strcmp(argv[i], "-lang-russian")) || (!strcmp(argv[i], "-lang-english"))
    || (!strcmp(argv[i], "-lang")) || (!strcmp(argv[i], "-russian"))
    || (!strcmp(argv[i], "-output")))
      continue;
    else
      return i;
  }
  return 0;
}

int While_symbol(FILE *input, wchar_t symbol) {
  if ((symbol != L' ') && (symbol != L'\t') && (symbol != L'\0')) {
	if ((symbol != L'\n') && ((int)symbol != 10) && (!feof(input))) {
	  if (symbol == L'\r') {
        if (feof(input))
          return 0;
        symbol = getwc(input);
        if (symbol == L'\n')
          return 0;
      }
	}
	else
	  return 0;
  }
  else
    return 0;
  return 1;
}

unsigned int Number_in_alphabet(int language, wchar_t symbol) {
  unsigned int index;
  if (!language) {
    for (index = 0; index < en_length; index++) {
      if ((symbol == en_alphabet[index]) || (symbol == en_capital_alphabet[index]))
        return index;
     }
  }
  else {
    for (index = 0; index < ru_length; index++) {
      if ((symbol == ru_alphabet[index]) || (symbol == ru_capital_alphabet[index]))
        return index;
    }
  }
  return 100;
}

wchar_t Empty_symbol(FILE *input, wchar_t symbol) {
  while (!While_symbol(input, symbol)) {
    if (feof(input))
      break;
    symbol = getwc(input);
  }
  return symbol;
}

unsigned int Action(FILE *input) {
  if (feof(input))
    throw ERROR_ACTION;
  wchar_t symbol = getwc(input);
  wchar_t *action = (wchar_t *) malloc (2 * sizeof(wchar_t));
  unsigned int sz, act = 2, string_length = 0;
  while (While_symbol(input, symbol)) {
    action[string_length] = symbol;
	sz = 2 * sizeof(wchar_t) * (string_length + 2);
    action = (wchar_t *) realloc (action, sz);
    symbol = getwc(input);
    string_length++;
  }
  action[string_length] = L'\0';
  if (!wcscmp(action, L"encrypt"))
    act = 0;
  if (!wcscmp(action, L"decrypt"))
	act = 1;
  free(action);
  if (act == 2)
    throw ERROR_ACTION;
  return act;
}

unsigned int wtoi(wchar_t *str) {
  unsigned int number = 0;
  int i;
  for (i = 0; str[i]; ++i) {
    number *= 10;
    number += str[i] - L'0';
  }
  return number;
}

unsigned int Keyword_length(FILE *input) {
  if (feof(input))
    throw ERROR_KEYWORD_LENGTH;
  wchar_t symbol = getwc(input);
  symbol = Empty_symbol(input, symbol);
  if ((feof(input)) && (!isdigit(symbol)))
    throw ERROR_KEYWORD_LENGTH;
  wchar_t *str_keyword_length = (wchar_t *) malloc (2 * sizeof(wchar_t));
  unsigned int sz, keyword_length = 1, string_length = 0;
  while (While_symbol(input, symbol)) {
    str_keyword_length[string_length] = symbol;
    sz = 2 * sizeof(wchar_t) * (string_length + 2);
    str_keyword_length = (wchar_t *) realloc (str_keyword_length, sz);
    symbol = getwc(input);
    string_length++;
  }
  str_keyword_length[string_length] = L'\0';
  keyword_length *= wtoi(str_keyword_length);
  free(str_keyword_length);
  return keyword_length;
}

wchar_t *Keyword(FILE *input, unsigned int keyword_length, int language) {
  unsigned int string_length;
  wchar_t symbol = getwc(input);
  symbol = Empty_symbol(input, symbol);
  if ((feof(input)) || (Number_in_alphabet(language, symbol) == 100))
    throw ERROR_KEYWORD;
  wchar_t *keyword = (wchar_t *) malloc (2 * sizeof(wchar_t) * (keyword_length + 1));
  keyword[0] = symbol;
  for (string_length = 1; string_length < keyword_length; string_length++) {
    if (feof(input))
      throw ERROR_KEYWORD;
    symbol = fgetwc(input);
	if (symbol == L'\r') {
	  if (feof(input))
        throw ERROR_KEYWORD;
	  symbol = getwc(input);
	}
    if ((symbol == L' ') || (symbol == L'\t') || (symbol == L'\0')
		|| (symbol == L'\n') || ((int)symbol == 10) || (feof(input))
	    || (Number_in_alphabet(language, symbol) == 100))
      throw ERROR_KEYWORD;
    keyword[string_length] = symbol;
  }
  keyword[keyword_length] = L'\0';
  while (While_symbol(input, symbol))
	symbol = getwc(input);
  return keyword;
}

unsigned int Text_length(FILE *input) {
  if (feof(input))
    throw ERROR_TEXT_LENGTH;
  wchar_t symbol = getwc(input);
  symbol = Empty_symbol(input, symbol);
  if ((feof(input)) && (!isdigit(symbol)))
    throw ERROR_TEXT_LENGTH;
  wchar_t *str_text_length = (wchar_t *) malloc (2 * sizeof(wchar_t));
  unsigned int sz, text_length = 1, string_length = 0;
  while (While_symbol(input, symbol)) {
    str_text_length[string_length] = symbol;
    sz = 2 * sizeof(wchar_t) * (string_length + 2);
    str_text_length = (wchar_t *) realloc (str_text_length, sz);
    symbol = getwc(input);
    string_length++;
  }
  str_text_length[string_length] = L'\0';
  text_length *= wtoi(str_text_length);
  free(str_text_length);
  return text_length;
}

wchar_t *Text(FILE *input, unsigned int text_length, int language) {
  unsigned int string_length;
  wchar_t symbol = getwc(input);
  symbol = Empty_symbol(input, symbol);
  if ((feof(input)) || (Number_in_alphabet(language, symbol) == 100))
    throw ERROR_TEXT;
  wchar_t *text = (wchar_t *) malloc (2 * sizeof(wchar_t) * (text_length + 1));
  text[0] = symbol;
  for (string_length = 1; string_length < text_length; string_length++) {
    if (feof(input))
      throw ERROR_TEXT;
    symbol = fgetwc(input);
    text[string_length] = symbol;
  }
  if (string_length < text_length)
    text_length = string_length;
  text[text_length] = L'\0';
  return text;
}

void Keyword_table(int language) {
  if (!language) {
    for (unsigned int x = 0; x < en_length; x++)
      for (unsigned int y = 0; y < en_length; y++) {
        en_table[x][y] = en_alphabet[(x + y) % en_length];
        en_capital_table[x][y] = en_capital_alphabet[(x + y) % en_length];
      }
  }
  else {
    for (unsigned int x = 0; x < ru_length; x++)
      for (unsigned int y = 0; y < ru_length; y++) {
        ru_table[x][y] = ru_alphabet[(x + y) % ru_length];
        ru_capital_table[x][y] = ru_capital_alphabet[(x + y) % ru_length];
      }
  }
}

void Main_program(unsigned int action, unsigned int output,
                 unsigned int text_length, unsigned int keyword_length,
                 unsigned int language, wchar_t *keyword, wchar_t *text) {
  Keyword_table(language);
  if (!action) {
    if (output)
	  wcout << L"Encrypted message: ";
	wcout << Encrypt(text, text_length, keyword, keyword_length, language) << endl;
  }
  else {
    if (output)
	  wcout << L"Decrypted message: ";
    wcout << Decrypt(text, text_length, keyword, keyword_length, language) << endl;
  }
}

void Exception_output(const int exception) {
  switch(exception) {
    case ERROR_ACTION:
      cerr << "Error: Please, input action \"encrypt/decrypt\"." << endl;
      break;
    case ERROR_KEYWORD_LENGTH:
      cerr << "Error: Please, input correct length of the keyword." << endl;
      break;
    case ERROR_KEYWORD:
      cerr << "Error: Please, input correct keyword." << endl;
      break;
    case ERROR_TEXT_LENGTH:
      cerr << "Error: Please, input correct length of the text." << endl;
      break;
    case ERROR_TEXT:
      cerr << "Error: Please, input correct text." << endl;
      break;
    case ERROR_SYMBOL:
      cerr << "Error: Unknown symbols in the text." << endl;
      break;
    default:
      cerr << "Unknown error." << endl;
      break;
  }
}

unsigned int Capital(int language, wchar_t symbol) {
  unsigned int index;
  if (!language) {
    for (index = 0; index < en_length; index++) {
      if (symbol == en_alphabet[index])
        return 0;
      if (symbol == en_capital_alphabet[index])
        return 1;
    }
  }
  else {
    for (index = 0; index < ru_length; index++) {
      if (symbol == ru_alphabet[index])
        return 0;
      if (symbol == ru_capital_alphabet[index])
        return 1;
    }
  }
  return 0;
}



wchar_t Table(int language, unsigned int capital, unsigned int row, unsigned int column) {
  if (!language) {
    if (capital)
      return en_capital_table[row][column];
    else
      return en_table[row][column];
  }
  else {
    if (capital)
      return ru_capital_table[row][column];
    else
      return ru_table[row][column];
  }
}

unsigned int Column_in_row(int language, wchar_t symbol, unsigned int row) {
  unsigned int index;
  if (!language) {
    for (index = 0; index < en_length; index++) {
      if ((en_table[row][index] == symbol) || (en_capital_table[row][index] == symbol))
        return index;
    }
  }
  else {
    for (index = 0; index < ru_length; index++) {
      if ((ru_table[row][index] == symbol) || (ru_capital_table[row][index] == symbol))
        return index;
    }
  }
  return 100;
}

wchar_t Alphabet(int language, unsigned int capital, unsigned int index) {
  if (!language) {
    if (capital)
      return en_capital_alphabet[index];
    else
      return en_alphabet[index];
  }
  else {
    if (capital)
      return ru_capital_alphabet[index];
    else
      return ru_alphabet[index];
  }
}
