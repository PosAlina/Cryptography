#include "consts.h"

using namespace std;

void init(file_struct &file) {
	file.mode = 0;
	file.ignore_missing = false;
	file.quiet = false;
	file.status = false;
	file.strict = false;
	file.warn = false;
	file.std_input = false;
}

void check_format(int argc, char **argv, size_t &type) {
	if (argc < 3)
		throw invalid_argument("not arguments");
	if (!strcmp(argv[1], "g256sum"))
		type = _IV_256;
	else
		if (!strcmp(argv[1], "g512sum"))
			type = _IV_512;
		else
			throw invalid_argument(argv[1]);
}

void check_help(int argc, char **argv, bool &help) {
	if (argc != 3)
		throw invalid_argument(argv[3]);
	help = true;
}

size_t c_size(char *str) {
	size_t i = 0;
	while (str[i] != '\0')
		i++;
	return i;
}

void write_file(char *argv, file_struct *files, size_t &f_size) {
	for (size_t i = 0; i < c_size(argv); i++)
		files[f_size].file_name[i] = argv[i];
	if (!files[f_size].mode)
		files[f_size].mode = TEXT_MODE;
	f_size++;
	init(files[f_size]);
}

void no_options(string argv, file_struct *files, size_t &f_size) {
	if ((files[f_size].ignore_missing) || (files[f_size].quiet) ||
		(files[f_size].status) || (files[f_size].strict) ||
		(files[f_size].warn))
		if (!files[f_size].mode)
			throw invalid_argument(argv);
}

void up_mode(file_struct *files, size_t &f_size, size_t mode,
			bool &f_name) {
	if (files[f_size].mode) {
		files[f_size].std_input = true;
		f_size++;
	}
	files[f_size].mode = mode;
	f_name = false;
}

void up_check_option(file_struct *files, size_t &f_size, bool &option,
					bool &f_name) {
	if ((option) || ((files[f_size].mode) &&
		(files[f_size].mode != CHECK_MODE))) {
		if (!files[f_size].mode)
			files[f_size].mode = TEXT_MODE;
		files[f_size].std_input = true;
		f_size++;
	}
	f_name = false;
}

void up_options(string argv, file_struct *files, size_t &f_size,
				bool &f_name) {
	if (argv == "--ignore-missing") {
		up_check_option(files, f_size, files[f_size].ignore_missing, f_name);
		files[f_size].ignore_missing = true;
	}
	if (argv == "--quiet") {
		up_check_option(files, f_size, files[f_size].quiet, f_name);
		files[f_size].quiet = true;
	}
	if (argv == "--status") {
		up_check_option(files, f_size, files[f_size].status, f_name);
		files[f_size].status = true;
	}
	if (argv == "--strict"){
		up_check_option(files, f_size, files[f_size].strict, f_name);
		files[f_size].strict = true;
	}
	if ((argv == "-w") || (argv == "--warn")){
		up_check_option(files, f_size, files[f_size].warn, f_name);
		files[f_size].warn = true;
	}
}

void up_flag(string argv, file_struct *files, size_t &f_size,
				bool &files_flag, bool &f_name) {
	if ((argv == "-b") || (argv == "--binary")) {
		no_options(argv, files, f_size);
		up_mode(files, f_size, BINARY_MODE, f_name);
	}
	if ((argv == "-t") || (argv == "--text")) {
		no_options(argv, files, f_size);
		up_mode(files, f_size, TEXT_MODE, f_name);
	}
	if ((argv == "-c") || (argv == "--check"))
		up_mode(files, f_size, CHECK_MODE, f_name);
	if (argv == "--") {
		files_flag = true;
		f_name = false;
	}
	up_options(argv, files, f_size, f_name);
}

void write_std_file(file_struct *files, size_t &f_size) {
	files[f_size].std_input = true;
	if (!files[f_size].mode)
		files[f_size].mode = TEXT_MODE;
	f_size++;
}

void read_arguments(int argc, char **argv, file_struct *files,
			size_t &f_size, bool &help, size_t &type) {
	check_format(argc, argv, type);
	if (!strcmp(argv[2], "--help")) {
		check_help(argc, argv, help);
		return;
	}
	init(files[0]);
	bool files_flag = false, f_after_flag = false, f_name;
	for (int i = 2; i < argc; i++) {
		if (files_flag) {
			f_after_flag = true;
			write_file(argv[i], files, f_size);
			continue;
		}
		if (!strcmp(argv[i], "--help"))
			throw invalid_argument(argv[i]);
		f_name = true;
		up_flag(argv[i], files, f_size, files_flag, f_name);
		if (f_name)
			write_file(argv[i], files, f_size);
	}
	if ((!f_size) || ((files_flag) && (!f_after_flag)))
		write_std_file(files, f_size);
}
