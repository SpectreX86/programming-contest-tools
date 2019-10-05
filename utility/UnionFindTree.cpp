#include <iostream>
#include <vector>
#include <stack>

template<class T>
class UnionFindTree{
public:
    UnionFindTree(const T N){
        tree = std::vector<T>(N);
        for(T i=0; i<N; ++i){
            tree[i] = i;
        }
        nGroup = N;
    }

    T root(const T idx){
        T tmp = idx;
        std::stack<T> stack;
        while(tree[tmp] != tmp){
            stack.push(tmp);
            tmp = tree[tmp];
        }
        while(!stack.empty()){
            tree[stack.top()] = tmp;
            stack.pop();
        }
        return tmp;
    }

    void merge(const T idx1, const T idx2){
        if(!same(idx1, idx2)){
            tree[root(idx1)] = root(idx2);
            --nGroup;
        }
    }

    bool same(const T idx1, const T idx2){
        return root(idx1) == root(idx2);
    }

    T groups(){
        return nGroup;
    }

private:
    std::vector<T> tree;
    T nGroup;
};

int main(int argc, char *argv[]){
    constexpr int N=6, M=5;
    UnionFindTree<int> tree(N);
    int X[M] = {1,2,1,4,5}, Y[M] = {2,3,3,5,6};
    for(int i=0; i<M; ++i){
        tree.merge(--X[i],--Y[i]);
    }

    std::cout << tree.groups() << std::endl;

    return 0;
}
