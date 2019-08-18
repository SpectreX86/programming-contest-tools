#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>

//get the parents of each node.

template<class T>
using Edge = std::map< std::string, T>; //each edge must have "child" key for this calculation
template<class T>
using Tree = std::map<T, std::vector<Edge<T> > >;

template<class T>
std::vector<T> getParent(T root, Tree<T> tree){
    T N = tree.size();
    std::vector<bool> isVisited(N,false);
    std::vector<T> parents(N);
    std::stack<T> stack;
    T parent = root;
    parents[parent-1] = parent;
    isVisited[parent-1]=true;
    stack.push(parent);
    T child;
    while(!stack.empty()){
        parent = stack.top();
        stack.pop();
        for(auto &edge : tree[parent]){
            child = edge["child"];
            if(!isVisited[child-1]){
                parents[child-1] = parent;
                isVisited[child-1] = true;
                stack.push(child);
            }
        }
    }
    return parents;
}

int main(int argc, char *argv[]){
    constexpr int N=5; //number of nodes

    int u[N-1] = {2,2,1,3},v[N-1]={5,3,3,4}; //nodes at the edge ends

    Tree<int> tree;
    Edge<int> edge;
    for(int i=0; i<N-1; ++i){
        edge.clear();
        edge["child"] = v[i];
        tree[u[i]].emplace_back(edge);
        edge["child"] = u[i];
        tree[v[i]].emplace_back(edge);
    }

    auto parents = getParent(1,tree);
    for(auto &p : parents){
        std::cout << p << std::endl;
    }

    return 0;
}