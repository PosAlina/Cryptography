#include "flags.h"
#include "consts.h"
#include "hash_consts.h"

using namespace std;

size_t get_size(FILE *f) {
	size_t size;
	fseek(f, 0, SEEK_END);
	size = ftell(f) - 1;
	fseek(f, 0, SEEK_SET);
	if (size) {
		char symbol = fgetc(f);
		if ((int)symbol == -1)
			return 0;
		fseek(f, 0, SEEK_SET);
	} 
	return size;
}

string itoa(size_t number) {
	string str;
	if (!number)
		str.push_back('0');
	while (number) {
		str.push_back('0' + number % 10);
		number = number / 10;
	}
	reverse(str.begin(), str.end());
	return str;
}

char xitoa(int number) {
	if (number == 0x00)
		return '0';
	if (number == 0x01)
		return '1';
	if (number == 0x02)
		return '2';
	if (number == 0x03)
		return '3';
	if (number == 0x04)
		return '4';
	if (number == 0x05)
		return '5';
	if (number == 0x06)
		return '6';
	if (number == 0x07)
		return '7';
	if (number == 0x08)
		return '8';
	if (number == 0x09)
		return '9';
	if (number == 0x0a)
		return 'a';
	if (number == 0x0b)
		return 'b';
	if (number == 0x0c)
		return 'c';
	if (number == 0x0d)
		return 'd';
	if (number == 0x0e)
		return 'e';
	if (number == 0x0f)
		return 'f';
	return '0';
}

void X(byte *k, byte *a, byte *output) {//k + a (mod 2)
	for (size_t i = 0; i < HASH_SIZE; i++)
		output[i] = k[i] ^ a[i];
}

void S(byte *a) {//Pi_
	for (size_t i = 0; i < HASH_SIZE; i++)
		a[i] = Pi_[a[i]];
}

void P(byte *a) {//Tau_
	byte permutation[HASH_SIZE];
	for (size_t i = 0; i < HASH_SIZE; i++)
		permutation[i] = a[Tau_[i]];
	memcpy(a, permutation, HASH_SIZE);
}

void L(byte *c) {//*A
	for (size_t i = 0; i < 8; i++) {
		long_byte a = 0;
		for (size_t j = 0; j < 8; j++)
			for (size_t k = 0; k < 8; k++)
				if (c[i * 8 + j] & (1 << (7 - k)))
					a ^= A_[j * 8 + k];
		for (size_t j = 0; j < 8; j++)
			c[i * 8 + j] = (a & (0xffffffffffffffff << (7 - j) * 8)) >> (7 - j) * 8;
	}
}

void K_(byte *K, size_t m) {
	X(K, C_[m], K);
	S(K);
	P(K);
	L(K);

}

void E(byte *K, byte *m, byte *output) {
	X(m, K, output);
	for (size_t i = 0; i < 12; i++) {
		S(output);
		P(output);
		L(output);
		K_(K, i);
		X(output, K, output);
	}
}

void g_N(byte *N, byte *h, byte *m) {
	byte output[HASH_SIZE];
	byte out[HASH_SIZE];
	X(h, N, output);
	S(output);
	P(output);
	L(output);
	E(output, m, out);
	X(out, h, out);
	X(out, m, h);
}

void X_512(byte *a, byte *b, byte *output) {
	size_t a_ = 0;
	for (int i = HASH_SIZE - 1; i >= 0; i--) {
		a_ = a[i] + b[i] + (a_ >> 8);
		output[i] = a_ & 0xff;
	}
}

void init_H(byte *h, byte *N, byte *Z, byte *CONST_512, byte *CONST_ZERO,
		size_t type){
	for (int i = 0; i < HASH_SIZE; i++) {
		h[i] = 0x00;
 		N[i] = 0x00;
		Z[i] = 0x00;
		CONST_512[i] = 0x00;
		CONST_ZERO[i] = 0x00;
	}
	CONST_512[HASH_SIZE - 1] = 0x02;
	if (type == _IV_256)
		for (int i = 0; i < HASH_SIZE; i++)
			h[i] = 0x01;
	else
		for (int i = 0; i < HASH_SIZE; i++)
			h[i] = 0x00;
}

