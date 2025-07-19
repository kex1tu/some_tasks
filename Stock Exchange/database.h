#pragma once
#include "datetime.h"

struct request {
  char ticker[16];
  char bs;
  int count;
  double price;
  int id;
  DateTime::datetime dt;
};

struct node {
  request data;
  node* next;
  node* prev;
};

struct database {
  node* begin;
  node* end;
  int last_id = 0;
};
request create_request(char str[256], bool fl);
int str_cmp(const char a[], const char b[]);
void del_spaces(char str[256]);
int add_request(database& DB, const request& rn);
void delete_request(database& DB, const node* index);
void delete_request(database& DB, int idx);
request* get_pto_request(database& DB, int idx);
void print_db(database& DB);
void print_info(const request& req);
void save_db(const database& DB, const char filename[]);
void delete_db(database& DB);
void load_db(database& DB, const char filename[]);
node* merge_sorted_lists(node* a, node* b, bool (*compare)(const request&, const request&));
void split_list(node* source, node** first, node** second);
void merge_sort(node** ptr_to_head, bool (*compare)(const request&, const request&));
bool compare_requests_dom(const request& a, const request& b);
void dom(database& DB, const char* ticker);
bool compare_requests_print(const request& a, const request& b);
void clear_db(database& DB);