#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "vigenere_functions.h"

wchar_t *Decrypt(wchar_t *text, unsigned int text_length, const wchar_t *keyword, unsigned int keyword_length, int language) {
  unsigned int index, x, y, cap, keysymbol = 0;
  for (index = 0; index < text_length; index++) {
    cap = Capital(language, text[index]);
    x = Number_in_alphabet(language, keyword[keysymbol % keyword_length]);
    keysymbol++;
    y = Column_in_row(language, text[index], x);
    if (y == 100) {
      keysymbol--;
      continue;
    }
    text[index] = Alphabet(language, cap, y);
  }
  return text;
}
