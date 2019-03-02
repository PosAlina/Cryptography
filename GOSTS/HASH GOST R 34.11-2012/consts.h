#pragma once
#ifndef CONSTS_H
#define CONSTS_H

#include <cstring>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <typeinfo>
#include <algorithm>

#define BINARY_MODE 1
#define TEXT_MODE 2
#define CHECK_MODE 3

#define _IV_256 1
#define _IV_512 2

#define STRUCT_NUMBER 100
#define ERRORS_NUMBER 200
#define ERROR_SIZE 100

using namespace std;

typedef struct f_struct {
	size_t mode;
	bool ignore_missing, quiet, status, strict, warn, std_input;
	char file_name[64];
} file_struct;

#endif
