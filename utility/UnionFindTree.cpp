#include <iostream>
#include <vector>
#include <stack>
#include <numeric>

template<class T>
class UnionFindTree{
public:
    UnionFindTree(const T N){
        const T zero = static_cast<T>(0);
        const T one = static_cast<T>(1);

        tree = std::vector<T>(N);
        std::iota(tree.begin(),tree.end(),zero);

        sizes = std::vector<T>(N,one);

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
            sizes[root(idx2)] = size(idx1) + size(idx2);
            tree[root(idx1)] = root(idx2);
            --nGroup;
        }
    }

    bool same(const T idx1, const T idx2){
        return root(idx1) == root(idx2);
    }

    T size(const T idx){
        return sizes[root(idx)];
    }

    T groups(){
        return nGroup;
    }

private:
    std::vector<T> tree; //parents of each nodes
    std::vector<T> sizes; //memory for the size of each group which includes each node (sizes[root(idx)] is the size of the group which includes idx, not sizes[idx] it self).
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
