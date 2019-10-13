#include <iostream>
#include <vector>
#include <stack>
#include <limits>
#include <utility>
#include <numeric>

//topological sort

template<class T>
using Edge = std::pair<T, T>; //pair of the id of the successor and the length of the edge.
template<class T>
using Graph = std::vector<std::vector<Edge<T> > >;

//V is the number of the vertices of the graph. The id of a vertex in the graph must be in [0,V).
template<class T>
std::pair<T, std::vector<T> > tsort(Graph<T> &graph){
    const T V = graph.size();

    std::vector<T> sorted;

    T pred, suc;
    std::stack<T> stack;
    std::vector<T> in(V,0);
    T remainder = 0;
    for(pred=0; pred<V; ++ pred){
        for(auto &edge : graph[pred]){
            suc = edge.first;
            ++in[suc];
            ++remainder;
        }
    }
    for(pred=0; pred<V; ++ pred){
        if(in[pred]==0){
            stack.emplace(pred);
        }
    }

    while(!stack.empty()){
        pred = stack.top();
        stack.pop();
        sorted.emplace_back(pred);
        for(auto &edge : graph[pred]){
            suc = edge.first;
            --in[suc];
            --remainder;
            if(in[suc] == 0){
                stack.emplace(suc);
            }
        }
    }

    return std::make_pair(remainder, sorted);
}

int main(int argc, char *argv[]){
    constexpr int N = 7;
    constexpr int M = 10;
    int u[M] = {0,1,2,3,2,4,1,0,6,6}, v[M] = {1,2,3,5,4,5,4,6,3,2};
    int w[M] = {1,1,1,1,1,1,1,1,1,1};
    Graph<int> graph(N);
    for(int i=0; i<M; ++i){
        graph[u[i]].emplace_back(v[i],w[i]);
    }

    auto topo = tsort(graph);// topological sort

    //detect cycles
    if(topo.first > 0){
        std::cout << "There are some cycles." << std::endl;
        return 0;
    }

    //in case where there are no cycles, find a shortest path to each vertices from the first vertex in the topologically sorted vertex list.
    constexpr int sup = std::numeric_limits<int>::max();
    std::vector<int> distance(N,sup);
    distance[*topo.second.begin()] = 0;
    std::vector<int> predecessor(N);
    std::iota(predecessor.begin(),predecessor.end(),0);
    int tmp;
    for(auto &pred : topo.second){
        for(auto &edge : graph[pred]){
            auto &suc = edge.first;
            tmp = distance[pred] + edge.second;
            if(tmp < distance[suc]){
                distance[suc] = tmp;
                predecessor[suc] = pred;
            }
        }
    }
    for(int i=0; i<graph.size(); ++i){
        int p = i;
        std::cout << "distance: " << distance[p] << "\t";
        std::cout << "path: (goal) " << p;
        while(p != predecessor[p]){
            p = predecessor[p];
            std::cout << " <-- " << p;
        }
        std::cout << " (start)" << std::endl;
    }
    return 0;
}
