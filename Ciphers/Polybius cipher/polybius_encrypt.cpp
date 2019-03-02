#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "polybius_functions.h"

using namespace std;

wchar_t *Encrypt(wchar_t *text, unsigned int language, int odd) {
  odd %= (2 * wcslen(text));
  if (odd < 0)
	odd += 2 * wcslen(text);
  unsigned int odd_number = (unsigned int)odd;
  unsigned int number1, number2, index, i;
  int cap[wcslen(text)];
  for (i = 0; i < wcslen(text); i++)
    cap[i] = Capital(language, text[i]);
  number1 = Number_in_alphabet(language, text[odd_number / 2]);
  for (index = (odd_number / 2) + 1; index < wcslen(text); index++) {
    number2 = Number_in_alphabet(language, text[index]);
    text[index] = Symbol(Capital(language, text[index]), language, number1 % 10, number2 / 10);
    number1 = number2;
  }
  for (index = 0; index <= (odd_number / 2); index++) {
    number2 = Number_in_alphabet(language, text[index]);
    text[index] = Symbol(Capital(language, text[index]), language, number1 % 10, number2 / 10);
    number1 = number2;
  }
  for (index = 0; index < (odd_number / 2) + 1; index++) {
    wchar_t first_symbol = text[0];
    for (i = 0; i < wcslen(text); i++) {
      if (cap[i] != cap[(i + 1) % wcslen(text)])
        text[i] = Change_register(language, text[(i + 1) % wcslen(text)]);
      else
        text[i] = text[(i + 1) % wcslen(text)];
    }
   if (cap[wcslen(text) - 1] != cap[0])
     text[wcslen(text) - 1] = Change_register(language, first_symbol);
    else
      text[wcslen(text) - 1] = first_symbol;
  }
  return text;
}
