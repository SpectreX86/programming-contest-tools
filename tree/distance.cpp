#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>

//calculate the distance of nodes from the root.

template<class T>
using Edge = std::map< std::string, T>; //each edge must have "child" and "length" keys for this calculation
template<class T>
using Tree = std::map<T, std::vector<Edge<T> > >;

template<class T>
std::vector<T> measureDistance(T root,  Tree<T> tree){
    T N = tree.size();
    std::vector<bool> isVisited(N,false);
    std::vector<T> distance(N);
    std::stack<T> stack;
    T parent = root;
    distance[parent-1]=static_cast<T>(0);
    isVisited[parent-1]=true;
    stack.push(parent);
    T child;
    T length;
    while(!stack.empty()){
        parent = stack.top();
        stack.pop();
        for(auto &edge : tree[parent]){
            child = edge["child"];
            length = edge["length"];
            if(!isVisited[child-1]){
                distance[child-1] = distance[parent-1]+length;
                isVisited[child-1] = true;
                stack.push(child);
            }
        }
    }
    return distance;
}

int main(int argc, char *argv[]){
    constexpr int N=5; //number of nodes

    int u[N-1] = {2,2,1,3},v[N-1]={5,3,3,4}; //nodes at the edge ends
    int w[N-1] = {2,10,8,2}; //length of the edges

    //construct tree structure
    Tree<int> tree; //tree structure
    Edge<int> edge;
    for(int i=0; i<N-1; ++i){
        edge.clear();
        edge["length"] = w[i];
        edge["child"] = v[i];
        tree[u[i]].emplace_back(edge);
        edge["child"] = u[i];
        tree[v[i]].emplace_back(edge);
    }

    //measure distance
    auto distance = measureDistance(1,tree);
    for(const auto &d : distance){
        std::cout << d << std::endl;
    }
    return 0;
}
