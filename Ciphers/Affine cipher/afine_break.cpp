#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "afine_functions.h"
#include "afine_decrypt.h"
#include "globals.h"

wchar_t *Break(wchar_t *clear, wchar_t *cipher, wchar_t *text, int language) {
  unsigned int X[2], Y[2], index;
  for (index = 0; index < 2; index++) {
    X[index] = Number_in_alphabet(language, clear[index]);
    Y[index] = Number_in_alphabet(language, cipher[index]);
    if ((X[index] == 100) || (Y[index] == 100))
      throw ERROR_TEXT;
  }

  unsigned int number = Len(language);
  int det = X[0] - X[1];
  if (!det)
    throw ERROR_TEXT;
  if (det < 0)
    det = number + det;
  det = Reverse_element(number, det);
  int x00 = det % number;
  int x10 = ((number - X[1]) * det) % number;
  int x01 = ((number - 1) * det) % number;
  int x11 = (X[0] * det) % number;
  int a = (x00 * Y[0] + x01 * Y[1]) % number;
  int b = (x10 * Y[0] + x11 * Y[1]) % number;
  return Decrypt(text, a, b, language);
}
