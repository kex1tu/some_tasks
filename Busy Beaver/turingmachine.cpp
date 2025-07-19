#include "turingmachine.h"
#include <iostream>



TuringMachine::TuringMachine(long long int len, list &programm) {
  programm_ = programm;
  curr_state_ = &(programm_.begin->data);

  tape_size_ = len;
  tape_ = new char[tape_size_];

  for (size_t i = 0; i < tape_size_; ++i) {
    tape_[i] = '0';
  }
  curr_pos_ = 0;
  maxsteps_ = 0;
}

TuringMachine::TuringMachine(const TuringMachine& MT) {

  programm_.begin = nullptr;
  programm_.end = nullptr;
  node* current = MT.programm_.begin;
  node* prev_node = nullptr;

  while (current != nullptr) {
    node* new_node = new node();
    new_node->data = current->data;
    new_node->prev = prev_node;
    new_node->next = nullptr;
    if (prev_node != nullptr) {
      prev_node->next = new_node;
    } else {
      programm_.begin = new_node;
    }

    prev_node = new_node;
    current = current->next;

  }

  programm_.end = prev_node;

  if (MT.curr_state_ != nullptr) {
    node* found_node = find_node(MT.curr_state_->name_, programm_);
    if (found_node != nullptr) {
      curr_state_ = &(found_node->data);
    } else {
      curr_state_ = nullptr;
    }
  } else {
    curr_state_ = nullptr;
  }

  tape_size_ = MT.tape_size_;
  tape_ = new char[tape_size_];
  for (long long int i = 0; i < tape_size_; ++i) {
    tape_[i] = MT.tape_[i];
  }

  curr_pos_ = MT.curr_pos_;
  maxsteps_ = MT.maxsteps_;
}

TuringMachine& TuringMachine::operator=(const TuringMachine& MT) {
  if (this == &MT) {
    return *this;
  }

  delete_list(this->programm_);

  this->programm_.begin = nullptr;
  this->programm_.end = nullptr;
  node* current = MT.programm_.begin;
  node* prev_node = nullptr;

  while (current != nullptr) {
    node* new_node = new node();
    new_node->data = current->data;
    new_node->prev = prev_node;
    new_node->next = nullptr;

    if (prev_node != nullptr) {
      prev_node->next = new_node;
    } else {
      programm_.begin = new_node;
    }

    prev_node = new_node;
    current = current->next;
  }

  this->programm_.end = prev_node;

  if (MT.curr_state_ != nullptr) {
    node* found_node = find_node(MT.curr_state_->name_, this->programm_);
    if (found_node != nullptr) {
      this->curr_state_ = &(found_node->data);
    } else {
      this->curr_state_ = nullptr;
    }
  } else {
    this->curr_state_ = nullptr;
  }

  this->tape_size_ = MT.tape_size_;
  this->tape_ = new char[this->tape_size_];
  for (long long int i = 0; i < this->tape_size_; ++i) {
    this->tape_[i] = MT.tape_[i];
  }
  this->curr_pos_ = MT.curr_pos_;
  this->maxsteps_ = MT.maxsteps_;
  return *this;
}

unsigned long long TuringMachine::run(unsigned long long maxsteps) {

  int mv = 0;
  char curr_ch = 0;
  unsigned long long  cnt = 0;
  node* tmp = nullptr;
  bool fl = false;

  while (cnt < maxsteps) {
    curr_ch = tape_[curr_pos_];

    if (curr_ch == '0') {
      if (curr_state_->put_zero_ != 'U') {
        tape_[curr_pos_] = curr_state_->put_zero_;
        mv = curr_state_->act_zero_;
        tmp = find_node(curr_state_->name_zero_, programm_);
      } else {
        break;
      }
    } else if (curr_ch == '1') {
      if (curr_state_->put_one_ != 'U') {
        tape_[curr_pos_] = curr_state_->put_one_;
        mv = curr_state_->act_one_;
        tmp = find_node(curr_state_->name_one_, programm_);
      } else {
        break;
      }
    }

    if (curr_pos_ + mv > tape_size_ - 1) {  // mv > 0
      curr_pos_ = curr_pos_ + mv - tape_size_;
    } else if (curr_pos_ + mv < 0) {  // mv < 0
      curr_pos_ = tape_size_ + mv;
    } else {
      curr_pos_ += mv;
    }

    if (tmp != nullptr) {
      curr_state_ = &(tmp->data);
      ++cnt;
    } else {
      fl = true;
      break;
    }

  }

  if (cnt >= maxsteps) {
    std::cout << "Not applicable" << std::endl;
    return cnt;
  }

  if (fl) {
    std::cout << cnt + 1 << std::endl;
  } else {
    std::cout << cnt << std::endl;
  }

  long long int idx = curr_pos_;
  long long int idx_buff = 0;
  char* buff = new char[tape_size_];
  long long int last_1 = 0;

  do {
    buff[idx_buff] = tape_[idx];
    if (buff[idx_buff] == '1') {
      last_1 = idx_buff;
    }
    if (idx + 1 > tape_size_ - 1) {  // mv > 0
      idx = idx + 1 - tape_size_;
    } else {
      idx += 1;
    }

    ++idx_buff;
  } while (idx != curr_pos_);

  for (size_t n = 0; n <= last_1; ++n) {
    std::cout << buff[n];
  }
  std::cout << std::endl;

  delete[] buff;
  return cnt;
}

