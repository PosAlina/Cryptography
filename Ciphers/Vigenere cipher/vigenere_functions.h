#ifndef FUNCTIONS_H
#define FUNCTIONS_H

unsigned int Arguments(int argc, char **argv);
unsigned int Language (int argc, char **argv);
int Argc_int(int argc, char **argv);
int While_symbol(FILE *input, wchar_t symbol);
wchar_t Empty_symbol(FILE *input, wchar_t symbol);
unsigned int Action(FILE *input);
unsigned int wtoi(wchar_t *str);
unsigned int Keyword_length(FILE *input);
wchar_t *Keyword(FILE *input, unsigned int keyword_length,
                 int language);
unsigned int Text_length(FILE *input);
wchar_t *Text(FILE *input, unsigned int text_length,
              int language);
void Keyword_table(int language);
void Main_program(unsigned int action, unsigned int output,
                 unsigned int text_length, unsigned int keyword_length,
                 unsigned int language, wchar_t *keyword, wchar_t *text);
void Exception_output(const int exception);
unsigned int Capital(int language, wchar_t symbol);
unsigned int Number_in_alphabet(int language, wchar_t symbol);
wchar_t Table(int language, unsigned int capital, unsigned int row, unsigned int column);
unsigned int Column_in_row(int language, wchar_t symbol, unsigned int row);
wchar_t Alphabet(int language, unsigned int capital, unsigned int index);

#endif