void second_stage(byte *M, byte *m, byte *N, byte *h, byte *Z, byte *CONST_512, long_byte &M_size) {
	while (M_size >= HASH_SIZE) {
		memcpy(m, M + M_size - HASH_SIZE, HASH_SIZE);
		for (long_byte i = M_size - HASH_SIZE; i < M_size; i++)
			m[i - M_size + HASH_SIZE] = M[i];
		g_N(N, h, m);
		X_512(N, CONST_512, N);
		X_512(Z, m, Z);
		M_size -= HASH_SIZE;
	}
}

void third_stage(byte *M, byte *m, byte *N, byte *h, byte *Z, byte *CONST_512,
		byte *CONST_ZERO, long_byte M_size) {
	for (size_t i = 0; i < HASH_SIZE; i++)
		m[i] = 0x00;
	m[HASH_SIZE - M_size - 1] = 0x01;
	for (int i = HASH_SIZE - M_size; i < HASH_SIZE; i++)
		m[i] = M[i - HASH_SIZE + M_size];
	g_N(N, h, m);
	long_byte M_size_512 = M_size << 3;
	CONST_512[HASH_SIZE - 1] = M_size_512 & 0xff;
	CONST_512[HASH_SIZE - 2] = (M_size_512 >> 8) & 0xff;
	X_512(N, CONST_512, N);
	X_512(Z, m, Z);
	g_N(CONST_ZERO, h, N);
	g_N(CONST_ZERO, h, Z);
}

void H(byte *M, size_t type, byte *hash, long_byte M_size) {
	byte h[HASH_SIZE], N[HASH_SIZE], Z[HASH_SIZE], CONST_512[HASH_SIZE];
	byte CONST_ZERO[HASH_SIZE];
	init_H(h, N, Z, CONST_512, CONST_ZERO, type);
	byte m[HASH_SIZE];
	second_stage(M, m, N, h, Z, CONST_512, M_size);
	third_stage(M, m, N, h, Z, CONST_512, CONST_ZERO, M_size);
	if (type == _IV_256)
		for (size_t i = 0; i < HASH_SIZE / 2; i++)
			hash[i] = h[i];
	else
		for (size_t i = 0; i < HASH_SIZE; i++)
			hash[i] = h[i];
}

void execute_help(ostream& stream) {
	stream << "Описание флагов\n\n[file] – название файла (путь к файлу),";
	stream << "для которого требуется посчитать контрольную сумму. Если ";
	stream << "параметр отсутствует или равен -, читать со стандартного ";
	stream << "потока ввода.\n";
	stream << "[option] – один из следующих флагов:\n-b, --binary чтение в ";
	stream << "бинарном режиме.\n-t, --text чтение в текстовом режиме (по ";
	stream << "умолчанию).\n-c, --check режим проверки: посчитать значения ";
	stream << "контрольных сумм и проверить соответствующие файлы.\n";
	stream << "-- интерпретировать все последующие операнды как названия ";
	stream << "файлов.\n\nСледующие опции имеют эффект только в режиме ";
	stream << "проверки:\n\n";
	stream << "--ignore-missing игнорировать отсутствующие файлы и ";
	stream << "не выводить сообщение об их статусе.\n";
	stream << "--quiet не печатать OK для удачно прошедших проверку файлов.\n";
	stream << "--status не печатать результаты проверок: ";
	stream << "предполагается использование кода завершения процесса ";
	stream << "для определения результата.\n";
	stream << "--strict выход с ненулевым кодом завершения ";
	stream << "в случае неправильного формата строки.\n";
	stream << "-w, --warn выводить сообщения ";
	stream << "о неправильно форматированных строках в stderr.\n";
	stream << "--help – вывести описание флагов в stdout\n\n";
}


bool count_check_hash_symbol(char &symbol) {
	if ((isdigit(symbol)) || ((isalpha(symbol)) &&
		(((symbol >= 'a') && (symbol <= 'f')) ||
		((symbol >= 'A') && (symbol <= 'F')))))
		return true;
	return false;
}

bool work_with_uncorrect_hash_string(FILE *input, int mode, char symbol) {
	if (feof(input))
		return true;
	symbol = fgetc(input);
	if (((symbol != ' ') &&
		(mode == TEXT_MODE)) || ((symbol != '*') &&
		(mode == BINARY_MODE)))
		return true;
	return false;
}

