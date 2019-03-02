#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "globals.h"
#include "afine_functions.h"
#include "afine_encrypt.h"
#include "afine_decrypt.h"
#include "afine_break.h"

using namespace std;

int main (int argc, char **argv) {
  if (argc < 2) {
    cerr << "Error: Please, input the name of correct file\nas an input parameter to this program." << endl;
    exit(1);
  }

  setlocale(LC_ALL, "");
  int language = 0;
  int argc_index = 1;
  int output = 0;
  int i;
  if (argc > 2) {
    if (!strcmp(argv[1], "-lang-russian")) {
      language = 1;
      argc_index = 2;
    }
    else {
      if (!strcmp(argv[1], "-lang")) {
        if (!strcmp(argv[2], "-russian")) {
          language = 1;
          argc_index = 3;
        }
        else {
          cerr << "Error: flag for language" << endl;
          exit(1);
        }
      }
      else {
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
  for (i = 1; i < argc; i++)
    if (!strcmp(argv[i], "-output"))
      output = 1;
  FILE *input = fopen(argv[argc_index], "r");
  if (input == NULL) {
    cerr << "Error: Input file is not open." << endl;
    exit(1);
  }

  wchar_t *action = (wchar_t *) malloc (2 * sizeof(wchar_t));
  wchar_t *str_a = (wchar_t *) malloc (2 * sizeof(wchar_t));
  wchar_t *str_b = (wchar_t *) malloc (2 * sizeof(wchar_t));
  wchar_t *clear = (wchar_t *) malloc (6 * sizeof(wchar_t));
  wchar_t *cipher = (wchar_t *) malloc (6 * sizeof(wchar_t));
  wchar_t *text = (wchar_t *) malloc (2 * sizeof(wchar_t));

  try {
//Read action
    if (feof(input))
      throw ERROR_ACTION;

    wchar_t symbol = getwc(input);
    symbol = Empty_symbol(input, symbol);
    unsigned int string_length = 0;
    while ((symbol != L' ') && (symbol != L'\t') && (symbol != L'\0') && (symbol != L'\n') && ((int)symbol != 10) && (!feof(input))) {
      if (symbol == L'\r') {
        if (feof(input))
           break;
        symbol = getwc(input);
        if (symbol == L'\n')
          break;
      }
      action[string_length] = symbol;
      action = (wchar_t *) realloc (action, 2 * sizeof(wchar_t) * (string_length + 2));
      symbol = getwc(input);
      string_length++;
    }
    action[string_length] = L'\0';
    symbol = Empty_symbol(input, symbol);
    
    if (feof(input))
      throw ERROR_ACTION;

    if ((wcscmp(action, L"encrypt")) && (wcscmp(action, L"decrypt")) && (wcscmp(action, L"break")))
      throw ERROR_ACTION;

    string_length = 0;
    if (!wcscmp(action, L"break")) {
    //Read clear text
      clear[0] = symbol;
      if (feof(input))
        throw ERROR_TEXT;
      symbol = getwc(input);
      symbol = Empty_symbol(input, symbol);
      if (feof(input))
        throw ERROR_TEXT;
      clear[1] = symbol;
      symbol = getwc(input);
      symbol = Empty_symbol(input, symbol);
      clear[2] = L'\0';

    //Read cyphertext
      if (feof(input))
        throw ERROR_TEXT;

      cipher[0] = symbol;
      if (feof(input))
        throw ERROR_TEXT;
      symbol = getwc(input);
      symbol = Empty_symbol(input, symbol);
      if (feof(input))
        throw ERROR_TEXT;
      cipher[1] = symbol;
      symbol = getwc(input);
      symbol = Empty_symbol(input, symbol);
      cipher[2] = L'\0';

    //Read text
      if (feof(input))
        throw ERROR_TEXT;

      text[string_length] = symbol;
      text = (wchar_t *) realloc (text, 2 * sizeof(wchar_t) * (string_length + 2));
      string_length++;
      while (!feof(input)) {
        symbol = fgetwc(input);
        text[string_length] = symbol;
        text = (wchar_t *) realloc (text, 2 * sizeof(wchar_t) * (string_length + 2));
        string_length++;
      }
      text[string_length] = L'\0';

      if (output)
        wcout << L"Hacked message: ";
      wcout << Break(clear, cipher, text, language);
    }
    else {//Encrypt/decrypt
    //Read a - multiplier
      if (feof(input))
        throw ERROR_MULTIPLIER;

      unsigned int number = Len(language);
      string_length = 0;
      int znak = 0;
      if (symbol == L'-') {
        znak = 1;
        if (feof(input))
          throw ERROR_MULTIPLIER;
        symbol = getwc(input);
        symbol = Empty_symbol(input, symbol);
      }
      while ((isdigit(symbol)) && (symbol != L' ') && (symbol != L'\t') && (symbol != L'\0') && (symbol != L'\n') && ((int)symbol != 10) && (!feof(input))) {
        if (symbol == L'\r') {
          if (feof(input))
             break;
          symbol = getwc(input);
          if (symbol == L'\n')
            break;
        }
        str_a[string_length] = symbol;
        str_a = (wchar_t *) realloc (str_a, 2 * sizeof(wchar_t) * (string_length + 2));
        symbol = getwc(input);
        string_length++;
      }
      str_a[string_length] = L'\0';
      symbol = Empty_symbol(input, symbol);
      int a = wtoi(str_a);
      a %= number;
      if (znak)
        a = number - a;

    //Read b - shift
      if (feof(input))
        throw ERROR_SHIFT;

      znak = 0;
      if (symbol == L'-') {
        znak = 1;
        if (feof(input))
          throw ERROR_SHIFT;
        symbol = getwc(input);
        symbol = Empty_symbol(input, symbol);
      }
      string_length = 0;
      while ((isdigit(symbol)) && (symbol != L' ') && (symbol != L'\t') && (symbol != L'\0') && (symbol != L'\n') && ((int)symbol != 10) && (!feof(input))) {
        if (symbol == L'\r') {
          if (feof(input))
             break;
          symbol = getwc(input);
          if (symbol == L'\n')
            break;
        }
        str_b[string_length] = symbol;
        str_b = (wchar_t *) realloc (str_b, 2 * sizeof(wchar_t) * (string_length + 2));
        symbol = getwc(input);
        string_length++;
      }
      str_b[string_length] = L'\0';
      symbol = Empty_symbol(input, symbol);
      int b = wtoi(str_b);
      b %= number;
      if (znak)
        b = number - b;

    //Read text
      if (feof(input))
        throw ERROR_TEXT;

      string_length = 0;
      text[string_length] = symbol;
      text = (wchar_t *) realloc (text, 2 * sizeof(wchar_t) * (string_length + 2));
      string_length++;
      while (!feof(input)) {
        symbol = fgetwc(input);
        text[string_length] = symbol;
        text = (wchar_t *) realloc (text, 2 * sizeof(wchar_t) * (string_length + 2));
        string_length++;
      }
      text[string_length] = L'\0';
      if (!wcscmp(action, L"encrypt")) {
        if (output)
          wcout << L"Encrypted message: ";
        wcout << Encrypt(text, a, b, language);
      }
      else {
        if (output)
          wcout << L"Decrypted message: ";
        wcout << Decrypt(text, a, b, language);
      }
    }

    free(action);
    free(str_a);
    free(str_b);
    free(clear);
    free(cipher);
    fclose(input);

  } catch (const int exception) {
    free(action);
    free(str_a);
    free(str_b);
    free(clear);
    free(cipher);
    fclose(input);
    switch(exception) {
    case ERROR_ACTION:
      cerr << "Error: Please, input action \"encrypt/decrypt\"." << endl;
      break;
    case ERROR_TEXT:
      cerr << "Error: Please, input correct text." << endl;
      break;
    case ERROR_MULTIPLIER:
      cerr << "Error: Please, input correct multiplier." << endl;
      break;
    case ERROR_SHIFT:
      cerr << "Error: Please, input correct shift." << endl;
      break;
    case ERROR_COPRIME:
      cerr << "Error: multiplier is no coprime with length of alphabet." << endl;
      break;
    default:
      cerr << "Unknown error." << endl;
      break;
    }
    exit(1);
  }
  return 0;
}
