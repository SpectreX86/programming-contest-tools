#include <iostream>

template <class T>
T GCD(T m, T n){
    const T zero = static_cast<T>(0);
    T r;
    while((r=m%n) != zero){
        m = n;
        n = r;
    }
    return n;
}

int main(int argc, char *argv[]){
    unsigned long long N=18LL, M=12LL;
    std::cout << GCD(N,M) << std::endl;
    return 0;
}
