#include <iostream>
#include <fstream>

char digit_to_hex(unsigned char ch) {
	if (ch < 10) {
		return (char)('0' + ch);
	}
	return (char)('A' + ch - 10);
}

void dec_to_hex(long long int num, char res[10], long long int& sz) {
	long long int numc = num;
	int n = 1;
	long long int szc = 0;
	sz = 0;
	while (num > 0) {
		++sz;
		num /= 16;
		n *= 16;
	}
	szc = sz;
	num = numc;
	while (n > 1) {
		numc = (num / (n / 16)) % 16;
		if (numc < 10) {
			res[(sz - szc)] = (char)('0' + numc);
			--szc;
		}
		else {
			res[(sz - szc)] = (char)('A' + numc - 10);
			--szc;
		}
		n /= 16;
	}
}

void hex_out(long long int s, long long int n, char* input) {
	std::ifstream inputfile(input, std::ios::binary);
	if (!inputfile) {
		std::cout << "Failed to open file\n";
		return;
	}

	const int szline = 16;
	unsigned char line[szline];
	unsigned char c = '0';
	char* ch;
	bool goal = false;
	long long int block = 0;
	long long int sz = 0;
	long long int ns = n;
	char out[10];
	long long int spaces = 0;

	while (s > 0 && !inputfile.eof()) {
		inputfile.get();
		--s;
	}

	while (!inputfile.eof() && !goal) {

		//cout block of num
		int cnt = 0;

		while (!inputfile.eof() && cnt < szline) {
			c = (unsigned char)inputfile.get();
			line[cnt++] = c;
		}
		long long int fact_size = cnt;



		if (n < fact_size && ns != 0) {
			fact_size = n;
		}

		if (inputfile.eof()) {
			--fact_size;
		}

		dec_to_hex(block, out, sz);

		for (int i = 0; i < (10 - sz); ++i) {
			std::cout << "0";
		}
		for (int i = 0; i < sz; ++i) {
			std::cout << out[i];
		}
		std::cout << ": ";

		//cout block of 16 symb in hex

		int idx = 0;

		for (int i = idx; i < 8 && i < fact_size; ++i) {
			unsigned char l = line[i] / 16;
			unsigned char r = line[i] % 16;
			std::cout << digit_to_hex(l) << digit_to_hex(r) << ' ';
			idx = i;
			i = idx;
		}


		if (fact_size < 8) {
			spaces = 8 - fact_size;
			for (int i = 0; i < spaces; ++i) {
				std::cout << "   ";
			}
		}
		std::cout << "| ";
		++idx;
		for (int i = idx; i < 16 && i < fact_size; ++i) {
			unsigned char l = line[i] / 16;
			unsigned char r = line[i] % 16;
			std::cout << digit_to_hex(l) << digit_to_hex(r) << ' ';
			idx = i;
			i = idx;
		}
		if (fact_size < 16) {
			(fact_size <= 8) ? spaces = 8 : spaces = 8 - fact_size % 8;
			for (int i = 0; i < spaces; ++i) {
				std::cout << "   ";
			}
		}
		std::cout << ' ';

		//cout block of 16 symb in char
		for (int i = 0; i < fact_size; ++i) {
			if (line[i] > 31) {
				std::cout << line[i];
			}
			else {
				std::cout << '.';
			}
		}
		n -= fact_size;
		block += 16;
		if (!inputfile.eof() && (n > 0 || ns == 0)) {
			std::cout << '\n';
		}
		else {
			break;
		}
	}
	inputfile.close();
}

int main(int argc, char* argv[])
{
	long long int n = 0;
	long long int s = 0;
	if (argc == 2) {
		hex_out(s, n, argv[argc - 1]);
	}
	else if (argc == 4) {
		if (argv[1][1] == 's') {
			s = atoi(argv[2]);
		}
		else {
			n = atoi(argv[2]);
		}
		hex_out(s, n, argv[argc - 1]);
	}
	else if (argc == 6) {
		if (argv[1][1] == 's') {
			s = atoi(argv[2]);
			n = atoi(argv[4]);
		}
		else {
			s = atoi(argv[4]);
			n = atoi(argv[2]);
		}
		hex_out(s, n, argv[argc - 1]);
	}

	return 0;
}
