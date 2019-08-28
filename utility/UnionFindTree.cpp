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
        tree[root(idx1)] = root(idx2);
    }

    bool same(const T idx1, const T idx2){
        return root(idx1) == root(idx2);
    }

private:
    std::vector<T> tree;
};


int main(int argc, char *argv[]){
    constexpr int N=6, M=5;
    UnionFindTree<int> tree(N);
    int X[M] = {1,2,1,4,5}, Y[M] = {2,3,3,5,6};
    for(int i=0; i<M; ++i){
        tree.merge(--X[i],--Y[i]);
    }
    std::vector<int> roots(N,0);
    for(int i=0; i<N; ++i){
        roots[tree.root(i)] = 1;
    }
    int cost = 0;
    for(auto &element : roots){
        cost += element;
    }
    std::cout << cost << std::endl;

    return 0;
}
