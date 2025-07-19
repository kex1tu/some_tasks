#pragma once
#include <stdexcept>

namespace DateTime {

enum class weekday {
  sunday,
  monday,
  tuesday,
  wednesday,
  thursday,
  friday,
  saturday
};

class time {
 private:
  int tm_;

 public:
  time(int hour = 0, int minute = 0, int second = 0);

  int tm() const { return tm_; }
  int hour() const { return tm_ / 3600; }
  int minute() const { return (tm_ % 3600) / 60; }
  int second() const { return tm_ % 60; }
  void add_hours(int nb_hours);
  void add_minutes(int nb_minutes);
  void add_seconds(int nb_seconds);
};

bool operator==(const time& tm1, const time& tm2);
bool operator!=(const time& tm1, const time& tm2);
bool operator<(const time& tm1, const time& tm2);
bool operator<=(const time& tm1, const time& tm2);
bool operator>(const time& tm1, const time& tm2);
bool operator>=(const time& tm1, const time& tm2);

extern int monthes[12];

class date {
 private:
  int day_;

 public:
  date(int r);
  date(int year, int month, int day);
  long long int jdn() const;
  int year() const;
  int month() const;
  int day() const;
  weekday weekday() const;
  bool is_leapyear() const;
  void add_days(int nb_days);
  date next() const;
  date prev() const;
  static bool is_leapyear(int year);
};

bool operator==(const date& dt1, const date& dt2);
bool operator!=(const date& dt1, const date& dt2);
bool operator<(const date& dt1, const date& dt2);
bool operator<=(const date& dt1, const date& dt2);
bool operator>(const date& dt1, const date& dt2);
bool operator>=(const date& dt1, const date& dt2);

class datetime {
 private:
  int secs_;
  int days_;

 public:
  datetime();
  datetime(long long int n);
  datetime(int year, int month, int day, int hour = 0, int minute = 0,
           int second = 0);
  long long int dt() const;
  long int tm() const;
  int year() const;
  int month() const;
  int day() const;
  int hour() const;
  int minute() const;
  int second() const;
  weekday weekday() const;
  bool is_leapyear() const;
  void add_days(int nb_days);
  void add_hours(int nb_hours);
  void add_minutes(int nb_minutes);
  void add_seconds(int nb_seconds);
  static bool is_leapyear(int year);
};

const char* to_cstr(const datetime& dt);

bool operator==(const datetime& dt1, const datetime& dt2);
bool operator!=(const datetime& dt1, const datetime& dt2);
bool operator<(const datetime& dt1, const datetime& dt2);
bool operator<=(const datetime& dt1, const datetime& dt2);
bool operator>(const datetime& dt1, const datetime& dt2);
bool operator>=(const datetime& dt1, const datetime& dt2);


static bool is_leapyear(int year);
bool valid_dt(int y, int m, int d, int ho, int mi, int se);
}
