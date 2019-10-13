#include <iostream>
#include <stack>
#include <queue>
#include <vector>

template<class T>
std::vector<T> getDivisors(T N){
    T zero = static_cast<T>(0); 
    T one = static_cast<T>(1);
    std::queue<T> D_lower;
    std::stack<T> D_upper;
    for(T i=one; i*i<=N; ++i){
        if(N%i == zero){
            D_lower.emplace(i);
            if(i*i != N){
                D_upper.emplace(N/i);
            }
        }
    }
    std::vector<T> D;
    while(!D_lower.empty()){
        D.emplace_back(D_lower.front());
        D_lower.pop();
    }
    while(!D_upper.empty()){
        D.emplace_back(D_upper.top());
        D_upper.pop();
    }
    return D;
}

int main(int argc, char *argv[]){
    auto D = getDivisors(1024);
    for(auto d : D){
        std::cout << d << " ";
    }
    std::cout << std::endl;
    return 0;
}
