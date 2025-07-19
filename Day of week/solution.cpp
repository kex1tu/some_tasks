#include <iostream>
#include <cstring>

const char* day_of_w(int Day, int Month, int Year){
    const char * day_of_week[] = {"Sunday", "Monday", "Tuesday", "Wednesday",
                                  "Thursday", "Friday", "Saturday" };
    if(Day == 29 && Year%4 !=0){
        return "0";
    }
    int a = (14-Month)/12;
    int y = Year - a;
    int m = Month - 2 +(12*a);
    int d = (Day + y + (y/4) - (y/100) + (y/400) + ((31*m)/12))%7;
    return day_of_week[d];
}
int next_year(int day, int month, int year){
    do{
        ++year;
    }while(std::strcmp(day_of_w(day, month, year), "Friday") != 0);
    return year;

}
int main(int argc, char *argv[])
{
    
    int Year;
    int Month;
    int Day;
    int mxdays;
    sscanf(argv[1], "%d.%d.%d", &Day, &Month, &Year);

 
    if(Month != 0){
        mxdays = 28 + (Month + Month / 8) % 2 + (2 % Month);
    }
    else{
        std::cout << "Unknown" << std::endl;
        return 0;
    }
    if(Month == 2 && Year % 4== 0 &&( Year%100!=0 || Year%400 == 0))
    {
        ++mxdays;
    }
    if(Day <1|| Day> mxdays || Month < 1 || Month > 12 || Year < 1){
        std::cout << "Unknown" <<std::endl;
        return 0;
    }
   
    
    const char* str = day_of_w(Day, Month, Year);
    std::cout << str << '\n';
    std::cout << next_year(Day, Month, Year) << '\n';
}
