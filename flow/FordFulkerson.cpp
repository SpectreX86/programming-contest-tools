#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <utility>
#include <string>
#include <stack>
#include <functional>

//calculates the muximum flow of networks with Ford-Fulkerson algorithm.

using T = int;

using Edge = std::map<std::string, T>; //for this algorithm, an edge must have "pred", "suc", "capasity" and "flow" keys.
using FlowNetwork = std::vector<std::pair<std::vector<std::reference_wrapper<Edge> >, std::vector<std::reference_wrapper<Edge> > > >; //the index of the vector means the id of the predecessor. the elements of the pair of vectors of edges mean "forward" and "backward."
using PathElement = std::pair<std::reference_wrapper<Edge>, bool>; //a pair of the predecessor and the direction from predecessor to successor (true: forward, false: backward).
using Path = std::vector<PathElement>; //a path in a FlowNetwork

//find the augumenting path.
std::pair<bool,Path> FindAugumentingPath(FlowNetwork &network, const T &source, const T &sink){
    T zero = static_cast<T>(0);
    const T V = network.size();
    Edge dummyEdge{{"pred",source},{"suc", source},{"capasity",0},{"flow",0}};
    Path path(V,PathElement(dummyEdge,true));
    std::vector<bool> isVisited(V,false);
    isVisited[source] = true;

    T pred, suc;
    std::stack<T> stack;
    stack.push(source);
    while(!stack.empty()){
        pred = stack.top();
        stack.pop();
        
        //search for the foward edges
        for(auto &edgeRef : network[pred].first){
            auto &edge = edgeRef.get();
            suc = edge["suc"];
            if(!isVisited[suc] && edge["flow"] < edge["capasity"]){
                path[suc] = PathElement(edge, true);
                isVisited[suc] = true;

                if(suc == sink){
                    return std::pair<bool, Path>(true, path);
                }
                stack.push(suc);
            }
        }

        //search for the backward edges
        for(auto &edgeRef : network[pred].first){
            auto &edge = edgeRef.get();
            suc = edge["pred"];
            if(!isVisited[suc] && edge["flow"] > zero){
                path[suc] = PathElement(edge, false);
                isVisited[suc] = true;
                stack.push(suc);
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
                edge["flow"] += dFlow;
            }else{
                pred = edge["suc"];
                edge["flow"] -= dFlow;
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
    Edge edge[M];
    for(T i=0; i<M; ++i){
        edge[i] = Edge{{"pred",u[i]},{"suc",v[i]},{"capasity",c[i]},{"flow",0}};
        network[u[i]].first.emplace_back(edge[i]);
        network[v[i]].second.emplace_back(edge[i]);
    }

    FordFulkerson(network, source, sink);
    for(auto edges : network){
        for(auto edgeRef : edges.first){
            auto &edge = edgeRef.get();
            std::cout << edge["pred"] << " --> " << edge["suc"] << "\t:\t" << edge["flow"] << " / " << edge["capasity"] << std::endl;
        }
    }
    return 0;
}
