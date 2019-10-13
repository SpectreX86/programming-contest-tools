#include <iostream>
#include <stack>
#include <queue>
#include <vector>

template<class T>
std::pair<std::vector<T>, std::vector<T> > getPrimeFactors(const T &N){
    const T zero = static_cast<T>(0);
    const T one = static_cast<T>(1);
    const T two = static_cast<T>(2);
    std::vector<T> F; //prime factors
    std::vector<T> E; //exponents
    T tmpN = N, tmpE;
    for(T i=two; i*i<=N; ++i){
        if(tmpN%i == zero){
            F.emplace_back(i);
            tmpE = zero;
            while(tmpN%i == zero){
                tmpN /= i;
                ++tmpE;
            }
            E.emplace_back(tmpE);
        }
    }
    if(tmpN > one){
        F.emplace_back(tmpN);
        E.emplace_back(one);
    }
    return std::make_pair(F,E);
}

int main(int argc, char *argv[]){
    constexpr long long N = 633755824LL;
    auto FE = getPrimeFactors(N);
    auto F = FE.first;
    auto E = FE.second;
    std::cout << N << " = ";
    for(int i=0; i<F.size(); ++i){
        std::cout << F[i] << "^" << E[i] << (i<F.size()-1 ? " * " : "\n");
    }
    std::cout << std::endl;
    return 0;
}
