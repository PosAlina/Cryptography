#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "afine_functions.h"

wchar_t *Decrypt(wchar_t *text, unsigned int a, unsigned int b, int language) {
  Coprime(language, a);
  unsigned int y, cap, index = 0;
  while (text[index] != L'\0') {
    cap = Capital(language, text[index]);
    y = Number_in_alphabet(language, text[index]);
    if (y != 100)
      text[index] = Return_Alphabet(language, cap, y, a, b);
    index++;
  }
  return text;
}
