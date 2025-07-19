#include <stdexcept>
#include <string>

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
  int tm() const;
  int hour() const;
  int minute() const;
  int second() const;
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
std::string to_string(const time& tm);

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
  DateTime::weekday weekday() const;
  bool is_leapyear() const;
  void add_days(int nb_days);
  date next() const;
  date prev() const;
  static bool is_leapyear(int year);
  date& operator++();
  date operator++(int);
  date& operator--();
  date operator--(int);
};

bool operator==(const date& dt1, const date& dt2);
bool operator!=(const date& dt1, const date& dt2);
bool operator<(const date& dt1, const date& dt2);
bool operator<=(const date& dt1, const date& dt2);
bool operator>(const date& dt1, const date& dt2);
bool operator>=(const date& dt1, const date& dt2);
std::string to_string(const date& dt);

class datetime {
 private:
  int secs_;
  int days_;

 public:
  datetime(long long int n = 0);
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
  DateTime::weekday weekday() const;
  bool is_leapyear() const;
  void add_days(int nb_days);
  void add_hours(int nb_hours);
  void add_minutes(int nb_minutes);
  void add_seconds(int nb_seconds);
  static bool is_leapyear(int year);
};

bool operator==(const datetime& dt1, const datetime& dt2);
bool operator!=(const datetime& dt1, const datetime& dt2);
bool operator<(const datetime& dt1, const datetime& dt2);
bool operator<=(const datetime& dt1, const datetime& dt2);
bool operator>(const datetime& dt1, const datetime& dt2);
bool operator>=(const datetime& dt1, const datetime& dt2);
std::string to_string(const datetime& dt);

class timediff {
 private:
  long long int secs_;

 public:
  timediff(long long int s);
  timediff(int days, int hours, int minutes, int seconds);
  int days() const;
  int hours() const;
  int minutes() const;
  int seconds() const;
  long long int total_hours() const;
  long long int total_minutes() const;
  long long int total_seconds() const;
};

bool operator==(const timediff& td1, const timediff& td2);
bool operator!=(const timediff& td1, const timediff& td2);
bool operator<(const timediff& td1, const timediff& td2);
bool operator<=(const timediff& td1, const timediff& td2);
bool operator>(const timediff& td1, const timediff& td2);
bool operator>=(const timediff& td1, const timediff& td2);
timediff operator+(const timediff& td1, const timediff& td2);
datetime operator+(const datetime& dt1, const timediff& ts1);
timediff operator-(const timediff& td1, const timediff& td2);
timediff operator-(const time& tm1, const time& tm2);
timediff operator-(const date& dt1, const date& dt2);
timediff operator-(const datetime& dt1, const datetime& dt2);
datetime operator-(const datetime& dt1, const timediff& ts1);

}  // namespace DateTime
