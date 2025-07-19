#include "datetime.h"
#include <cstring>
#include <iostream>


namespace DateTime {

bool operator==(const time& tm1, const time& tm2) {
  return tm1.tm() == tm2.tm();
}

bool operator!=(const time& tm1, const time& tm2) {
  return tm1.tm() != tm2.tm();
}

bool operator<(const time& tm1, const time& tm2) { return tm1.tm() < tm2.tm(); }

bool operator<=(const time& tm1, const time& tm2) {
  return tm1.tm() <= tm2.tm();
}

bool operator>(const time& tm1, const time& tm2) { return tm1.tm() > tm2.tm(); }

bool operator>=(const time& tm1, const time& tm2) {
  return tm1.tm() >= tm2.tm();
}

time::time(int hour, int minute, int second) : tm_(0) {
  if (hour >= 0 && hour < 24) {
    if (minute >= 0 && minute < 60) {
      if (second >= 0 && second < 60) {
        tm_ = hour * 3600 + minute * 60 + second;
      } else {
        throw std::invalid_argument("seconds must be between 0 and 59");
      }
    } else {
      throw std::invalid_argument("minutes must be between 0 and 59");
    }
  } else {
    throw std::invalid_argument("hours must be between 0 and 23");
  }
}

void time::add_hours(int nb_hours) {
  tm_ += nb_hours * 3600;
  if (tm_ >= 86400) {
    tm_ = 86399;
  }
  if (tm_ < 0) {
    tm_ = 0;
  }
}

void time::add_minutes(int nb_minutes) {
  tm_ += nb_minutes * 60;
  if (tm_ >= 86400) {
    tm_ = 86399;
  }
  if (tm_ < 0) {
    tm_ = 0;
  }
}

void time::add_seconds(int nb_seconds) {
  tm_ += nb_seconds;
  if (tm_ >= 86400) {
    tm_ = 86399;
  }
  if (tm_ < 0) {
    tm_ = 0;
  }
}

int monthes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

bool operator==(const date& dt1, const date& dt2) {
  return dt1.jdn() == dt2.jdn();
}

bool operator!=(const date& dt1, const date& dt2) {
  return dt1.jdn() != dt2.jdn();
}

bool operator<(const date& dt1, const date& dt2) {
  return dt1.jdn() < dt2.jdn();
}

bool operator<=(const date& dt1, const date& dt2) {
  return dt1.jdn() <= dt2.jdn();
}

bool operator>(const date& dt1, const date& dt2) {
  return dt1.jdn() > dt2.jdn();
}

bool operator>=(const date& dt1, const date& dt2) {
  return dt1.jdn() >= dt2.jdn();
}

date::date(int r) : day_(r) {
  if (r <= 0) {
    throw std::invalid_argument("day must be positive");
  }
}

date::date(int year, int month, int day) : day_(0) {
  if (year >= 0) {
    if (month >= 1 && month <= 12) {
      if (day >= 1 && ((month != 2 && day <= monthes[month - 1]) ||
                       (month == 2 && is_leapyear(year) && day <= 29) ||
                       (month == 2 && !is_leapyear(year) && day <= 28))) {
        int a = (14 - month) / 12;
        int y = year + 4800 - a;
        int m = month + 12 * a - 3;
        day_ = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 -
               32045;
      } else {
        throw std::invalid_argument("day is invalid");
      }
    } else {
      throw std::invalid_argument("month is invalid");
    }
  } else {
    throw std::invalid_argument("year is invalid");
  }
}

long long int date::jdn() const { return day_; }

int date::year() const {
  int a = day_ + 32044;
  int b = (4 * a + 3) / 146097;
  int c = a - (146097 * b) / 4;
  int d = (4 * c + 3) / 1461;
  int e = c - (1461 * d) / 4;
  int m = (5 * e + 2) / 153;
  return (100 * b + d - 4800 + (m / 10));
}

int date::month() const {
  int a = day_ + 32044;
  int b = (4 * a + 3) / 146097;
  int c = a - (146097 * b) / 4;
  int d = (4 * c + 3) / 1461;
  int e = c - (1461 * d) / 4;
  int m = (5 * e + 2) / 153;
  return (m + 3 - (12 * (m / 10)));
}

int date::day() const {
  int a = day_ + 32044;
  int b = (4 * a + 3) / 146097;
  int c = a - (146097 * b) / 4;
  int d = (4 * c + 3) / 1461;
  int e = c - (1461 * d) / 4;
  int m = (5 * e + 2) / 153;
  return (1 + e - (153 * m + 2) / 5);
}

weekday date::weekday() const {
  int d = day_ % 7;
  switch (d) {
    case 0:
      return weekday::monday;
    case 1:
      return weekday::tuesday;
    case 2:
      return weekday::wednesday;
    case 3:
      return weekday::thursday;
    case 4:
      return weekday::friday;
    case 5:
      return weekday::saturday;
    case 6:
      return weekday::sunday;
  }
  return weekday::monday;
}

bool date::is_leapyear() const { return is_leapyear(year()); }

void date::add_days(int nb_days) { day_ += nb_days; }

date date::next() const { return date(day_ + 1); }

date date::prev() const { return date(day_ - 1); }

bool date::is_leapyear(int year) {
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool operator==(const datetime& dt1, const datetime& dt2) {
  return (dt1.dt() == dt2.dt() && dt1.tm() == dt2.tm());
}

bool operator!=(const datetime& dt1, const datetime& dt2) {
  return (dt1.dt() != dt2.dt() || dt1.tm() != dt2.tm());
}

bool operator<(const datetime& dt1, const datetime& dt2) {
  return (dt1.dt() < dt2.dt() || (dt1.dt() == dt2.dt() && dt1.tm() < dt2.tm()));
}

bool operator<=(const datetime& dt1, const datetime& dt2) {
  return (dt1 < dt2 || dt1 == dt2);
}

bool operator>(const datetime& dt1, const datetime& dt2) {
  return (dt1.dt() > dt2.dt() || (dt1.dt() == dt2.dt() && dt1.tm() > dt2.tm()));
}

bool operator>=(const datetime& dt1, const datetime& dt2) {
  return (dt1 > dt2 || dt1 == dt2);
}

const char* to_cstr(const datetime& dt) {
  char* str = new char[20];
  str[0] = (char)(dt.year() / 1000 + '0');
  str[1] = (char)((dt.year() % 1000) / 100 + '0');
  str[2] = (char)((dt.year() % 100) / 10 + '0');
  str[3] = (char)(dt.year() % 10 + '0');
  str[4] = '.';
  str[5] = (char)(dt.month() / 10 + '0');
  str[6] = (char)(dt.month() % 10 + '0');
  str[7] = '.';
  str[8] = (char)(dt.day() / 10 + '0');
  str[9] = (char)(dt.day() % 10 + '0');
  str[10] = ' ';
  str[11] = (char)(dt.hour() / 10 + '0');
  str[12] = (char)(dt.hour() % 10 + '0');
  str[13] = ':';
  str[14] = (char)(dt.minute() / 10 + '0');
  str[15] = (char)(dt.minute() % 10 + '0');
  str[16] = ':';
  str[17] = (char)(dt.second() / 10 + '0');
  str[18] = (char)(dt.second() % 10 + '0');
  str[19] = '\0';
  return str;
}

datetime::datetime() : secs_(0), days_(0) {}

datetime::datetime(long long int n) {
  if (n >= 0) {
    secs_ = (int)(n % 86400);
    days_ = (int)(n / 86400);
  }
}

datetime::datetime(int year, int month, int day, int hour, int minute,
                   int second) {
  if (year >= 0) {
    if (month >= 1 && month <= 12) {
      if (day >= 1 && ((month != 2 && day <= monthes[month - 1]) ||
                       (month == 2 && is_leapyear(year) && day <= 29) ||
                       (month == 2 && !is_leapyear(year) && day <= 28))) {
        int a = (14 - month) / 12;
        int y = year + 4800 - a;
        int m = month + 12 * a - 3;
        days_ = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 -
                32045;
        if (hour >= 0 && hour < 24) {
          if (minute >= 0 && minute < 60) {
            if (second >= 0 && second < 60) {
              secs_ = hour * 3600 + minute * 60 + second;
            } else {
              throw std::invalid_argument("seconds must be between 0 and 59");
            }
          } else {
            throw std::invalid_argument("minutes must be between 0 and 59");
          }
        } else {
          throw std::invalid_argument("hours must be between 0 and 23");
        }
      } else {
        throw std::invalid_argument("day is invalid");
      }
    } else {
      throw std::invalid_argument("month is invalid");
    }
  } else {
    throw std::invalid_argument("year is invalid");
  }
}

long long int datetime::dt() const { return days_; }

long int datetime::tm() const { return secs_; }

int datetime::year() const {
  int a = days_ + 32044;
  int b = (4 * a + 3) / 146097;
  int c = a - (146097 * b) / 4;
  int d = (4 * c + 3) / 1461;
  int e = c - (1461 * d) / 4;
  int m = (5 * e + 2) / 153;
  return (100 * b + d - 4800 + (m / 10));
}

int datetime::month() const {
  int a = days_ + 32044;
  int b = (4 * a + 3) / 146097;
  int c = a - (146097 * b) / 4;
  int d = (4 * c + 3) / 1461;
  int e = c - (1461 * d) / 4;
  int m = (5 * e + 2) / 153;
  return (m + 3 - (12 * (m / 10)));
}

int datetime::day() const {
  int a = days_ + 32044;
  int b = (4 * a + 3) / 146097;
  int c = a - (146097 * b) / 4;
  int d = (4 * c + 3) / 1461;
  int e = c - (1461 * d) / 4;
  int m = (5 * e + 2) / 153;
  return (1 + e - (153 * m + 2) / 5);
}
int datetime::hour() const { return secs_ / 3600; }

int datetime::minute() const { return (secs_ % 3600) / 60; }

int datetime::second() const { return secs_ % 60; }

weekday datetime::weekday() const {
  int d = days_ % 7;
  switch (d) {
    case 0:
      return weekday::monday;
    case 1:
      return weekday::tuesday;
    case 2:
      return weekday::wednesday;
    case 3:
      return weekday::thursday;
    case 4:
      return weekday::friday;
    case 5:
      return weekday::saturday;
    case 6:
      return weekday::sunday;
  }
  return weekday::monday;
}

bool datetime::is_leapyear() const { return is_leapyear(year()); }

void datetime::add_days(int nb_days) { days_ += nb_days; }

void datetime::add_hours(int nb_hours) {
  secs_ += nb_hours * 3600;
  while (secs_ < 0) {
    secs_ += 86400;
    days_--;
  }
  days_ += secs_ / 86400;
  secs_ = secs_ % 86400;
}

void datetime::add_minutes(int nb_minutes) {
  secs_ += nb_minutes * 60;
  while (secs_ < 0) {
    secs_ += 86400;
    days_--;
  }
  days_ += secs_ / 86400;
  secs_ = secs_ % 86400;
}

void datetime::add_seconds(int nb_seconds) {
  secs_ += nb_seconds;
  while (secs_ < 0) {
    secs_ += 86400;
    days_--;
  }
  days_ += secs_ / 86400;
  secs_ = secs_ % 86400;
}

bool datetime::is_leapyear(int year) {
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

static bool is_leapyear(int year) {
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

bool valid_dt(int y, int m, int d, int ho, int mi, int se) {
  if (ho >= 0 && ho < 24 && mi >= 0 && mi < 60 && se >= 0 && se < 60) {
  } else {
    char str[9];
    str[0] = (char)(char)(ho / 10 + '0');
    str[1] = (char)(char)(ho % 10 + '0');
    str[2] = ':';
    str[3] = (char)(mi / 10 + '0');
    str[4] = (char)(mi % 10 + '0');
    str[5] = ':';
    str[6] = (char)(se / 10 + '0');
    str[7] = (char)(se % 10 + '0');
    str[8] = '\0';
    std::cout << "Time value is invalid: " << str << '\n';
    return false;
  }

  if (y >= 0) {
    if (m >= 1 && m <= 12) {
      if (d >= 1 && ((m != 2 && d <= monthes[m - 1]) ||
                     (m == 2 && is_leapyear(y) && d <= 29) ||
                     (m == 2 && !is_leapyear(y) && d <= 28))) {
      } else {
        std::cout << "Day value is invalid: " << d << '\n';
        return false;
      }
    } else {
      std::cout << "Month value is invalid: " << m << '\n';
      return false;
    }
  } else {
    std::cout << "Year value is invalid: " << y << '\n';
    return false;
  }

  return true;
}


}
