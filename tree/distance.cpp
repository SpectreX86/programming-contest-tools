#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>

//calculate the distance of nodes from the root.

using Edge = std::map< std::string, long int>; //edges should have "child" and "length" keys.
using Tree = std::map<long int, std::vector<Edge> >;

std::vector<long int> measureDistance(long int root,  Tree tree){
    long int N = tree.size();
    std::vector<bool> isVisited(N,false);
    std::vector<long int> distance(N);
    std::stack<long int> stack;
    long int parent = root;
    distance[parent-1]=0l;
    isVisited[parent-1]=true;
    stack.push(parent);
    long int child;
    long int length;
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
    constexpr long int N=5; //number of nodes

    long int u[N-1] = {2l,2l,1l,3l},v[N-1]={5l,3l,3l,4l}; //nodes at the edge ends
    long int w[N-1] = {2l,10l,8l,2l}; //length of the edges

    //construct tree structure
    Tree tree; //tree structure
    Edge edge;
    for(long int i=0; i<N-1; ++i){
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
