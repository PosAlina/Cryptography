#ifndef FLAGS_H
#define FLAGS_H

int flag(char *arg);
void is_correct_gost(char *argv, int &gost);
void is_correct_action(char *argv, int &action);
void is_correct_file_flag(char *argv, int &flag, int &flag_name, int j);
void is_correct_flag_type(int flag_type, char *argv, int j, int &gost,
                          int &action, int &k, int &v, int &i, int &o,
						  int &flag_name);
void is_argument_error(int &gost, int &action, int &k, int &v, int &i, int &o,
                       int &flag_name);
void read_arguments(int argc, char **argv, int &help, int &gost, int &action,
                    int &k, int &v, int &i, int &o);

#endif