bool read_hash_string(file_struct input_file, FILE *input, string &hash,
					string &filename, char symbol, size_t &mode) {
	while ((!feof(input)) && (symbol != ' ') && (symbol != '\n') &&
			(count_check_hash_symbol(symbol))) {
		hash.push_back(symbol);
		symbol = fgetc(input);
	}
	if (symbol != ' ') {
		if ((!feof(input)) && (symbol != '\n'))
			while ((!feof(input)) && (symbol != '\n'))
				symbol = fgetc(input);
		return false;
	}
	if (feof(input))
		return false;
	symbol = fgetc(input);
	if ((symbol != ' ') && (symbol != '*')) {
		if ((!feof(input)) && (symbol != '\n'))
			while ((!feof(input)) && (symbol != '\n'))
				symbol = fgetc(input);
		return false;
	}
	if (symbol == ' ')
		mode = TEXT_MODE;
	else
		mode = BINARY_MODE;
	if (feof(input))
		return false;
	symbol = fgetc(input);
	if ((mode == TEXT_MODE)  && (feof(input)))
		return false;
	while ((!feof(input)) &&  (symbol != '\n')) {
		filename.push_back(symbol);
		symbol = fgetc(input);
	}
	return true;
}

void read_message_from_text(byte *message, byte *m, size_t size, FILE *hash_file) {
	for (size_t i = 0; i < size*2; i++) {
		if (i % 2) {
			if (!(fread(message + (i/2)*sizeof(byte), sizeof(byte),
					1, hash_file)))
				throw runtime_error("unreadable file");
		}
		else {
			if (!(fread(m + (i/2)*sizeof(byte), sizeof(byte), 1,
				hash_file)))
				throw runtime_error("unreadable file");
		}
	}
}

void read_message_from_binary(byte *message, size_t size, FILE *hash_file) {
	for (size_t i = 0; i < size; i++) {
		if (!(fread(message + i * sizeof(byte), sizeof(byte),
					1, hash_file)))
				throw runtime_error("unreadable file");
	}
}

void count_hash(FILE *hash_file, size_t type, byte *hash, size_t mode) {
	size_t size = get_size(hash_file);
	if (mode == TEXT_MODE)
		size /= 2;
	else
		size++;
	byte *message = new byte[size];
	if (mode == TEXT_MODE) {
		byte *m = new byte[size];
		read_message_from_text(message, m, size, hash_file);
		delete []m;
	}
	else
		read_message_from_binary(message, size, hash_file);
	if (type == _IV_256)
		H(message, _IV_256, hash, size);
	else
		H(message, _IV_512, hash, size);
	delete []message;
}

void write_error(string error, char (&error_strings)[ERRORS_NUMBER][ERROR_SIZE], size_t &number_of_errors, size_t index_string) {
	string s = ": WARNING: " + itoa(index_string) + ":" + error;
	for(size_t i = 0 ; i < s.length(); i++)
		error_strings[number_of_errors][i] = s[i];
	error_strings[number_of_errors][s.length()] = '\0';
	number_of_errors++;
}

bool count_check_hash(string &filename, bool mis,
				char (&error_strings)[ERRORS_NUMBER][ERROR_SIZE], size_t &number_of_errors,
				size_t index_string, size_t type, byte *hash, size_t mode) {
	FILE *hash_file;
	if (mode == TEXT_MODE)
		hash_file = fopen((filename).c_str(), "r");
	else
		hash_file = fopen((filename).c_str(), "rb");
	if (!hash_file) {
		if (!mis)
			write_error(" no properly formatted g256 checksum lines found", error_strings, number_of_errors, index_string);
		hash[0] = '-';
		return false;
	}
	else
		if (!get_size(hash_file)) {
			if (!mis)
			write_error(" listed file could not be read", error_strings, number_of_errors, index_string);
			fclose(hash_file);
			return false;
		}
		count_hash(hash_file, type, hash, mode);
		fclose(hash_file);
		return true;
}

bool hash_cmp(string h_count, string hash, size_t len) {
	for (size_t i = 0; i < len; i++)
		if (h_count[i] != hash[i])
			return false;
	return true;
}

