#include <iostream>

//compute x^(-1) modulo a prime number m for any positive integer x in [1,N]. 

template<unsigned long int N, unsigned long int m> class ModInv{
public:
    constexpr ModInv() : array(){
        for(unsigned long int i=1; i<=N; ++i){
            array[i-1]=this->getModInv(i);
        }
    }
    const unsigned long int &operator[](unsigned long int i) const {
        return array[i-1];
    }
private:
    unsigned long int array[N];
    constexpr unsigned long int getModInv(const unsigned int a) const {
        constexpr unsigned long int p = m-2;
        unsigned long int mod = 1;
        for(int j=63; j>=0; --j){
            mod = mod*mod % m;
            if( ((p>>j)&1)==1 ){
                mod = mod*a % m;
            }
        }
        return mod;
    }
};

int main(int argc, char *argv[]){
    constexpr unsigned long int m = 1000000000 + 7; //a prime modulus
    constexpr unsigned long int N = 1024; //maximum number for which you want to get the inverse number modulo a prime number
    constexpr auto inv = ModInv<N,m>();
    for(unsigned long int i=1; i<=N; ++i){
        std::cout << "x: " << i << ", x^(-1): " << inv[i] << ", x*x^(-1) mod m: " << (i*inv[i])%m << std::endl;
    }
    return 0;
}
