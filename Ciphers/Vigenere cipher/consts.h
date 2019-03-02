#ifndef CONSTS_H
#define CONSTS_H

const int en_length = 26;
const int ru_length = 33;

const wchar_t *en_alphabet = L"abcdefghijklmnopqrstuvwxyz";
const wchar_t *en_capital_alphabet = L"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const wchar_t *ru_alphabet = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const wchar_t *ru_capital_alphabet = L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";

wchar_t en_table[en_length][en_length];
wchar_t en_capital_table[en_length][en_length];
wchar_t ru_table[ru_length][ru_length];
wchar_t ru_capital_table[ru_length][ru_length];

#endif
