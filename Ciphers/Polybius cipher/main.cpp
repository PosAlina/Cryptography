#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "globals.h"
#include "polybius_functions.h"

using namespace std;

int main (int argc, char **argv) {
  int output;
  if ((output = Arguments(argc, argv)) == 2)
	exit(1);
  setlocale(LC_ALL, "");
  FILE *input = fopen(argv[1], "r");
  if (input == NULL) {
    cerr << "Error: Input file is not open." << endl;
    exit(1);
  }
  try {
    unsigned int action = Action(input);
    unsigned int language = Language(input);
    int odd_number = Odd_number(input);
    Main_program(action, output, Text(input), odd_number, language);
    fclose(input);
  } catch (const int exception) {
    fclose(input);
    Exception_output(exception);
    exit(1);
  }
  return 0;
}
