#include <iostream>
#include <fstream>
#include <cstring>

char base_32_alph[] = "0123456789ABCDEFGHJKMNPQRSTVWXYZ";
char base_32_char(unsigned char b) {
	b &= 0x1F;
	return base_32_alph[(int)b];
}
int base_32_code(int ch) {
	int idx = 0;
	ch = std::toupper(ch);
	for (; idx < 32; ++idx) {
		if (ch == base_32_alph[idx]) {
			return idx;
		}
	}
	if (ch == 'I' || ch == 'L') {
		return 1;
	}
	if (ch == 'O') {
		return 0;
	}
	return -1;
}

void base_32_decode(std::ifstream& input_file, std::ofstream& output_file) {
	const int block_sz = 1;
	int input_str[8 * block_sz];
	int output_str[5 * block_sz];

	int cnt = 0;
	int size_s[9] = { 5,5,4,4,3,2,2,1,0 };
	int ch = 0;
	while (ch!= EOF) {
		for (int i = 0; i < 8; ++i) {
			input_str[i] = -1;
		}
		cnt = 0;
		ch = 0;
		int cd = 0;
		int input_cnt = 0;
  
		while (input_cnt != 8 && ch != EOF) {
			ch = input_file.get();
			if (ch != '=') {
				cd = base_32_code(ch);
				if (cd != -1) {
					input_str[input_cnt] = cd;
					++input_cnt;
				}
			}
			else {
				input_str[input_cnt] = -1;
				++cnt;
				++input_cnt;
			}
		}
		if (input_cnt == 0) {
			break;
		}
		int out_lim = 0;

		output_str[0] = ((input_str[0] & 0b00011111) << 3) | ((input_str[1] & 0b00011100) >> 2);
		output_str[1] = (input_str[1] << 6) | (input_str[2] << 1) | (input_str[3] >> 4);
		output_str[2] = ((input_str[3] & 0b00001111) << 4) | (input_str[4] >> 1);
		output_str[3] = (input_str[4] << 7) | (input_str[5] << 2) | (input_str[6] >> 3);
		output_str[4] = (input_str[6] << 5) | input_str[7];
		char out_chars[5 * block_sz];
		out_lim = size_s[cnt];
		while ((output_str[out_lim - 1] == -1 || output_str[out_lim - 1] == 0) && input_str[8 - cnt] == -1) {
			--out_lim;
		}

		for (int i = 0; i < out_lim; ++i) {
				out_chars[i] = (char)output_str[i];
		}
		output_file.write(out_chars, out_lim);
	}

}
int base_32_encode(const char input_str[], int sz, char output_str[]) {
	unsigned char in_bytes[5];
	unsigned char out_bytes[8];

	int in_idx = 0;
	int out_idx = 0;
	for (in_idx = 0; in_idx < sz; in_idx += 5) {
		for (int i = 0; i < 5; ++i) {
			in_bytes[i] = 0;
		}
		for (int i = 0; i < 5; ++i) {
			if (in_idx + i < sz) {
				in_bytes[i] = input_str[in_idx + i];
			}
		}
		out_bytes[0] = ( ( in_bytes[0] & 0b11111000) >> 3);
		out_bytes[1] = ( ( ( in_bytes[0] & 0b00000111) << 2) | ( ( in_bytes[1] & 0b11000000) >> 6) );
		out_bytes[2] = ( ( in_bytes[1] & 0b00111110) >> 1);
		out_bytes[3] = ( ( ( in_bytes[1] & 0b00000001) << 4) | ( ( in_bytes[2] & 0b11110000) >> 4) );

		out_bytes[4] = ( ( ( in_bytes[2] & 0b00001111) << 1) | ( ( in_bytes[3] & 0b10000000) >> 7) );
		out_bytes[5] = ( ( in_bytes[3] & 0b01111100) >> 2);
		out_bytes[6] = ( ( ( in_bytes[3] & 0b00000011) << 3) | ( ( in_bytes[4] & 0b11100000) >> 5) );
		out_bytes[7] = ( in_bytes[4] & 0b00011111 );

		
		output_str[out_idx++] = base_32_char(out_bytes[0]);
		output_str[out_idx++] = base_32_char(out_bytes[1]);
		output_str[out_idx++] = base_32_char(out_bytes[2]);
		output_str[out_idx++] = (in_idx < sz) ? base_32_char(out_bytes[3]) : '=';
		output_str[out_idx++] = (in_idx + 1 < sz) ? base_32_char(out_bytes[4]) : '=';
		output_str[out_idx++] = (in_idx + 2 < sz) ? base_32_char(out_bytes[5]) : '=';
		output_str[out_idx++] = (in_idx + 3 < sz) ? base_32_char(out_bytes[6]) : '=';
		output_str[out_idx++] = (in_idx + 4 < sz) ? base_32_char(out_bytes[7]) : '=';
	}
	return out_idx;
}

int main(int argc, char* argv[]) {
	
	std::ifstream input_file(argv[2], std::ios::binary);
	std::ofstream output_file(argv[3], std::ios::binary);
	
	if (strcmp(argv[1], "-d") == 0) {
		base_32_decode(input_file, output_file);
	}
	if (strcmp(argv[1], "-e") == 0) {
		const int block_sz = 8;
		char input_str[5 * block_sz];
		char output_str[8 * block_sz];
		while (input_file.peek() != EOF) {
			input_file.read(input_str, 40);
			int s = (int)input_file.gcount();
			s = base_32_encode(input_str, s, output_str);
			output_file.write(output_str, s);
		}
	}
	input_file.close();
	output_file.close();

	return 0;
}
