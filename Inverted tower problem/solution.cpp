#include <iostream>

int main() {
    unsigned long long int num = 0;
    std::cin >> num;
    unsigned long long int floor = 0;
    unsigned long long int tmp = 0;
    unsigned long long int i = 1;
    unsigned long long int sqri = 0;
  
    while (tmp < num) {
        sqri = i * i;
        if (tmp + sqri >= num || tmp >= num - sqri) {
            break;
        }
        tmp += sqri;
        floor += i;  
        ++i;
    }

    floor += 1 + (num - tmp-1)/i ;
    std::cout << floor << " ";

    std::cout << (num - tmp - ((num - tmp - 1) / i)*i)%(i+1);

    return 0;
}