void print_error_in_correct_string(byte *hash_count, char (&error_str)[ERRORS_NUMBER][ERROR_SIZE], size_t number_of_errors, size_t index_string, bool mis, bool status, bool &error_exit, string filename) {
	error_exit = true;
	if (!status) {
		if (hash_count[0] != '-') {
			write_error(" computed checksum did NOT match",
					error_str, number_of_errors,
					index_string);
			if (mis)
				cout << filename << ": FAILED" << endl;
			else
				cout << filename << ": FAILED open or read" << endl;
		}
		else
			if (!mis)
				cout << filename << ": FAILED open or read" << endl;
	}
}

void print_check_errors(file_struct input_file,
		char (&errors_str)[ERRORS_NUMBER][ERROR_SIZE], size_t er_numb,
		bool status, bool &error_exit, size_t type) {
	if (er_numb) {
		if (!status) {
			string er_g_sum;
			if (type == _IV_256)
				er_g_sum = "g256sum: ";
			else
				er_g_sum = "g512sum: ";
			er_g_sum = er_g_sum + "'" + input_file.file_name + "'";
			for (size_t i = 0; i < er_numb; i++)
				cerr << er_g_sum << errors_str[i] << endl;
		}
		error_exit = true;
	}
}

size_t write_hash_in_char(byte *hash, size_t len, string& h) {
	int mask_2 = 0xf0, mask_3 = 0x0f;
	size_t k = 0;
	for (size_t i = 0; i < len; i++) {
		if ((((int)hash[i] & mask_2)>>4) == 0x00) {
			k++;
			h.push_back(xitoa((int)((int)hash[i] & mask_3)));
			
		}
		else {
			k += 2;
			h.push_back(xitoa(((int)hash[i] & mask_2)>>4));
			h.push_back(xitoa((int)((int)hash[i] & mask_3)));
		}
	}
	return k;
}

void work_with_correct_hash_string(string filename, bool mis, bool status, bool quiet,
		char (&error_strings) [ERRORS_NUMBER][ERROR_SIZE], size_t& number_of_errors,
		size_t index_string, size_t type, bool &error_exit, string hash, size_t len, size_t mode) {
	byte *hash_count = new byte[HASH_SIZE];
	string h;
	if (!count_check_hash(filename, mis, error_strings, number_of_errors,
		index_string, type, hash_count, mode)) {
			print_error_in_correct_string(hash_count, error_strings, number_of_errors, index_string, mis, status,
					error_exit, filename);
			delete [] hash_count;
			return;
	}
	size_t sz;
	if (type == _IV_256)
		sz = write_hash_in_char(hash_count, 32, h);
	else
		sz = write_hash_in_char(hash_count, 64, h);
	if (!hash_cmp(h, hash, sz)) {
		print_error_in_correct_string(hash_count, error_strings, number_of_errors, index_string, mis, status,
					error_exit, filename);
	}
	else
		if ((!quiet) && (!status))
			cout << filename << ":  OK" << endl;
	delete [] hash_count;
}

bool print_improperly_string_format(string filename, char (&error_str) [ERRORS_NUMBER][ERROR_SIZE], size_t &er_numb,
		size_t index_string, bool status,
		bool warn, bool strict, bool& error_exit, size_t type) {
	if (!status) {
		error_exit = true;
		write_error(" is improperly formatted", error_str, er_numb,
				index_string);
		if (warn) {
			string er_g_sum;
			if (type == _IV_256)
				er_g_sum = "g256sum: ";
			else
				er_g_sum = "g512sum: ";
				er_g_sum = er_g_sum + "'" +
					filename + "'";
				cerr << er_g_sum << error_str[er_numb - 1];
				cerr << endl;
			}
		}
	if (strict)
		return false;
	return true;
}

size_t write_hash_in_bytes(string hash, byte *h) {
	stringstream s;
	char b[2];
	size_t half = hash.length() % 2;
	size_t limit = (hash.length() / 2) + half, k = 0;
	for (size_t i = 0; i < limit; i++) {
		s.str("");
		if (hash[2 * (i - k) + k] == '0') {
			s << '0';
			if (hash[2 * (i - k) + k + 1] != '0') {
				s << hash[2 * (i - k) + k + 1];
				memcpy(b, s.str().c_str(), 2);
				h[i] = (byte)strtol(b, 0, 16);
				k++;
			}
			else {
				s << '0';
				memcpy(b, s.str().c_str(), 2);
				h[i] = (byte)strtol(b, 0, 16);
				k += 2;
			}
		}
		else {
			s << hash[2 * (i - k) + k];
			s << hash[2 * (i - k) + k + 1];
			memcpy(b, s.str().c_str(), 2);
			h[i] = (byte)strtol(b, 0, 16);
		}
	}
	return ((hash.length() / 2) + half + 1);
}

