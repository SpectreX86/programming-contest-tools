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
using Graph = std::map<T, std::vector<Edge<T> > >;

//V is the number of the vertices of the graph. The id of a vertex in the graph must be in [0,V).
template<class T>
std::pair<std::vector< std::vector<T> >, std::vector< std::vector<T> > > FloydWarshall(Graph<T> &graph, const T &V){
    const T distanceSup = std::numeric_limits<T>::max();
    std::vector< std::vector<T> > distance(V, std::vector<T>(V,distanceSup));
    std::vector< std::vector<T> > predecessor(V, std::vector<T>(V,distanceSup));
    for(int i=0; i<V; ++i){
        distance[i][i] = 0;
        predecessor[i][i] = i;
    }
    T pred, suc;
    for(auto &edges : graph){
        pred = edges.first;
        for(auto &edge : edges.second){
            suc = edge["vertex"];
            distance[pred][suc] = edge["length"];
            predecessor[pred][suc] = pred;
        }
    }

    T distanceTmp;
    T s,t;
    for(T i=0; i<V; ++i){
        for(s=0; s<V; ++s){
            if(distance[s][i] == distanceSup){
                continue;
            }
            for(t=0; t<V; ++t){
                if(distance[i][t] == distanceSup){
                    continue;
                }
                distanceTmp = distance[s][i] + distance[i][t];
                if(distance[s][t] > distanceTmp){
                    distance[s][t] = distanceTmp;
                    predecessor[s][t] = predecessor[i][t];
                }
            }
        }
    }

    return std::pair<std::vector< std::vector<T> >, std::vector< std::vector<T> > >(distance,predecessor);
}

int main(int argc, char *argv[]){
    constexpr int N = 5;
    constexpr int M = 7;
    int u[M] = {0,1,2,3,0,2,4}, v[M] = {1,2,3,0,4,4,3};
    int w[M] = {2,3,5,8,4,1,7};
    Graph<int> graph;
    for(int i=0; i<M; ++i){
        graph[u[i]].emplace_back(Edge<int>{{"vertex",v[i]},{"length",w[i]}});
    }

    auto test = FloydWarshall(graph, N);

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
