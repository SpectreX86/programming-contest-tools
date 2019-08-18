#include <iostream>
#include <vector>

//print vector in a line

template<class T>
void print(std::vector<T> &vector){
    for(const auto &v : vector){
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[]){
    std::vector<int> x{0,1,2,3};
    print(x);

    return 0;
}