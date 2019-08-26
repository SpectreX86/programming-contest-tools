#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <utility>
#include <string>

//find the shortest path and its distance with Dijkstra algorithm.

template<class T>
using Edge = std::map<std::string, T>; //for this algorithm, an edge must have "vertex" and "length" keys.
template<class T>
using Graph = std::map<T, std::vector<Edge<T> > >;

//The id of a vertex in the graph must be in [0,V).
template<class T>
std::pair<T, std::vector<T> > Dijkstra(Graph<T> &graph, const T &V, const T &start, const T &end){
    const T distanceSup = std::numeric_limits<T>::max();
    std::vector<T> distance(V, distanceSup);
    std::vector<T> predecessor(V, distanceSup);
    std::vector<bool> isVisited(V, false);
    distance[start] = 0;
    predecessor[start] = start;

    auto compare = [](const std::pair<T,T> &a, const std::pair<T,T> &b){
        return a.second > b.second;
    };
    std::priority_queue<std::pair<T,T>, std::vector<std::pair<T,T> >, decltype(compare)> queue(compare);
    queue.emplace(start,distance[start]);
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

        if(pred == end || distance[pred] == distanceSup){
            break;
        }

        for(auto &edge: graph[pred]){
            suc = edge["vertex"];
            if(isVisited[suc]){
                continue;
            }
            distTmp = distance[pred] + edge["length"];
            if(distance[suc] > distTmp){
                distance[suc] = distTmp;
                predecessor[suc] = pred;
                queue.emplace(suc,distance[suc]);
            }
        }        
    }

    return std::pair<T, std::vector<T> >(distance[end],predecessor);
}

int main(int argc, char *argv[]){
    constexpr int N = 5;
    constexpr int M = 7;
    int u[M] = {0,1,2,4,3,2,0}, v[M] = {1,2,4,3,0,3,4};
    int w[M] = {2,3,1,7,8,5,4};
    Graph<int> graph;
    for(int i=0; i<M; ++i){
        graph[u[i]].emplace_back(Edge<int>{{"vertex",v[i]},{"length",w[i]}});
    }

    constexpr int S=0, T=3;
    auto test = Dijkstra(graph, N, S, T);
    std::cout << "distance: " << test.first << std::endl;
    int p = T;
    std::cout << "path: (goal) " << p;
    while(p != test.second[p]){
        p = test.second[p];
        std::cout << " <-- " << p;
    }
    std::cout << " (start)" << std::endl;
    return 0;
}
