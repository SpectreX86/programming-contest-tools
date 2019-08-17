#include <iostream>

unsigned long int GCD(unsigned long int m, unsigned long int n){
    unsigned long int r;
    while((r=m%n) != 0){
        m = n;
        n = r;
    }
    return n;
}

int main(int argc, char *argv[]){
    unsigned long int N=18l, M=12l;
    std::cout << GCD(N,M) << std::endl;
    return 0;
}
