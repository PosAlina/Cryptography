#ifndef GLOBALS_H
#define GLOBALS_H

const int ERROR_INPUT = 1;
const int ERROR_FILE = 2;
const int ERROR_ACTION = 3;
const int ERROR_LANGUAGE = 4;
const int ERROR_NUMBER = 5;
const int ERROR_FORMAT_NUMBER = 6;
const int ERROR_FORMAT_TEXT = 7;
const int ERROR_SYMBOL = 8;

const wchar_t en_alphabet[5][6] = {L"abcde", L"fghik", L"lmnop", L"qrstu", L"vwxyz"};
const wchar_t en_capital_alphabet[5][6] = {L"ABCDE", L"FGHIK", L"LMNOP", L"QRSTU", L"VWXYZ"};
const wchar_t ru_alphabet[6][7] = {L"абвгде", L"ёжзийк", L"лмнопр", L"стуфхц", L"чшщъыь", L"эюя_.,"};
const wchar_t ru_capital_alphabet[6][7] = {L"АБВГДЕ", L"ЁЖЗИЙК", L"ЛМНОПР", L"СТУФХЦ", L"ЧШЩЪЫЬ", L"ЭЮЯ_.,"};

#endif
