#include "database.h"
#include <cmath>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "datetime.h"


int monthes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int str_cmp(const char a[], const char b[]) {
  unsigned long int sz_a = strlen(a);
  unsigned long int sz_b = strlen(b);
  if (sz_a != sz_b) {
    return 1;
  }
  for (int i = 0; i < sz_a; ++i) {
    if (tolower(a[i]) != tolower(b[i])) {
      return 2;
    }
  }
  return 0;
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

request create_request(char str[256],
    bool fl) {  // fl = false - load from file. fl = true - from console
  request tmp;
  int idx = 0;
  for (unsigned long int i = 0; i < strlen(str); ++i) {
    str[i] = (str[i] == ',') ? ' ' : str[i];
  }
  del_spaces(str);
  char strc[256] = "\0";
  char strcint[256] = "\0";
  char strcdouble[256] = "\0";
  char date[11] = "\0";
  char time[9] = "\0";
  char datetime1[20] = "\0";
  char datetime2[20] = "\0";
  char name[16] = "\0";
  char action[5] = "\0";
  int n = 0;

  for (idx = 0; idx < 10; ++idx) {
    date[n++] = str[idx];
  }
  int day;
  int month;
  int year;
  if (sscanf(date, "%d. %d. %d", &year, &month, &day) != 3) {
    std::cout << "Wrong date format: " << date << std::endl;
    return tmp;
  }

  ++n;
  for (; n < 19; ++n) {
    time[n-11] = str[n];
  }
  int sec;
  int min;
  int hour;
  if (sscanf(time, "%d: %d: %d", &hour, &min, &sec) != 3) {
    std::cout << "Wrong time format: " << time << std::endl;
    return tmp;
  }

  while ((str[idx] < 'a' || str[idx] > 'z') &&
         (str[idx] < 'A' || str[idx] > 'Z') && (idx < strlen(str))) {
    ++idx;
  }
  n = 0;
  while (((str[idx] >= 'a' && str[idx] <= 'z') ||
          (str[idx] >= 'A' && str[idx] <= 'Z')) &&
         (idx < strlen(str) && n < sizeof(name) / sizeof(char))) {
    name[n] = str[idx];
    ++n;
    ++idx;
  }
  while ((str[idx] < 'a' || str[idx] > 'z') &&
         (str[idx] < 'A' || str[idx] > 'Z') && idx < strlen(str)) {
    ++idx;
  }
  n = 0;
  while (((str[idx] >= 'a' && str[idx] <= 'z') ||
          (str[idx] >= 'A' && str[idx] <= 'Z')) &&
         (n <= strlen(action))) {
    action[n] = str[idx];
    ++n;
    ++idx;
  }
  while ((str[idx] < '0' || str[idx] > '9') && idx < strlen(str)) {
    ++idx;
  }
  for (int i = idx; i < strlen(str); ++i) {
    strc[i - idx] = str[i];
  }
  n = 0;
  idx = 0;
  while ((strc[n] < '0' || strc[n] > '9') && n < strlen(strc)) {
    ++n;
  }
  while (strc[n] >= '0' && strc[n] <= '9') {
    strcint[idx++] = strc[n++];
  }
  idx = 0;
  while ((strc[n] < '0' || strc[n] > '9') && n < strlen(strc)) {
    ++n;
  }
  while ((strc[n] >= '0' && strc[n] <= '9') || strc[n] == '.') {
    strcdouble[idx++] = strc[n++];
  }
  
  if (!fl) {
    std::swap(year, day);
  }
  if (DateTime::valid_dt(year, month, day, hour, min, sec)) {
    double pr;
    DateTime::datetime one_day(year, month, day, hour, min, sec);
    tmp.bs = (str_cmp(action, "sell") == 0 || str_cmp(action, "buy") == 0)
                 ? action[0]
                 : 'E';
    if (tmp.bs == 'E') {
      std::cout << "Unknown command: " << action << std::endl;
    }
    if (strlen(strcint) > 0) {
      tmp.count = atoi(strcint);
    } else {
      tmp.count = -1;
    }
    tmp.dt = one_day;
    if (strlen(strcdouble) > 0) {
      sscanf(strcdouble, "%lf", &pr);
      tmp.price = pr;
    } else {
      tmp.price = -1;
    }
    if (tmp.price == -1 || tmp.count == -1) {
      tmp.bs = 'E';
      std::cout << "Unknown command" << std::endl;
    }
    strncpy(tmp.ticker, name, sizeof(tmp.ticker) - 1);
    tmp.ticker[sizeof(tmp.ticker) - 1] = '\0'; 
  } else {
    tmp.bs = 'E';
  }
  return tmp;
}

int add_request(database& DB, const request& rn) {
  request r = rn;
  r.id = 0;
  node* tmpn = new node;
  tmpn->data = r;
  tmpn->data.id = DB.last_id + 1;
  tmpn->next = nullptr;
  tmpn->prev = nullptr;

  node* current = DB.begin;
  node* currentn;
  request tmpr;
  tmpr.dt = {3000, 1, 1, 0, 0, 0};
  tmpr.count = 0;
  double mxpr = 0;
  if (r.bs == 'b') {
    mxpr = INFINITY;
  } else {
    mxpr = -1;
  }
  while (mxpr != 0 && r.count != 0 && current != nullptr) {
    currentn = current->next;
    if (str_cmp(current->data.ticker, r.ticker) == 0) {
      if (current->data.count != 0) {
        if (current->data.bs != r.bs) {
          if (r.bs == 's') {
            if (mxpr == current->data.price) {
              if (current->data.dt < tmpr.dt) {
                tmpr = (current->data);
                mxpr = tmpr.price;
              }
            } else if (current->data.price > mxpr) {
              tmpr = (current->data);
              mxpr = tmpr.price;
            }
          } else if (r.bs == 'b') {
            if (mxpr == current->data.price) {
              if (current->data.dt < tmpr.dt) {
                tmpr = (current->data);
                mxpr = tmpr.price;
              }
            } else if (mxpr > current->data.price) {
              tmpr = (current->data);
              mxpr = tmpr.price;
            }
          }
        }
      }
    }

    if (current == DB.end && mxpr != 0 &&
        ((mxpr >= r.price && r.bs == 's') ||
         (mxpr <= r.price && r.bs == 'b'))) {
      if (tmpr.count >= r.count) {
        tmpr.count -= r.count;
        r.count = 0;
        request* tmp_update = get_pto_request(DB, tmpr.id);
        tmp_update->count = tmpr.count;
        if (r.bs == 'b') {
          mxpr = INFINITY;
        } else {
          mxpr = -1;
        }
      } else {
        if (r.bs == 'b') {
          mxpr = INFINITY;
        } else {
          mxpr = -1;
        }
        r.count -= tmpr.count;
        tmpr.count = 0;
        request* tmp_update = get_pto_request(DB, tmpr.id);
        tmp_update->count = tmpr.count;
      }
      tmpr.dt = {3000, 1, 1, 0, 0, 0};
      currentn = DB.begin;
    }
    current = currentn;
  }

  if (DB.begin != nullptr) {
    r.id = ++DB.last_id;
    tmpn->data = r;
    DB.end->next = tmpn;
    tmpn->prev = DB.end;
    DB.end = tmpn;
  } else {
    r.id = ++DB.last_id;
    tmpn->data = r;
    DB.begin = DB.end = tmpn;
  }

  return DB.last_id;
}

void delete_request(database& DB, const node* index) {
  if (index == nullptr) {
    return;
  }
  if (index->prev != nullptr) {
    index->prev->next = index->next;
  } else {
    DB.begin = index->next;
  }
  if (index->next != nullptr) {
    index->next->prev = index->prev;
  } else {
    DB.end = index->prev;
  }
  delete index;
}

void delete_request(database& DB, int idx) {
  node* current = DB.begin;
  while (current != nullptr) {
    if (current->data.id == idx) {
      delete_request(DB, current);
      return;
    }
    current = current->next;
  }
}


request* get_pto_request(database& DB, int idx) {
  request* tmp = nullptr;
  if (idx > 0) {
    node* current = DB.begin;
    while (current != nullptr) {
      if (current->data.id == idx) {
        tmp = &current->data;
        break;
      }
      current = current->next;
    }
  }
  return tmp;
}

void print_db(database& DB) {
  merge_sort(&DB.begin, compare_requests_print);
  node* current = DB.begin;
  std::cout << "ID      DATE                 TICKER   TYPE   COUNT   PRICE"
            << std::endl;
  while (current != nullptr) {
    const request tmp = current->data;
    print_info(tmp);
    current = current->next;
  }
}

void print_info(const request& req) {
  std::cout << req.id << "        ";
  const char* out = DateTime::to_cstr(req.dt);
  std::cout << out;
  delete[] out;
  std::cout << "     " << req.ticker;
  std::cout << "     " << req.bs << "     " << req.count << "      "
            << std::fixed << std::setprecision(2) << req.price;
  std::cout << '\n';
}

void print_info_dom(const request& req) {
  (req.bs == 'b') ? std::cout << "buy," : std::cout << "sell,";
  std::cout << " " << std::fixed << std::setprecision(2) << req.price;
  std::cout << ", " << req.count << ", ";
  const char* out = DateTime::to_cstr(req.dt);
  std::cout << out << std::endl;
  delete[] out;
}

void save_db(const database& DB, const char filename[]) {
  std::ofstream ofs(filename);
  if (ofs) {
    const node* current = DB.begin;
    while (current != nullptr) {
      const char* out = DateTime::to_cstr(current->data.dt);
      ofs << out << ", ";
      delete[] out;
      ofs << current->data.ticker << ", ";
      (current->data.bs == 'b') ? ofs << "buy" : ofs << "sell";
      ofs << ", ";
      ofs << current->data.count << ", ";
      ofs << std::fixed << std::setprecision(2) << current->data.price << '\n';
      current = current->next;
    }
  } else {
    std::cout << "Can not open";
    printf("%s", filename);
  }
  ofs.close();
}

void delete_db(database& DB) {
  node* current;
  while (DB.begin != nullptr) {
    current = DB.begin;
    DB.begin = DB.begin->next;
    delete current;
  }
  DB.end = nullptr;
  DB.last_id = 0;
}

void load_db(database& DB, const char filename[]) {
  std::ifstream ifs(filename);
  delete_db(DB);
  if (ifs) {
    request tmp;
    if (ifs) {
      char str[256];
      while (ifs.getline(str, 256)) {
        tmp = create_request(str, true);
        if (tmp.bs != 'E') {
          add_request(DB, tmp);
        }
      }
    }
    ifs.close();
  } else {
    std::cout << "Can not open database" << std::endl;
    //std::cout << filename << std::endl;
  }
  ifs.close();
}

void clear_db(database& DB) {
  node* current = DB.begin;
  node* currentn;
  while (current != nullptr) {
    currentn = current->next;
    if (current->data.count == 0) {
      delete_request(DB, current);
    }
    current = currentn;
  }
}

node* merge_sorted_lists(node* list_a, node* list_b,
                         bool (*compare)(const request&, const request&)) {
  if (list_a == nullptr) {
    return list_b;
  }
  if (list_b == nullptr) {
    return list_a;
  }

  node* result = nullptr;
  node* tail = nullptr;

  while (list_a!= nullptr && list_b != nullptr) {
    node* temp = nullptr;
    if (compare(list_a->data, list_b->data)) {
      temp = list_a;
      list_a = list_a->next;
    } else {
      temp = list_b;
      list_b = list_b->next;
    }

    if (result == nullptr) {
      result = temp;
    } else {
      tail->next = temp;
    }
    temp->prev = tail;
    tail = temp;
  }

  if (list_a != nullptr) {
    tail->next = list_a;
    list_a->prev = tail;
  } else if (list_b != nullptr) {
    tail->next = list_b;
    list_b->prev = tail;
  }

  return result;
}

void split_list(node* source, node** first, node** second) {
  node* tmp; // go to the end, while midl go to the mid
  node* midl; //go to the mid  
  midl = source;
  tmp = source->next;

  while (tmp != nullptr) {
    tmp = tmp->next;
    if (tmp!=nullptr) {
      midl = midl->next;
      tmp = tmp->next;
    }
  }

  *first = source;
  *second = midl->next;
  midl->next = nullptr;
}

bool compare_requests_dom(const request& a, const request& b) {
  if (a.price != b.price) {
    return a.price > b.price;
  }
  if (a.bs != b.bs) {
    return a.bs == 's';
  }
  if (a.bs == 's') {
    return compare_requests_print(b, a);
  }
  return compare_requests_print(a, b);
}

bool compare_requests_print(const request& a, const request& b) {
  if (a.dt == b.dt) {
    return a.price > b.price;
  }
  return a.dt < b.dt;
}

void merge_sort(node** ptr_to_head,
                bool (*compare)(const request&, const request&)) {
  node* head = *ptr_to_head;
  if (head == nullptr || head->next == nullptr) {
    return;
  }

  node* a;
  node* b;
  split_list(head, &a, &b);

  merge_sort(&a, compare);
  merge_sort(&b, compare);

  *ptr_to_head = merge_sorted_lists(a, b, compare);
}

void dom(database& DB, const char* ticker) {
  node* filtered_list = nullptr;
  node* last = nullptr;

  node* current = DB.begin;
  while (current != nullptr) {
    if (str_cmp(current->data.ticker, ticker) == 0 &&
        current->data.count > 0) {
      node* new_node = new node;
      new_node->data = current->data;
      new_node->next = nullptr;
      new_node->prev = last;
      if (last != nullptr) {
        last->next = new_node;
      } else {
        filtered_list = new_node;
      }
      last = new_node;
    }
    current = current->next;
  }

  merge_sort(&filtered_list, compare_requests_dom);
  current = filtered_list;
  while (current != nullptr) {
    print_info_dom(current->data);
    node* temp = current;
    current = current->next;
    delete temp;
  }
}