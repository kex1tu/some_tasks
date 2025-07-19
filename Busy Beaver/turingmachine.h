#pragma once
#include <string>
#include <cstring>
#include <iostream>

/*-------S T R U C T U R E S-------*/
struct state {
  char name_[16];
  char name_zero_[16];
  char name_one_[16];
  char put_zero_;
  char put_one_;
  int act_zero_;
  int act_one_;
};

struct node {
  state data;
  node* next;
  node* prev;
};

struct list {
  node* begin;
  node* end;
};


/*-------F U N C T I O N S-------*/
void del_spaces(char str[256]);
node* find_node(char name[16], list& ls);
void add_state(char buff[256], list& prog);
void delete_list(list& ls);

/*-------C L A S S E S-------*/

class TuringMachine {
 private:
  list programm_;
  char* tape_;
  long long int tape_size_;
  long long int curr_pos_;
  state* curr_state_;
  unsigned long long maxsteps_;
 public:
  TuringMachine(long long int len, list &programm);
  TuringMachine(const TuringMachine& MT);
  TuringMachine& operator=(const TuringMachine& MT);
  ~TuringMachine() {
    delete_list(this->programm_);
    delete[] tape_;
  }
  
  unsigned long long run(unsigned long long maxsteps);
  unsigned long long calc(std::string& tape, unsigned long long maxsteps);
};
