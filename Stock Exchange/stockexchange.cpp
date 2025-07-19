#include <iostream>
#include <fstream>
#include "database.h"

#define load_command 0
#define save_command 1
#define add_command 2
#define delete_command 3
#define clear_command 4
#define print_command 5
#define dom_command 6
#define export_command 7
#define quit_command 8



database dbas{nullptr, nullptr, 0};

static const char* commands[9] = {"load",  "save", "add", "delete", "clear",  "print", "dom",  "export", "quit"};


int menu() {
  std::cout << "> ";
  bool fl = false;
  int action = -1;
  char str[256];
  char command[256];
  std::cin >> command;

  std::cin.getline(str, 256);
  for (int i = 0; i < 9; ++i) {
    if (str_cmp(command, commands[i]) == 0) {
      fl = true;
      action = i;
      break;
    }
  }
  if (fl) {
    int idx = 0;
    int n = 0;
    char argument[256];
    del_spaces(str);
    switch (action) {
      case load_command: {
        while (str[idx] == ' ') {
          ++idx;
        }
        while (str[idx] != '\0') {
          argument[n++] = str[idx++];
        }
        argument[n] = '\0';
        load_db(dbas, argument);
        break;
      }
      case save_command: {
        while (str[idx] == ' ') {
          ++idx;
        }
        while (str[idx] != '\0') {
          argument[n++] = str[idx++];
        }
        argument[n] = '\0';
        save_db(dbas, argument);
        break;
      }
      case add_command: {
        while (str[idx] == ' ') {
          ++idx;
        }
        while (str[idx] != '\0') {
          argument[n++] = str[idx++];
        }
        argument[n] = '\0';
        request tmp = create_request(argument, false);
        if (tmp.bs != 'E') {
          add_request(dbas, tmp);
        }
        break;
      }
      case delete_command: {
        while (str[idx] == ' ') {
          ++idx;
        }
        while (str[idx] != '\0') {
          argument[n++] = str[idx++];
        }
        argument[n] = '\0';
        int id = atoi(argument);
        delete_request(dbas, id);
        break;
      }
      case clear_command: {
        clear_db(dbas);
        break;
      }
      case print_command: {
        print_db(dbas);
        break;
      }
      case dom_command: {
        while (str[idx] == ' ') {
          ++idx;
        }
        while (str[idx] != '\0') {
          argument[n++] = str[idx++];
        }
        argument[n] = '\0';
        dom(dbas, argument);
        break;
      }
      case export_command: {
        while (str[idx] == ' ') {
          ++idx;
        }
        while (str[idx] != '\0') {
          argument[n++] = str[idx++];
        }
        argument[n] = '\0';
        merge_sort(&dbas.begin, compare_requests_print);
        save_db(dbas, argument);
        break;
      }
      case quit_command: {
        delete_db(dbas);
        break;
      }
    }
  }
  else {
    std::cout << "Unknown command: " << command << std::endl;
  }
  return action;
}


int main(){

  while (menu() != quit_command) {
  }
    return 0;
}