bool execute_check(file_struct input_file, FILE *input, bool& error_exit,
				size_t type) {
	char error_str [ERRORS_NUMBER][ERROR_SIZE];
	size_t er_numb = 0, index_string = 1, len = 64;
	if (type == _IV_256)
		len = 32;
	char symbol;
	while ((!feof(input)) && (((int)(symbol = fgetc(input)) != -1))) {
		string hash, filename;
		size_t mode;
		index_string++;
		if (read_hash_string(input_file, input, hash, filename,
					symbol, mode)) {
			work_with_correct_hash_string(filename,
				input_file.ignore_missing, input_file.status,
				input_file.quiet, error_str, er_numb,
				index_string - 1, type, error_exit, hash, len, mode);
		}
		else
			if (!print_improperly_string_format(input_file.file_name, error_str, er_numb, index_string - 1,
				input_file.status,input_file.warn,
				input_file.strict, error_exit, type))
				return false;
	}
	print_check_errors(input_file, error_str, er_numb,
			input_file.status, error_exit, type);
	return true;
}

bool read_file(file_struct input_file, FILE *input, bool& error_exit,
				size_t type) {
	if (input_file.mode == CHECK_MODE)
		return execute_check(input_file, input, error_exit, type);
	else {
		byte *hash = new byte[HASH_SIZE];
		count_hash(input, type, hash, input_file.mode);
		if (type == _IV_512)
			for (size_t i = 0; i < HASH_SIZE; i++)
				cout << hex << (int)hash[i];
		else
			for (size_t i = 0; i < HASH_SIZE / 2; i++)
				cout << hex << (int)hash[i];
		cout << " ";
		if (input_file.mode == BINARY_MODE)
			cout << "*";
		else
			cout << " ";
		cout << input_file.file_name << endl;
		delete[] hash;
	}
	return true;
}

bool print_file_format(file_struct input_file, bool& error_exit, size_t type,
		string error_mes) {
	if (type == _IV_256)
		cerr << "g256sum: " ;
	else
		cerr << "g512sum: ";
	cerr << "'" << input_file.file_name << error_mes << endl;
	error_exit = true;
	return true;
}

bool execute_action(file_struct input_file, bool& error_exit, size_t type) {
	FILE *input;
	if (input_file.std_input) {
		if (input_file.mode == BINARY_MODE)
			input = freopen(NULL, "rb", stdin);
		else
			input = freopen(NULL, "r", stdin);
	}
	else {
		if (input_file.mode == BINARY_MODE)
			input = fopen(input_file.file_name, "rb");
		else
			input = fopen(input_file.file_name, "r");
	}
	if (!input) 
		return print_file_format(input_file, error_exit, type,
				"': No such file or directory");
	if (!get_size(input)) {
		fclose(input);
		return print_file_format(input_file, error_exit, type,
			"': No properly formatted g256 checksum lines found");
	}
	bool correct = read_file(input_file, input, error_exit, type);
	return correct;
}

void except(exception &e) {
	execute_help(cerr);
	cerr << "Error: " << e.what() << endl;
	cerr << "Error type: " << typeid(e).name() << endl << endl;
}

int main (int argc, char **argv) {
	setlocale(LC_ALL, "rus");
	bool help = false, error_exit = false;
	size_t f_size = 0, type = _IV_256;
	try {
		file_struct *files = new file_struct[STRUCT_NUMBER];
		read_arguments(argc, argv, files, f_size, help, type);
		if (help)
			execute_help(cout);
		else
			for (size_t i = 0; i < f_size; i++)
				if (!execute_action(files[i],
					error_exit, type))
					return 1;
		delete []files;
	}
	catch(exception &e) {
		except(e);
		return 1;
	}
	if (error_exit)
		return 1;
	return 0;
}
