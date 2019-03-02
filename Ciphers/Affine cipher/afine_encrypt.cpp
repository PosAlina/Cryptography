#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "afine_functions.h"

wchar_t *Encrypt(wchar_t *text, unsigned int a, unsigned int b, int language) {
  unsigned int x, cap, index = 0;
  while (text[index] != L'\0') {
    cap = Capital(language, text[index]);
    x = Number_in_alphabet(language, text[index]);
    if (x != 100)
      text[index] = Alphabet(language, cap, x, a, b);
    index++;
  }
  return text;
}