unsigned long long TuringMachine::calc(std::string& tape, unsigned long long maxsteps) {
  unsigned long long res = 0;
  for (size_t i = 0; i < tape.size(); ++i) {
    tape_[i] = tape[i];
  }
  res = run(maxsteps);
  return res;
}

void del_spaces(char str[256]) {
  int i = 0;
  int j = 0;
  unsigned long int sz = strlen(str);
  int cnt = 0;

  for (i = 0; i < sz; i++) {
    if (str[i] != ' ' || (str[i] == ' ' && cnt == 0)) {
      str[j++] = str[i];
      cnt = (str[i] == ' ') ? 1 : 0;
    }
  }
  str[j] = '\0';
}

void add_state(char buff[256],list& prog) {
  char current_symbol;
  char name_current[16];
  char name_next[16] = {'U', 'N', 'D', 'E', 'F', '\0'};
  char name_default[16] = {'U', 'N', 'D', 'E', 'F', '\0'};
  char put_current = 'U';
  char put_default = 'U';
  int action_current = -2;
  int action_default = -2;

  del_spaces(buff);
  try {
    size_t idx = 0;
    size_t n = 0;

    while (buff[idx] != ' ') {
      name_current[n] = buff[idx];
      ++n;
      ++idx;
    }
    name_current[n] = '\0';

    ++idx;
    current_symbol = buff[idx];

    idx += 5;
    n = 0;
    while (buff[idx] != ' ') {
      name_next[n] = buff[idx];
      ++n;
      ++idx;
    }
    name_next[n] = '\0';

    ++idx;
    put_current = buff[idx];

    idx += 2;
    if (buff[idx] == 'R') {
      action_current = 1;
    } else if (buff[idx] == 'L') {
      action_current = -1;
    } else if (buff[idx] == 'N') {
      action_current = 0;
    } else {
      throw;
    }

  } catch (...) {
    std::cout << "Error" << std::endl;
    return;
  }
  


  state tmp_state;
  strncpy(tmp_state.name_, name_current, sizeof(name_current) - 1);
  if (current_symbol == '0') {
    strncpy(tmp_state.name_zero_, name_next, sizeof(name_next) - 1);
    strncpy(tmp_state.name_one_, name_default, sizeof(name_default) - 1);
    tmp_state.put_zero_ = put_current;
    tmp_state.put_one_ = put_default;
    tmp_state.act_zero_ = action_current;
    tmp_state.act_one_ = action_default;
  } else {
    strncpy(tmp_state.name_zero_, name_default, sizeof(name_default) - 1);
    strncpy(tmp_state.name_one_, name_next, sizeof(name_next) - 1);

    tmp_state.put_zero_ = put_default;
    tmp_state.put_one_ = put_current;

    tmp_state.act_zero_ = action_default;
    tmp_state.act_one_ = action_current;
  }
  if (prog.begin != nullptr) {

    node* current = find_node(name_current, prog);
    if (current == nullptr) {

      node* tmpn = new node;
      tmpn->next = nullptr;
      tmpn->prev = nullptr;
      tmpn->data = tmp_state;
      prog.end->next = tmpn;
      tmpn->prev = prog.end;
      prog.end = tmpn;

    } else {
      if (current_symbol == '0') {
        strncpy(current->data.name_zero_, name_next,
                sizeof(name_next));
        current->data.act_zero_ = action_current;
        current->data.put_zero_ = put_current;
      } else {
        strncpy(current->data.name_one_, name_next,
                sizeof(name_next));
        current->data.act_one_ = action_current;
        current->data.put_one_ = put_current;
      }
    }
  }
  else {
    node* tmpn = new node;
    tmpn->next = nullptr;
    tmpn->prev = nullptr;
    tmpn->data = tmp_state;
    prog.begin = prog.end = tmpn;
  }

}

void delete_list(list& ls) {
  node* current;
  while (ls.begin != nullptr) {
    current = ls.begin;
    ls.begin = ls.begin->next;
    delete current;
  }
  ls.end = nullptr;
}

node* find_node(char name[16], list& ls) {
  node* current = ls.begin;
  if (strcmp(name, "UNDEF") == 0) {
    return nullptr;
  }
  while (current != nullptr) {
    if (strcmp(current->data.name_, name) == 0) {
      return current;
    }
    current = current->next;
  }
  return nullptr;
}
