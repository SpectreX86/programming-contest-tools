#include <iostream>

unsigned long int LCM(unsigned long int m, unsigned long int n){
    unsigned long int m_original = m;
    unsigned long int n_original = n;
    unsigned long int r;
    while((r=m%n) != 0){
        m = n;
        n = r;
    }
    return (m_original*n_original)/n;
}

int main(int argc, char *argv[]){
    unsigned long int N=18l, M=12l;
    std::cout << LCM(N,M) << std::endl;
    return 0;
}
