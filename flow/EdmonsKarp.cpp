#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <utility>
#include <string>
#include <queue>
#include <functional>

//calculates the muximum flow of networks with Edmons-Karp algorithm.

using T = int;

using Edge = std::map<std::string, T>; //for this algorithm, an edge must have "pred", "suc", "capasity" and "flow" keys.
using FlowNetwork = std::vector<std::pair<std::vector<Edge>, std::vector<Edge> > >; //the index of the vector means the id of the predecessor. the elements of the pair of vectors of edges mean "forward" and "backward."
using PathElement = std::pair<std::reference_wrapper<Edge>, bool>; //a pair of the predecessor and the direction from predecessor to successor (true: forward, false: backward).
using Path = std::vector<PathElement>; //a path in a FlowNetwork

//find the augumenting path.
std::pair<bool,Path> FindAugumentingPath(FlowNetwork &network, const T &source, const T &sink){
    const T V = network.size();
    Edge dummyEdge{{"pred",source},{"suc", source},{"capasity",0},{"flow",0}};
    Path path(V,PathElement(dummyEdge,true));
    std::vector<bool> isVisited(V,false);
    isVisited[source] = true;

    T pred, suc;
    std::queue<T> queue;
    queue.push(source);
    while(!queue.empty()){
        pred = queue.front();
        queue.pop();
        
        //search for the foward edges
        for(auto &edge : network[pred].first){
            suc = edge["suc"];
            if(!isVisited[suc] && edge["flow"] < edge["capasity"]){
                path[suc] = PathElement(edge, true);
                isVisited[suc] = true;

                if(suc == sink){
                    return std::pair<bool, Path>(true, path);
                }
                queue.push(suc);
            }
        }

        //search for the backward edges
        for(auto &edge : network[pred].second){
            suc = edge["pred"];
            if(!isVisited[suc] && edge["flow"] > static_cast<T>(0)){
                path[suc] = PathElement(edge, false);
                isVisited[suc] = true;
                queue.push(suc);
            }
        }
    }    
    return std::pair<bool, Path>(false, path);
}

void FordFulkerson(FlowNetwork &network, const T &source, const T &sink){
    const T dFlowSup = std::numeric_limits<T>::max();

    std::pair<bool, Path> result;
    Path path;
    T pred, suc;
    T dFlow, tmpFlow; //degree of flow augumentation
    while((result = FindAugumentingPath(network,source,sink)).first){
        path = result.second;

        //estimate the maximum dFlow
        suc = sink;
        dFlow = dFlowSup;
        while(suc != source){
            if(path[suc].second){
                pred = path[suc].first.get()["pred"];
                tmpFlow = path[suc].first.get()["capasity"] - path[suc].first.get()["flow"];
            }else{
                pred = path[suc].first.get()["suc"];
                tmpFlow = path[suc].first.get()["flow"];
            }
            if(dFlow > tmpFlow){
                dFlow = tmpFlow;
            }
            suc = pred;
        }

        //update the flow
        suc = sink;
        while(suc != source){
            if(path[suc].second){
                pred = path[suc].first.get()["pred"];
                path[suc].first.get()["flow"] += dFlow;
            }else{
                pred = path[suc].first.get()["suc"];
                path[suc].first.get()["flow"] -= dFlow;
            }
            suc = pred;
        }
    }
}

int main(int argc, char *argv[]){
    constexpr T N = 6;
    constexpr T M = 8;
    constexpr T source=0, sink=5;

    T u[M] = {0,1,3,0,2,4,1,2}, v[M] = {1,3,5,2,4,5,4,3};
    T c[M] = {3,2,3,2,3,2,2,2};
    FlowNetwork network(N);
    for(T i=0; i<M; ++i){
        network[u[i]].first.emplace_back(Edge{{"pred",u[i]},{"suc",v[i]},{"capasity",c[i]},{"flow",0}});
        network[v[i]].second.emplace_back(Edge{{"pred",u[i]},{"suc",v[i]},{"capasity",c[i]},{"flow",0}});
    }

    FordFulkerson(network, source, sink);
    for(auto edges : network){
        for(auto edge : edges.first){
            std::cout << edge["pred"] << " --> " << edge["suc"] << "\t:\t" << edge["flow"] << " / " << edge["capasity"] << std::endl;
        }
    }
    return 0;
}
