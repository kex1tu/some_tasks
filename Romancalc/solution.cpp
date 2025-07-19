#include <iostream>
#include <fstream>

void action(int* stack, char ch, int& sz) {
	int a = stack[sz - 2];
	int b = stack[sz - 1];
	if (ch == '+') {
		a += b;
	}
	if (ch == '-') {
		a -= b;
	}
	if (ch == '/') {
		a /= b;
	}
	if (ch == '*') {
		a *= b;
	}
	stack[sz - 2] = a;
	stack[sz - 1] = 0;
	--sz;
}
int to_arab(const char* num, int sznum) {

	char romanalph[7] = { 'I','V', 'X', 'L' ,'C', 'D','M' };
	int romannum[7] = { 1, 5, 10, 50, 100, 500, 1000 };

	int k_1 = 0;
	int k_2 = 0;
	char ch_1;
	char ch_2;
	int res = 0;

	ch_2 = num[0];
	while (ch_2 != romanalph[k_2]) {
		++k_2;
	}

	for (int i = 0; i < sznum - 1; ++i) {

		k_1 = k_2;
		ch_2 = num[i + 1];
		k_2 = 0;
		while (ch_2 != romanalph[k_2]) {
			++k_2;
		}

		if (k_1 >= k_2) {
			res += romannum[k_1];
		}
		else {
			res -= romannum[k_1];
		}
	}
	res += romannum[k_2];
	return res;
}
void to_roman(int num, int& sz, char outn[32]) {
	int arab[13] = { 1,4,5,9,10,40,50,90,100,400,500,900,1000 };
	static const char* roman[13] = { "I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M" };
	int i = 12;
	char tmp[32];
	sz = 0;
	while (num != 0) {
		while (num >= arab[i]) {
			tmp[sz] = roman[i][0];
			sz++;
			if (i % 2 == 1) {
				tmp[sz] = roman[i][1];
				sz++;
			}
			num -= arab[i];
		}
		i--;
	}
	for (int i = 0; i < sz; ++i) {
		outn[i] = tmp[i];
	}
}
void func(char input[], char output[]) {
	std::ifstream in;
	in.open(input);
	std::ofstream out;
	out.open(output);
	char ch;
	int szstack = 1;
	char num[32];
	num[0] = '0';
	char flagch = '0';
	int sznum = 0;
	int stack[102];
	int cnt = 0;
	ch = (char)in.get();
	char outnum[32];
	while (ch != EOF && !in.eof()) {
		if (ch == '\n') {
			++cnt;
			out << " = ";
			int szout = 0;
			if (stack[szstack - 1] < 4000 && stack[szstack - 1] != 0) {
				to_roman(stack[szstack - 1], szout, outnum);
				for (int i = 0; i < szout; ++i) {
					out << outnum[i];
				}
				for (int i = 0; i < szout; ++i) {
					outnum[i] = '0';
				}
			}
			else {
				out << "ERR";
			}
			
		}
		else if (ch == ' ') {
			if (num[0] != '0') {
				int arab_num = to_arab(num, sznum);
				if (szstack < 102) {
					stack[szstack++] = arab_num;
				}
				for (int i = 0; i < 32; ++i) {
					num[i] = '0';
				}
				sznum = 0;
			}

		}
		else if (ch == 'I' || ch == 'V' || ch == 'X' ||
			ch == 'L' || ch == 'C' || ch == 'D' || ch == 'M') {
			num[sznum++] = ch;
		}
		else {
			action(stack, ch, szstack);
		}
		out << ch;
		ch = (char)in.get();

	}
	std::cout << cnt << " " << szstack << '\n';
	if (ch == EOF || in.eof()) {
		if (cnt + 1 != szstack && cnt != szstack) {
			++cnt;
			out << " = ";
			int szout = 0;
			if (stack[szstack - 1] < 4000 && stack[szstack - 1] != 0) {
				to_roman(stack[szstack - 1], szout, outnum);
				for (int i = 0; i < szout; ++i) {
					out << outnum[i];
				}
				for (int i = 0; i < szout; ++i) {
					outnum[i] = '0';
				}
			}
			else {
				out << "ERR";
			}
		}
	}

	in.close();
	out.close();
}

int main(int argc, char* argv[])
{
	func(argv[1], argv[2]);
	return 0;
}
