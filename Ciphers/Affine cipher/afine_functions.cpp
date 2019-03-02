#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "globals.h"
#include "consts.h"

using namespace std;

wchar_t Empty_symbol(FILE *input, wchar_t symbol) {
  while (((symbol == L' ') || (symbol == L'\t') || (symbol == L'\0') || (symbol == L'\n') || (symbol == L'\r') || ((int)symbol == 10) || ((int)symbol == -1)) && (!feof(input))) {
    if (symbol == L'\r') {
     symbol = getwc(input);
     if (symbol == L'\n')
       symbol = getwc(input);
     else
       continue;
    }
    else
      symbol = getwc(input);
  }
  return symbol;
}

unsigned int wtoi(wchar_t *str) {
  unsigned int number = 0;
  unsigned int i;
  for (i = 0; str[i]; ++i) {
    number *= 10;
    number += str[i] - L'0';
  }
  return number;
}

unsigned int Coprime(unsigned int language, int b) {
  int a;
  if (!language)
    a = en_length;
  else
    a = ru_length;
  while (a && b) {
    if (a >= b)
      a %= b;
    else
      b %= a;
  }
  if ((a | b) == 1)
    return 0;
  else
    throw ERROR_COPRIME;
}

unsigned int Len(int language) {
  if (!language)
    return en_length;
  else
    return ru_length;
}

unsigned int Reverse_element(unsigned int m, int n) {
  Coprime(m, n);
  unsigned int elem = 1;
  while (((n * elem) % m) != 1)
    elem++;
  return elem;
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
    for (index = 0; index < en_length; index++) {
      if (symbol == ru_alphabet[index])
        return 0;
      if (symbol == ru_capital_alphabet[index])
        return 1;
    }
  }
  return 0;
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

wchar_t Alphabet(int language, unsigned int cap, unsigned int x, unsigned int a, unsigned int b) {
  if (!language) {
    if (cap)
      return en_capital_alphabet[(a * x + b) % en_length];
    else
      return en_alphabet[(a * x + b) % en_length];
  }
  else {
    if (cap)
      return ru_capital_alphabet[(a * x + b) % ru_length];
    else
      return ru_alphabet[(a * x + b) % ru_length];
  }
}

wchar_t Return_Alphabet(int language, unsigned int cap, unsigned int y, unsigned int a, unsigned int b) {
  unsigned int number = y - b;  
  if (!language) {
    while (number % a)
      number += en_length;
    number /= a;
    if (cap)
      return en_capital_alphabet[number];
    else
      return en_alphabet[number];
  }
  else {
    while (number % a)
      number += ru_length;
    number /= a;
    if (cap)
      return ru_capital_alphabet[number];
    else
      return ru_alphabet[number];
  }
}
