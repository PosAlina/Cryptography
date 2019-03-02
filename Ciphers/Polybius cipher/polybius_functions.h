#ifndef FUNCTIONS_H
#define FUNCTIONS_H

unsigned int Arguments(int, char **);
int While_symbol(FILE *, wchar_t);
wchar_t Empty_symbol(FILE *, wchar_t);
unsigned int Action(FILE *);
unsigned int Language(FILE *);
unsigned int wtoi(wchar_t *);
int Odd_number(FILE *);
wchar_t *Text(FILE *);
void Main_program(unsigned int, unsigned int, wchar_t *,
                 int, unsigned int);
void Exception_output(const int exception);
unsigned int Capital(unsigned int, wchar_t);
wchar_t Change_register(unsigned int, wchar_t);
unsigned int Number_in_alphabet(unsigned int, wchar_t);
unsigned int Number_in_english(wchar_t);
unsigned int Number_in_russian(wchar_t);
wchar_t Symbol(unsigned int, unsigned int, unsigned int, unsigned int);

#endif
