#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "polybius_functions.h"

using namespace std;

wchar_t *Decrypt(wchar_t *text, unsigned int language, int odd) {
  if (odd < 0) {
    odd *= (-1);
    odd %= 2 * wcslen(text);
    odd = 2 * wcslen(text) - odd;
  }
  else
    odd %= 2 * wcslen(text);
  unsigned int odd_number = (unsigned int)odd;
  unsigned int number1, number2, first, index, i;
  int cap[wcslen(text)];
  for (i = 0; i < wcslen(text); i++)
    cap[i] = Capital(language, text[i]);
  number1 = Number_in_alphabet(language, text[0]);
  first = number1;
  for (index = 1; index < wcslen(text); index++) {
    number2 = Number_in_alphabet(language, text[index]);
    text[index] = Symbol(Capital(language, text[index]), language, number1 % 10, number2 / 10);
    number1 = number2;
  }
  number2 = first;
  text[0] = Symbol(Capital(language, text[0]), language, number1 % 10, number2 / 10);
  for (i = 0; i < odd_number / 2; i++) {
    wchar_t first_symbol = text[wcslen(text) - 1];
    for (index = wcslen(text) - 1; index > 0; index--) {
      if (cap[index] != cap[(index - 1) % wcslen(text)])
        text[index] = Change_register(language, text[(index - 1) % wcslen(text)]);
      else
        text[index] = text[(index - 1) % wcslen(text)]; 
    }
    if (cap[0] != cap[wcslen(text) - 1])
      text[0] = Change_register(language, first_symbol);
    else
      text[0] = first_symbol;
  }
  return text;
}
