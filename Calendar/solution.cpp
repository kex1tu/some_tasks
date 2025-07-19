#include <iostream>

void calendar_month(int& year, int& month);
void calendar_year(int& year);
const char* kvartals[] = { "January               February              March",
                              "April                 May                   June",
                              "July                  August                September",
                              "October               November              December" };

const char* monthes[] = { "January", "February", "March",
                              "April", "May","June",
                              "July","August","September",
                              "October", "November", "December" };

const char* days = "Su Mo Tu We Th Fr Sa";

int arr_days_in_monthes[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int main(int argc, char* argv[])
{

    int year;
    int month;
    /*проверки*/
    if (argc >= 2) {
        year = atoi(argv[argc - 1]);
        if (year < 0) {
            std::cout << "Unknown" << '\n';
            return 0;
        }
        if (argc == 2) {
            calendar_year(year);
        }
        if (argc == 3) {
            month = atoi(argv[1]);
            if (month < 0 || month > 12) {
                std::cout << "Unknown" << '\n';
                return 0;
            }
            calendar_month(year, month);
        }
    }
    else {
        std::cout << "Unknown" << '\n';
    }
    return 0;
}
int day_of_week(int& year, int& month, int day) {
    int a = (14 - month) / 12;
    int y = year - a;
    int m = month - 2 + (12 * a);
    int d = (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;

    return d;
}
void calendar_month(int& year, int& month) {
    std::cout << year << '\n';
    std::cout << monthes[month - 1] << '\n';
    std::cout << days << '\n';
    int days_in_month = 0;
    int fst_day = 0;

    if (month != 0) {
        days_in_month = arr_days_in_monthes[month - 1];
    }
    if (month == 2 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
    {
        ++days_in_month;
    }
    fst_day = day_of_week(year, month, 1);
    for (int spaces = 0; spaces < fst_day; ++spaces) {
        std::cout << "   ";
    }
    for (int day = 1; day < days_in_month + 1; ++day) {
        if (day < 10) {
            std::cout << " ";
        }
        std::cout << day;
        if (fst_day % 7 == 6) {
            std::cout << '\n';
        }
        else {
            if (day < days_in_month) {
                std::cout << " ";
            }
        }
        ++fst_day;
    }
    if (fst_day % 7 != 0) {
        std::cout << '\n';
    }
}
void calendar_year(int& year) {
    std::cout << year << '\n';
    for (int kvartal = 0; kvartal < 4; ++kvartal) {
        
        std::cout << kvartals[kvartal]<< '\n';
        for (int i = 0; i < 2; ++i) {
            std::cout << days << "  ";
        }
        std::cout << days << '\n';

        int last_days[3] = { 1, 1, 1 };
        bool lines = false;
        int mxdays[3] = { 0,0,0 };
        for (int i = 0; i < 3; ++i) {
            mxdays[i] = arr_days_in_monthes[kvartal * 3 + i];
            if (kvartal * 3 + i + 1 == 2 && year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))
            {
                ++mxdays[i];
            }
        }
        do {
            lines = false;
            for (int i = 0; i < 3; ++i) {
                if (last_days[i] <= mxdays[i]) {
                    int fst_day = kvartal * 3 + i + 1;
                    fst_day = day_of_week(year, fst_day, last_days[i]);
                    for (int spaces = 0; spaces < fst_day; ++spaces) {
                        std::cout << "   ";
                    }
                    for (int day = fst_day; day < 7 && last_days[i] <= mxdays[i]; ++day) {
                        if (last_days[i] < 10) {
                            std::cout << " ";
                        }
                        
                        std::cout << last_days[i];
                        if (day + 1 < 7 && last_days[i] + 1 <= mxdays[i]) {
                            std::cout << " ";
                        }
                        ++last_days[i];
                    }
                    if (i < 2 ){
                        fst_day = kvartal * 3 + i + 1;
                        fst_day = day_of_week(year, fst_day, last_days[i] - 1);
                        if (last_days[i+1] > mxdays[i+1]) {
                            if (i != 0 || last_days[i + 2] > mxdays[i + 2]) {
                                break;
                            }
                        }
                        else {
                            for (int spaces = 0; spaces < 7 - fst_day - 1; ++spaces) {
                                std::cout << "   ";
                            }
                        }


                    }
                }
                else {
                    std::cout << "                    ";
                }
                if (i < 2) {
                    std::cout << "  ";
                }
                if (last_days[i] <= mxdays[i]) {
                    lines = true;
                }

            }
            if (kvartal < 3 || lines) {
                std::cout << '\n';
            }
        } while (lines);
        std::cout << '\n';

    }
}
