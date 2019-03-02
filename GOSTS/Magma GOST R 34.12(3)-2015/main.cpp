#include "consts.h"
#include "flags.h"
#include "actions.h"

using namespace std;

int main (int argc, char **argv) {
  try {
	setlocale(LC_ALL, "rus");
	int h = 0, gost = 0, act = 0, k = 0, v = 0, i = 0, o = 0;
	read_arguments(argc, argv, h, gost, act, k, v, i, o);
    if (h)
	  help(cout);
    else
	  action(argv, gost, act, k, v, i, o);
  }
  catch(exception &e) {
    cerr << "Error: " << e.what() << " type: " << typeid(e).name() << endl;
    help(cerr);
    return 1;
  }
  return 0;
}
