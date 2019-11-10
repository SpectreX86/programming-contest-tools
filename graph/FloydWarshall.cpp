#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <utility>
#include <string>

//find the shortest path and its distance with Floyd-Warshall algorithm.

template<class T>
using Edge = std::map<std::string, T>; //for this algorithm, an edge must have "vertex" and "length" keys.
template<class T>
using Graph = std::vector<std::vector<Edge<T> > >;

//V is the number of the vertices of the graph. The id of a vertex in the graph must be in [0,V).
template<class T>
std::pair<std::vector< std::vector<T> >, std::vector< std::vector<T> > > FloydWarshall(Graph<T> &graph){
    const T V = graph.size();
    const T sup = std::numeric_limits<T>::max();
    const T zero = static_cast<T>(0);
    std::vector< std::vector<T> > cost(V, std::vector<T>(V,sup));
    std::vector< std::vector<T> > predecessor(V, std::vector<T>(V,sup));
    for(int i=0; i<V; ++i){
        cost[i][i] = 0;
        predecessor[i][i] = i;
    }
    T pred, suc;
    for(pred=zero; pred<V; ++pred){
        for(auto &edge : graph[pred]){
            suc = edge["vertex"];
            cost[pred][suc] = edge["length"];
            predecessor[pred][suc] = pred;
        }
    }

    T costTmp;
    T s,t;
    for(T i=zero; i<V; ++i){
        for(s=zero; s<V; ++s){
            if(cost[s][i] == sup){
                continue;
            }
            for(t=zero; t<V; ++t){
                if(cost[i][t] == sup){
                    continue;
                }
                costTmp = cost[s][i] + cost[i][t];
                if(cost[s][t] > costTmp){
                    cost[s][t] = costTmp;
                    predecessor[s][t] = predecessor[i][t];
                }
            }
        }
    }

    return std::make_pair(cost, predecessor);
}

int main(int argc, char *argv[]){
    constexpr int N = 5;
    constexpr int M = 7;
    int u[M] = {0,1,2,3,0,2,4}, v[M] = {1,2,3,0,4,4,3};
    int w[M] = {2,3,5,8,4,1,7};
    Graph<int> graph(N);
    for(int i=0; i<M; ++i){
        graph[u[i]].emplace_back(Edge<int>{{"vertex",v[i]},{"length",w[i]}});
    }

    auto test = FloydWarshall(graph);

    int i;
    for(int s=0; s<N; ++s){
        for(int t=0; t<N; ++t){
            std::cout << "distance: " << test.first[s][t] << "\t";
            std::cout << "path: (goal) " << t;
            i = t;  
            while(i != test.second[s][i]){
                i = test.second[s][i];
                std::cout << " <-- " << i;
            }
            std::cout << " (start)" << std::endl;
        }
    }

    return 0;
}
