#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <utility>
#include <functional>
#include <string>

template<class T>
using Edge = std::map<std::string, T>;
template<class T>
using Graph = std::map<T, std::vector<Edge<T> > >;

template<class T>
std::pair<T, std::vector<T> > Dijkstra(Graph<T> &graph, const T &start, const T &end){
    T V = graph.size();
    std::vector<T> distance(V, std::numeric_limits<int>::max());
    std::vector<T> predecessor(V, std::numeric_limits<int>::max());
    std::vector<bool> isVisited(V,false);
    distance[start] = 0;

    auto compare = [](const std::pair<T,T> &a, const std::pair<T,T> &b){
                        return a.second > b.second;
                    };
    std::priority_queue<std::pair<T,T>, std::vector<std::pair<T,T> >, decltype(compare)> queue(compare);
    queue.emplace(start,distance[start]);
    predecessor[start] = start;
    T pred, suc;
    std::pair<T,T> tmp;
    T distTmp;
    while(!queue.empty()){
        tmp = queue.top();
        pred = tmp.first;
        isVisited[pred] = true;
        queue.pop();

        if(pred == end){
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
    constexpr int M = 7;
    int u[M] = {0,1,2,4,3,2,0}, v[M] = {1,2,4,3,0,3,4};
    int w[M] = {2,3,1,7,8,5,4};
    Graph<int> graph;
    Edge<int> edge;
    for(int i=0; i<M; ++i){
        edge["vertex"] = v[i];
        edge["length"] = w[i];
        graph[u[i]].emplace_back(edge);
    }

    int S=0, T=3;
    auto test = Dijkstra(graph, S, T);
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
