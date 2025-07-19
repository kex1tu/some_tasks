#include <iostream>
#include <string>

std::string to_s(unsigned long long n) {
	std::string res;
	while (n > 0) {
		res+=(char)((n % 10) + '0');
		n /= 10;
	}
	char tmp;
	for(int i = 0; i < res.size()/2; ++i){
	    tmp = res[i];
	    res[i] = res[res.size() -1 - i];
	    res[res.size() -1 - i] = tmp;
	}
	return res;
}

unsigned long long to_i(std::string &str) {
	unsigned long long res = 0;
	unsigned long long pw = 1;
	for (unsigned long long i = str.size(); i > 0; --i){
		res +=(str[i-1] -'0') * pw;
		pw *= 10;
	}
	return res;
}

std::string to_ten_base(std::string str, unsigned long long int base) {
	char dig[21] = "0123456789ABCDEFGHIJ";
	unsigned long long int ten_base_num = 0;
	unsigned long long int pw = 1;
	unsigned long long int prpw = 0;
	char ch;
	std::string res;
	for (int j = 0; j < str.size(); ++j) {
		ch = str[str.size() -j- 1];
		prpw = pw;
		for (int i = 0; i < base; ++i) {
			if (dig[i] == ch) {
				ten_base_num += (i * pw);
				pw *= base;
				break;
			}
		}
		if (pw == prpw) {
			return "error";
		}
		
	}
	res = to_s(ten_base_num);
	return res;
}

std::string to_some_base(std::string ten_base_num, int base) {
	char dig[20] = "0123456789ABCDEFGHI";
	std::string res;
	unsigned long long num = 0;
	num = to_i(ten_base_num);
	while (num > 0) {
		res+= dig[num % base];
		num /= base;
	}

	char tmp;
	for(int i = 0; i < res.size()/2; ++i){
	    tmp = res[i];
	    res[i] = res[res.size() -1 - i];
	    res[res.size() -1 - i] = tmp;
	}
	return res;
}

int main()
{
	std::string input_num;
	std::string output_num;
	int input_base;
	int output_base;
	std::string ten_base_num;

	std::cin >> input_num >> input_base >> output_base;
	ten_base_num = to_ten_base(input_num, input_base);
	
	if (ten_base_num == "error") {
		std::cout << "wrong integer" << std::endl;
		return 0;
	}
	if (output_base == 10) {
		std::cout << ten_base_num  << std::endl;
		return 0;
	}
	output_num = to_some_base(ten_base_num, output_base);

	std::cout << output_num << std::endl;

	return 0;
}
