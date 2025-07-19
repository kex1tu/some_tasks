#include <iostream>
#include <fstream>
#include "turingmachine.h"

int main(int argc, char* argv[]){

  if (argc != 4) {
    std::cout << "not enough arguments" << std::endl;
  }
  std::ifstream ifs(argv[1]);
  if (ifs) {
    list prog;
    prog.begin = nullptr;
    prog.end = nullptr;
    char buff[256];

    while (ifs.getline(buff, 256)) {
      add_state(buff, prog);
    }

    long long int len_tape = atoi(argv[2]);
    long long int mx_steps = atoll(argv[3]);

    TuringMachine TM1(len_tape, prog);
    TuringMachine TM2 = TM1;

    TM2.run(mx_steps);
    ifs.close();
  } else {
    std::cout << "cannot open file" << std::endl;
  }

  return 0;
}
