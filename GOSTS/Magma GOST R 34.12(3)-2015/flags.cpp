#include "consts.h"

using namespace std;

int flag(char *arg) {
  if ((!strcmp(arg, "--ecb")) || (!strcmp(arg, "--ctr")) ||
     (!strcmp(arg, "--ofb")) || (!strcmp(arg, "--cbc")) ||
	 (!strcmp(arg, "--cfb")) || (!strcmp(arg, "--mac")))
    return F_GOST;
  if ((!strcmp(arg, "-e")) || (!strcmp(arg, "-d")))
	return F_ACTION;
  if (!strcmp(arg, "-k"))
	return F_K;
  if (!strcmp(arg, "-v"))
    return F_V;
  if (!strcmp(arg, "-i"))
    return F_I;
  if (!strcmp(arg, "-o"))
	return F_O;
  throw invalid_argument(arg);
}

void is_correct_gost(char *arg, int &gost) {
  if (gost)
	throw invalid_argument(arg);
  if (!strcmp(arg, "--ecb"))
    gost = F_ECB;
  if (!strcmp(arg, "--ctr"))
    gost = F_CTR;
  if (!strcmp(arg, "--ofb"))
    gost = F_OFB;
  if (!strcmp(arg, "--cbc"))
    gost = F_CBC;
  if (!strcmp(arg, "--cfb"))
    gost = F_CFB;
  if (!strcmp(arg, "--mac"))
    gost = F_MAC;
}

void is_correct_action(char *arg, int &action) {
  if (action)
	throw invalid_argument(arg);
  if (!strcmp(arg, "-e"))
    action = F_E;
  else
	action = F_D;
}

void is_correct_file_flag(char *argv, int &flag, int &flag_name, int j) {
  if (flag)
	throw invalid_argument(argv);
  flag = j;
  flag_name = 1;
}

void is_correct_flag_type(int flag_type, char *argv, int j, int &gost,
                          int &action, int &k, int &v, int &i, int &o,
						  int &flag_name) {
  if (flag_type == F_GOST)
	is_correct_gost(argv, gost);
  if (flag_type == F_ACTION)
	is_correct_action(argv, action);
  if (flag_type == F_K)
    is_correct_file_flag(argv, k, flag_name, j);
  if (flag_type == F_V)
    is_correct_file_flag(argv, v, flag_name, j);
  if (flag_type == F_I)
    is_correct_file_flag(argv, i, flag_name, j);
  if (flag_type == F_O)
    is_correct_file_flag(argv, o, flag_name, j);
}

void is_argument_error(int &gost, int &action, int &k, int &v, int &i, int &o,
                       int &flag_name) {
  if (flag_name)
	throw invalid_argument("no file name");
  if ((gost == F_MAC) && action)
    throw invalid_argument("action with flag \"mac\"");
  if (gost && (!k))
    throw invalid_argument("no key file");
  if ((gost != F_MAC) && (!action))
    throw invalid_argument("no action: encrypt/decrypt");
  if (v && gost && ((gost == F_ECB) || (gost == F_MAC)))
    throw invalid_argument("unless file with IV");
}

void read_arguments(int argc, char **argv, int &help, int &gost, int &action,
                    int &k, int &v, int &i, int &o) {
  if (argc < 3)
    throw invalid_argument("error number");
  if (strcmp(argv[1], "magma"))
	throw invalid_argument("no \"magma\"");
  if ((!strcmp(argv[2], "-h")) || (!strcmp(argv[2], "-help"))) {
	if (argc != 3)
	  throw invalid_argument(argv[3]);
    help = 1;
	return;
  }
  int flag_name = 0, flag_type;
  for (int j = 2; j < argc; ++j) {
	if (flag_name) {
	  flag_name = 0;
	  continue;
	}
	flag_type = flag(argv[j]);
    is_correct_flag_type(flag_type, argv[j], j + 1, gost, action, k, v, i, o,
	                     flag_name);
  }
  is_argument_error(gost, action, k, v, i, o, flag_name);
}
