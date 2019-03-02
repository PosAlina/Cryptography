#ifndef FUNCTIONS_H
#define FUNCTIONS_H

wchar_t Empty_symbol(FILE*, wchar_t);
unsigned int wtoi(wchar_t*);
unsigned int Len(int language);
unsigned int Reverse_element(unsigned int, int);
unsigned int Coprime(unsigned int language, int b);
unsigned int Capital(int language, wchar_t symbol);
unsigned int Number_in_alphabet(int language, wchar_t symbol);
wchar_t Alphabet(int language, unsigned int cap, unsigned int x, unsigned int a, unsigned int b);
wchar_t Return_Alphabet(int language, unsigned int cap, unsigned int y, unsigned int a, unsigned int b);

#endif
