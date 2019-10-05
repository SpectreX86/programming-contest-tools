#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <utility>
#include <string>
#include <numeric>

//find the shortest path and its distance with Dijkstra algorithm.

//if you would like this program to run faster, use pair or vector instead of map in Edge.
template<class T>
using Edge = std::map<std::string, T>; //for this algorithm, an edge must have "successor" and "cost" keys.
template<class T>
using Graph = std::vector<std::vector<Edge<T> > >;

//The id of a vertex in the graph must be in [0,V).
template<class T>
std::pair<std::vector<T>, std::vector<T> > Dijkstra(Graph<T> &graph, const T &start){
    const T V = graph.size();
    const T distanceSup = std::numeric_limits<T>::max();
    const T zero = static_cast<T>(0);

    std::vector<T> distance(V, distanceSup);
    std::vector<T> predecessor(V);
    std::vector<bool> isVisited(V, false);
    distance[start] = zero;
    std::iota(predecessor.begin(),predecessor.end(),zero);

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

        if(distance[pred] == distanceSup){
            break;
        }

        for(auto &edge: graph[pred]){
            suc = edge["successor"];
            if(isVisited[suc]){
                continue;
            }
            distTmp = distance[pred] + edge["cost"];
            if(distance[suc] > distTmp){
                distance[suc] = distTmp;
                predecessor[suc] = pred;
                queue.emplace(suc,distance[suc]);
            }
        }        
    }

    return std::pair<std::vector<T>, std::vector<T> >(distance,predecessor);
}

int main(int argc, char *argv[]){
    constexpr int N = 5;
    constexpr int M = 7;
    int u[M] = {0,1,2,4,3,2,0}, v[M] = {1,2,4,3,0,3,4};
    int w[M] = {2,3,1,7,8,5,4};
    Graph<int> graph(N);
    for(int i=0; i<M; ++i){
        graph[u[i]].emplace_back(Edge<int>{{"successor",v[i]},{"cost",w[i]}});
    }

    constexpr int S=0;
    auto test = Dijkstra(graph, S);
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
