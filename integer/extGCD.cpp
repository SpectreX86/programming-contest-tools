#include <iostream>
#include <stack>
#include <cstdlib>

//solve ax + by = c
template<class T>
T extGCD(T a, T b, T c, T &x, T &y, T &dx, T &dy){
    //calculate the gcd(a,b)
    T m = a;
    T n = b;
    T r;
    std::stack<T> q; //quotients
    if(n!=0){
        while((r=m%n) != 0){
            q.emplace(m/n);
            m = n;
            n = r;
        }
        q.emplace(m/n);
    }else if(m!=0){
        n = m;
    }else{
        return 0; //any pair of integers (x,y) is a solution.
    }
    T d = std::abs(n); //gcd

    //check if the equation has solutions.
    if(c%d != 0){
        return -1; //no solution exists
    }
    a = a/d;
    b = b/d;
    c = c/d;
    dx = b;
    dy = -a;

    x = 1;
    y = 0;
    while(!q.empty()){
        r = x;
        x = y;
        y = r - q.top()*y;
        q.pop();
    }
    x *= c;
    y *= c;
    return d;
}

int main(int argc, char *argv[]){
    int a=111, b=30, c=6;
    std::cout << "Solve " << a << "x + " << b << "y = " << c << std::endl;
    int x,y;
    int dx, dy;
    int d = extGCD(a,b,c,x,y,dx,dy);
    if(d==-1){
        std::cout << "No solutions." << std::endl;
    }else if(d==0){
        std::cout << "Any pair of integers (x,y) is a solution." << std::endl;
    }else{
        std::cout << "GCD = " << d 
            << ", x = " << x << (dx>=0? " + " : " - ") << std::abs(dx) << "k"
            << ", y = " << y << (dy>=0? " + " : " - ") << std::abs(dy) << "k"
            << std::endl;
    }
    return 0;
}
