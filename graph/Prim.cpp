#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <utility>
#include <string>

//find the minimum spanning tree of the graph with Prim's algorithm.

template<class T>
using Edge = std::map<std::string, T>; //for this algorithm, an edge must have "vertex" and "length" keys.
template<class T>
using Graph = std::map<T, std::vector<Edge<T> > >;
template<class T>
using Tree = std::map<T, std::vector<Edge<T> > >; //same class as graph. use different name for clarity.

//The id of a vertex in the graph must be in [0,V).
template<class T>
Tree<T> Prim(Graph<T> &graph, const T &V, const T &root){
    const T distanceSup = std::numeric_limits<T>::max();
    std::vector<T> distance(V, distanceSup);
    std::vector<T> predecessor(V, distanceSup);
    std::vector<bool> isVisited(V, false);
    distance[root] = 0;
    predecessor[root] = root;

    auto compare = [](const std::pair<T,T> &a, const std::pair<T,T> &b){
        return a.second > b.second;
    };
    std::priority_queue<std::pair<T,T>, std::vector<std::pair<T,T> >, decltype(compare)> queue(compare);
    queue.emplace(root,distance[root]);
    T pred, suc;
    T distTmp;
    while(!queue.empty()){
        pred = queue.top().first;
        if(isVisited[pred]){
            queue.pop();
            continue;
        }
        isVisited[pred] = true;
        queue.pop();

        for(auto &edge: graph[pred]){
            suc = edge["vertex"];
            if(isVisited[suc]){
                continue;
            }
            distTmp = edge["length"];
            if(distance[suc] > distTmp){
                distance[suc] = distTmp;
                predecessor[suc] = pred;
                queue.emplace(suc,distance[suc]);
            }
        }        
    }
    
    Tree<T> MST;
    for(suc=0; suc<V; ++suc){
        if(suc==root){
            continue;
        }
        pred = predecessor[suc];
        MST[pred].emplace_back(Edge<T>{{"child",suc},{"length",distance[suc]}});
    }

    return MST;
}

int main(int argc, char *argv[]){
    constexpr int N = 5;
    constexpr int M = 8;
    int u[M] = {0,0,0,1,2,2,3}, v[M] = {1,3,4,2,3,4,4};
    int w[M] = {2,8,4,3,5,1,7};
    Graph<int> graph;
    for(int i=0; i<M; ++i){
        graph[u[i]].emplace_back(Edge<int>{{"vertex",v[i]},{"length",w[i]}});
        graph[v[i]].emplace_back(Edge<int>{{"vertex",u[i]},{"length",w[i]}});
    }

    constexpr int root=0;
    auto test = Prim(graph, N, root);

    for(auto &edges : test){
        for(auto &edge : edges.second){
            std::cout << "parent: " << edges.first << "\t" << "child: " << edge["child"] << "\t" << "length: " << edge["length"] << std::endl;
        }
    }
    return 0;
}
