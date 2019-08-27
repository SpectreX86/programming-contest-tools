#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <utility>
#include <string>
#include <queue>
#include <functional>

//calculates the muximum flow with minimum cost of networks with Edmons-Karp-like algorithm.

using T = int;

using Edge = std::map<std::string, T>; //for this algorithm, an edge must have "pred", "suc", "capasity", "cost" and "flow" keys.
using FlowNetwork = std::vector<std::pair<std::vector<std::reference_wrapper<Edge> >, std::vector<std::reference_wrapper<Edge> > > >; //the index of the vector means the id of the predecessor. the elements of the pair of vectors of edges mean "forward" and "backward."
using PathElement = std::pair<std::reference_wrapper<Edge>, bool>; //a pair of the predecessor and the direction from predecessor to successor (true: forward, false: backward).
using Path = std::vector<PathElement>; //a path in a FlowNetwork

//find the augumenting path.
std::pair<bool,Path> FindAugumentingPath(FlowNetwork &network, const T &source, const T &sink){
    const T V = network.size();
    const T infinity = std::numeric_limits<T>::max();
    const T zero = static_cast<T>(0);

    Edge dummyEdge{{"pred",infinity},{"suc", infinity},{"capasity",zero},{"cost",zero},{"flow",zero}};
    Path path(V,PathElement(dummyEdge,true));

    std::vector<T> cost(V, infinity);
    cost[source] = zero;

    std::vector<bool> isVisited(V,false);

    auto compare = [](const std::pair<T,T> &a, const std::pair<T,T> &b){
        return a.second > b.second;
    };
    std::priority_queue<std::pair<T,T>, std::vector<std::pair<T,T> >, decltype(compare)> queue(compare);
    queue.emplace(source,cost[source]);

    T pred, suc;
    T costTmp;
    while(!queue.empty()){
        pred = queue.top().first;
        if(queue.top().second > cost[pred]){ //version management
            queue.pop();
            continue;
        }
        queue.pop();

        if(pred == sink || cost[pred] == infinity){
            break;
        }
        
        //search for the foward edges
        for(auto &edgeRef : network[pred].first){
            auto &edge = edgeRef.get();
            suc = edge["suc"];
            if(edge["flow"] < edge["capasity"]){
                costTmp = cost[pred] + edge["cost"];
                if(cost[suc] > costTmp && costTmp >= zero){
                    cost[suc] = costTmp;
                    path[suc] = PathElement(edge, true);
                    queue.emplace(suc,cost[suc]);
                }
            }
        }

        //search for the backward edges
        for(auto &edgeRef : network[pred].second){
            auto &edge = edgeRef.get();
            suc = edge["pred"];
            if(edge["flow"] > zero){
                costTmp = cost[pred] - edge["cost"];
                if(cost[suc] > costTmp && costTmp >= zero){
                    cost[suc] = costTmp;
                    path[suc] = PathElement(edge, false);
                    queue.emplace(suc,cost[suc]);
                }
            }
        }
    }    
    return std::pair<bool, Path>(cost[sink] < infinity, path);
}

void MaxFlowMinCost(FlowNetwork &network, const T &source, const T &sink){
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
            auto &edge = path[suc].first.get();
            if(path[suc].second){
                pred = edge["pred"];
                tmpFlow = edge["capasity"] - edge["flow"];
            }else{
                pred = edge["suc"];
                tmpFlow = edge["flow"];
            }
            if(dFlow > tmpFlow){
                dFlow = tmpFlow;
            }
            suc = pred;
        }

        //update the flow
        suc = sink;
        while(suc != source){
            auto &edge = path[suc].first.get();
            if(path[suc].second){
                pred = edge["pred"];
                edge["flow"] += dFlow; //相方のエッジ(suc-->pred)も更新するべき。
            }else{
                pred = edge["suc"];
                edge["flow"] -= dFlow; ////相方のエッジ(suc-->pred)も更新するべき。
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
    T capacity[M] = {300,200,300,300,350,300,200,280};
    T cost[M] = {0,7,0,0,6,0,6,4};
    FlowNetwork network(N);
    Edge edge[M];
    for(T i=0; i<M; ++i){
        edge[i] = Edge{{"pred",u[i]},{"suc",v[i]},{"capasity",capacity[i]},{"cost",cost[i]},{"flow",0}};
        network[u[i]].first.emplace_back(edge[i]);
        network[v[i]].second.emplace_back(edge[i]);
    }

    T costSum = 0;
    MaxFlowMinCost(network, source, sink);
    for(auto &edges : network){
        for(auto &edgeRef : edges.first){
            auto edge = edgeRef.get();
            std::cout << edge["pred"] << " --> " << edge["suc"] << "\t:\t" << edge["flow"] << " / " << edge["capasity"] << "\t:\t" << edge["flow"]*edge["cost"] <<std::endl;
            costSum += edge["cost"]*edge["flow"];
        }
    }
    std::cout << "cost: " << costSum << std::endl;
    return 0;
}
