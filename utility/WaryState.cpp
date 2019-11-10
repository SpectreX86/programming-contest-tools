#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <cmath>
#include <algorithm>
#include <array>

//express state by w-ary. w is stride.

constexpr int getStride(int nStates){
    --nStates;
    int stride = 0;
    while(nStates != 0){
        ++stride;
        nStates >>= 1;
    }
    return stride;
}
constexpr int nStates = 4;
constexpr int stride = getStride(nStates);

constexpr int nElements = 3;
using State = std::array<int, nElements>;

using T = int;
T toID(const State &S){
    T id = 0;
    for(int i=0; i<nElements; ++i){
        id <<= stride;
        id |= S[i];
    }
    return id;
}
State toState(T id){
    State S;
    for(int i=0; i<nElements; ++i){
        S[nElements-1 - i] = id&((1<<stride)-1);
        id >>= stride;
    }
    return S;
}

int main(int argc, char *argv[]){
    for(int i=0; i<64; ++i){
        std::cout << "state: " << toState(i)[0] << " " << toState(i)[1] << " " << toState(i)[2] << ", id: " << toID(toState(i)) << std::endl;
    }
    return 0;
}
