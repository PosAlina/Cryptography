#ifndef FLAGS_H
#define FLAGS_H
#include "consts.h"

void init(file_struct &file);
void check_format(int argc, char **argv, size_t &type_iv);
void check_help(int argc, char **argv, bool &help);
void write_file(string argv, file_struct *files, size_t &f_size);
void no_options(string argv, file_struct *files, size_t &f_size);
void up_mode(file_struct *files, size_t &f_size, size_t mode,
			bool &f_name);
void up_check_option(file_struct *files, size_t &f_size, bool &option,
					bool &f_name);
void up_options(string argv, file_struct *files, size_t &f_size,
				bool &f_name);
void up_flag(string argv, file_struct *files, size_t &f_size,
				bool &files_flag, bool &f_name);
void write_std_file(file_struct *files, size_t &f_size);
void read_arguments(int argc, char **argv, file_struct *files,
					size_t &f_size, bool &help,
		size_t &type);

#endif
