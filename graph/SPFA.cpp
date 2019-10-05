#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <utility>
#include <string>
#include <numeric>

//SFPA stands for Shortest Path Faster Algorithm, which is an improvement of the Bellman–Ford algorithm.

//if you would like this program to run faster, use pair or vector instead of map in Edge.
template<class T>
using Edge = std::map<std::string, T>; //for this algorithm, an edge must have "successor" and "cost" keys.
template<class T>
using Graph = std::vector<std::vector<Edge<T> > >;

//V is the number of the vertices of the graph. The id of a vertex in the graph must be in [0,V).
template<class T>
std::pair<std::vector<T>, std::vector<T> > BellmanFord(Graph<T> &graph, const T &start){
    const T V = graph.size();
    const T distanceSup = std::numeric_limits<T>::max();
    const T distanceInf = std::numeric_limits<T>::min();
    const T zero = static_cast<T>(0);

    std::vector<T> distance(V, distanceSup);
    std::vector<T> predecessor(V);
    distance[start] = zero;
    std::iota(predecessor.begin(),predecessor.end(),zero);

    std::queue<T> queue;
    std::vector<bool> isInQueue(V,false);
    std::vector<T> count(V,zero);
    queue.emplace(start);
    isInQueue[start] = true;
    ++count[start];
    T distanceTmp;
    T pred, suc;
    while(!queue.empty()){
        pred = queue.front();
        queue.pop();
        isInQueue[pred] = false;
        for(auto &edge : graph[pred]){
            suc = edge["successor"];
            distanceTmp = distance[pred] > distanceInf ? distance[pred] + edge["cost"] : distanceInf;
            if(distance[suc] > distanceTmp){
                distance[suc] = distanceTmp;
                predecessor[suc] = pred;
                if(!isInQueue[suc]){
                    queue.emplace(suc);
                    isInQueue[suc] = true;
                    if(++count[suc] >= V){
                        distance[suc] = distanceInf;
                    }
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
    Graph<int> graph(N);
    for(int i=0; i<M; ++i){
        graph[u[i]].emplace_back(Edge<int>{{"successor",v[i]},{"cost",w[i]}});
    }

    int S=0;
    auto test = BellmanFord(graph,S);

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
