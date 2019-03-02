#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "globals.h"
#include "polybius_encrypt.h"
#include "polybius_decrypt.h"

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

unsigned int Language(FILE *input) {
  if (feof(input))
    throw ERROR_LANGUAGE;
  wchar_t symbol = getwc(input);
  symbol = Empty_symbol(input, symbol);
  wchar_t *language = (wchar_t *) malloc (2 * sizeof(wchar_t));
  unsigned int sz, lang = 2, string_length = 0;
  while (While_symbol(input, symbol)) {
    language[string_length] = symbol;
    sz = 2 * sizeof(wchar_t) * (string_length + 1);
    language = (wchar_t *) realloc (language, sz);
    symbol = getwc(input);
    string_length++;
  }
  language[string_length] = L'\0';
  if (!wcscmp(language, L"english"))
    lang = 0;
  if (!wcscmp(language, L"russian"))
    lang = 1;
  free(language);
  if (lang == 2)
    throw ERROR_LANGUAGE;
  return lang;
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

int Odd_number(FILE *input) {
  if (feof(input))
    throw ERROR_NUMBER;
  wchar_t symbol = getwc(input);
  symbol = Empty_symbol(input, symbol);
  if ((feof(input)) && (!isdigit(symbol)))
    throw ERROR_NUMBER;
  wchar_t *str_odd_number = (wchar_t *) malloc (2 * sizeof(wchar_t));
  unsigned int sz, string_length = 0;
  int odd_number = 1;
  if (symbol == L'-') {
    odd_number = -1;
    symbol = getwc(input);
  }
  while (While_symbol(input, symbol)) {
    str_odd_number[string_length] = symbol;
    sz = 2 * sizeof(wchar_t) * (string_length + 2);
    str_odd_number = (wchar_t *) realloc (str_odd_number, sz);
    symbol = getwc(input);
    string_length++;
  }
  str_odd_number[string_length] = L'\0';
  odd_number *= wtoi(str_odd_number);
  free(str_odd_number);
  if (!(odd_number % 2))
    throw ERROR_FORMAT_NUMBER;
  return odd_number;
}

wchar_t *Text(FILE *input) {
  wchar_t *text = (wchar_t *) malloc (2 * sizeof(wchar_t));
  unsigned sz, string_length = 0;
  if (!feof(input)) {
    wchar_t symbol = getwc(input);
    symbol = Empty_symbol(input, symbol);
    while (While_symbol(input, symbol)) {
      text[string_length] = symbol;
	  sz = 2 * sizeof(wchar_t) * (string_length + 2);
      text = (wchar_t *) realloc (text, sz);
      symbol = getwc(input);
      string_length++;
    }
  }
  text[string_length] = L'\0';
  return text;
}

void Main_program(unsigned int action, unsigned int output,
                 wchar_t *text, int odd_number,
                 unsigned int language) {
  if (!action) {
    if (output)
      wcout << L"Encrypted message: ";
    if (wcslen(text))
      wcout << Encrypt(text, language, odd_number) << endl;
  }
  else {
    if (output)
      wcout << L"Decrypted message: ";
    if (wcslen(text))
      wcout << Decrypt(text, language, odd_number) << endl;
  }
}
	
void Exception_output(const int exception) {
  switch(exception) {
    case ERROR_ACTION:
      cerr << "Error: Please, input action \"encrypt/decrypt\"." << endl;
      break;
    case ERROR_LANGUAGE:
      cerr << "Error: Please, input language \"english/russian\"." << endl;
      break;
    case ERROR_NUMBER:
      cerr << "Error: Please, input number." << endl;
      break;
    case ERROR_FORMAT_NUMBER:
      cerr << "Error: Please, input odd number." << endl;
      break;
    case ERROR_FORMAT_TEXT:
      cerr << "Error: Please, input not empty text on inputed language." << endl;
      break;
    case ERROR_SYMBOL:
      cerr << "Error: Unknown symbols in the text." << endl;
      break;
    default:
      cerr << "Unknown error." << endl;
      break;
  }
}
	
unsigned int Capital(unsigned int language, wchar_t symbol) {
  unsigned int x, y;
  if (!language) {
      for (x = 0; x < 5; x++)
        for (y = 0; y < 5; y++) {
          if (symbol == en_alphabet[x][y])
            return 0;
          if (symbol == en_capital_alphabet[x][y])
            return 1;
        }
  }
  else {
    for (x = 0; x < 6; x++)
      for (y = 0; y < 6; y++) {
        if (symbol == ru_alphabet[x][y])
          return 0;
        if (symbol == ru_capital_alphabet[x][y])
          return 1;
      }
  }
  return 0;
}

wchar_t Change_register(unsigned int language, wchar_t symbol) {
  unsigned int x, y;
  if (!language) {
    for (x = 0; x < 5; x++)
      for (y = 0; y < 5; y++) {
        if (symbol == en_alphabet[x][y])
          return en_capital_alphabet[x][y];
        if (symbol == en_capital_alphabet[x][y])
          return en_alphabet[x][y];
    }
  }
  else {
    for (x = 0; x < 6; x++)
      for (y = 0; y < 6; y++) {
        if (symbol == ru_alphabet[x][y])
          return ru_capital_alphabet[x][y];
        if (symbol == ru_capital_alphabet[x][y])
          return ru_alphabet[x][y];
    }
  }
  return symbol;
}

unsigned int Number_in_english(wchar_t symbol) {
  unsigned int x, y;
  if (symbol == L'j')
    symbol = L'i';
  if (symbol == L'J')
    symbol = L'I';
      for (x = 0; x < 5; x++)
        for (y = 0; y < 5; y++)
          if ((symbol == en_alphabet[x][y]) || (symbol == en_capital_alphabet[x][y]))
            return (x + 1) * 10 + y + 1;
  throw ERROR_SYMBOL;
}

unsigned int Number_in_russian(wchar_t symbol) {
  unsigned int x, y;
  for (x = 0; x < 6; x++)
    for (y = 0; y < 6; y++)
      if ((symbol == ru_alphabet[x][y]) || (symbol == ru_capital_alphabet[x][y]))
        return (x + 1) * 10 + y + 1;
  throw ERROR_SYMBOL;
}

unsigned int Number_in_alphabet(unsigned int language, wchar_t symbol) {
  if (!language)
    return Number_in_english(symbol);
  else
    return Number_in_russian(symbol);
}

wchar_t Symbol(unsigned int cap, unsigned int language, unsigned int x, unsigned int y) {
  if (!language) {
    if (cap)
      return en_capital_alphabet[x - 1][y - 1];
    else
      return en_alphabet[x - 1][y - 1];
  }
  else {
    if (cap)
      return ru_capital_alphabet[x - 1][y - 1];
    else
      return ru_alphabet[x - 1][y - 1];
  }
}
