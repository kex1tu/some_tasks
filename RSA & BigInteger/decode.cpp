#include "biginteger.hpp"
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {


  if (argc != 3) {
    throw std::invalid_argument("Incorrect count of arguments");
  }

  std::ifstream key_file;
  std::ifstream message_file;
  key_file.open(argv[1]);
  message_file.open(argv[2]);
  if (key_file && message_file) {
    std::string coded_message_str;
    std::string modulus_str;
    std::string private_exp_str;

    message_file >> coded_message_str;
    key_file >> modulus_str; key_file >> modulus_str;

    key_file >> private_exp_str; key_file >> private_exp_str;
    key_file >> private_exp_str; key_file >> private_exp_str;
    BigInteger coded_message(coded_message_str, biginteger_base::hex);
    BigInteger modulus(modulus_str, biginteger_base::hex);
    BigInteger private_exp(private_exp_str, biginteger_base::hex);
    BigInteger decoded_message;
    decoded_message = binmodpow(coded_message, private_exp, modulus);
    std::cout << to_hex(decoded_message);
  } else {
    std::cout << "cannot open file(s)" << std::endl;
  }
  key_file.close();
  message_file.close();
  return 0;
}
