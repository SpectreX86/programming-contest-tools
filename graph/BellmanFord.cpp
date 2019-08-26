#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <utility>
#include <string>

//find the shortest path and its distance with Bellman-Ford algorithm.

template<class T>
using Edge = std::map<std::string, T>; //for this algorithm, an edge must have "vertex" and "length" keys.
template<class T>
using Graph = std::map<T, std::vector<Edge<T> > >;

//V is the number of the vertices of the graph. The id of a vertex in the graph must be in [0,V).
template<class T>
std::pair<std::vector<T>, std::vector<T> > BellmanFord(Graph<T> &graph, const T &V, const T &start){
    const T distanceSup = std::numeric_limits<T>::max();
    const T distanceInf = std::numeric_limits<T>::min();
    std::vector<T> distance(V, distanceSup);
    std::vector<T> predecessor(V, distanceSup);
    distance[start] = 0;
    predecessor[start] = start;

    T distanceTmp;
    T pred, suc;
    for(T i=0; i<V; ++i){
        for(auto &edges : graph){
            pred = edges.first;
            if(distance[pred] == distanceSup){
                continue;
            }
            for(auto &edge : edges.second){
                suc = edge["vertex"];
                distanceTmp = distance[pred] + edge["length"];
                if(distance[suc] > distanceTmp){
                    if(i==V){
                        for(auto &d : distance){
                            d = distanceInf;
                        }
                        distance[start] = 0;
                        return std::pair<std::vector<T>, std::vector<T> >(distance,predecessor);
                    }
                    distance[suc] = distanceTmp;
                    predecessor[suc] = pred;
                }
            }
        }
    }

    return std::pair<std::vector<T>, std::vector<T> >(distance,predecessor);
}

int main(int argc, char *argv[]){
    constexpr int N = 5;
    constexpr int M = 6;
    int u[M] = {0,4,3,2,4,1}, v[M] = {4,3,2,1,1,3};
    int w[M] = {2,4,6,-3,5,-2};
    Graph<int> graph;
    for(int i=0; i<M; ++i){
        graph[u[i]].emplace_back(Edge<int>{{"vertex",v[i]},{"length",w[i]}});
    }

    int S=0;
    auto test = BellmanFord(graph, N, S);

    for(int i=0; i<N; ++i){
        int p = i;
        std::cout << "distance: " << test.first[p] << "\t";
        std::cout << "path: (goal) " << p;
        while(p != test.second[p]){
            p = test.second[p];
            std::cout << " <-- " << p;
        }
        std::cout << " (start)" << std::endl;
    }


    return 0;
}
