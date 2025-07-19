#include <iostream>

int main()
{
    unsigned long long r;
    std::cin >> r;
    unsigned long long tmp; 
    unsigned long long cnt = 0;
    unsigned long long sqr = r * r;
    unsigned long long y = 1;
    unsigned long long x = r - 1;

    for(;y<r;++y) {
        tmp = y * y;
        while (x * x + tmp > sqr){
            --x;
        }
        cnt += x;
    }
    std::cout << 4*(cnt + r) + 1;
    return 0;
}
