#include <iostream>
#include <vector>
#include <map>

//priority queue in which the priority among the elements can be updated.
//this implementation may be slow, so I'd like to modify in the future.
template<class K, class P>
class PriorityQueue{
public:
    K top(){
        return heap[0].first;
    }
    void push(K key, P priority){
        heap.emplace_back(std::pair<K,P>(key, priority));
        pos[key] = heap.size()-1;
        decrease(key, priority);
    }
    void pop(){
        pos.erase(heap[0].first);
        heap[0] = heap[heap.size()-1];
        pos[heap[0].first] = 0;
        heap.pop_back();
        increase(heap[0].first, heap[0].second);
    }
    void update(K key, P priority){
        unsigned int idx = pos[key];
        if(isPrior(priority, heap[idx].second)){
            decrease(key, priority);
        }else if(isPrior(heap[idx].second, priority)){
            increase(key, priority);
        }
    }
    bool empty(){
        return heap.empty();
    }

    void print(){
        for(auto &h : heap){
            std::cout << h.first << " ";
        }
        std::cout << std::endl;
    }

private:
    std::vector< std::pair<K, P> >heap;
    std::map<K,unsigned int> pos;

    bool isPrior(const P &a, const P &b){
        return a < b;
    }

    void increase(K key, P priority){
        unsigned int idx = pos[key];
        heap[idx].second = priority;

        unsigned int idxSup = heap.size();
        unsigned int idxLeft, idxRight, idxPrior; 
        while(idx < idxSup){
            idxLeft = 2*idx+1;
            if((idxLeft < idxSup) && isPrior(heap[idxLeft].second, heap[idx].second)){
                idxPrior = idxLeft;
            }else{
                idxPrior = idx;
            }

            idxRight = 2*idx+2;
            if((idxRight < idxSup) && isPrior(heap[idxRight].second, heap[idxPrior].second)){
                idxPrior = idxRight;                
            }

            if(idxPrior == idx){ 
                break; 
            }

            heap[idx] = heap[idxPrior];
            pos[heap[idx].first] = idx;

            heap[idxPrior].first = key;
            heap[idxPrior].second = priority;

            idx = idxPrior;
        }
        pos[key] = idx;
    }

    void decrease(K key, P priority){
        unsigned int idx = pos[key];
        unsigned int idxParent;
        while(idx > 0){
            idxParent = (idx-1)/2;
            if(isPrior(heap[idxParent].second, priority)){
                break;
            }
            heap[idx] = heap[idxParent];
            pos[heap[idx].first] = idx;
            idx = idxParent;
        }
        
        heap[idx].first = key;
        heap[idx].second = priority;
        pos[key] = idx;
    }
};

int main(int argc, char *argv[]){
    PriorityQueue<int, int> heap;
    heap.print();
    assert (heap.empty());

    heap.push(0, 32);
    heap.print();
    assert (!heap.empty());

    heap.push(1, 5);
    heap.push(2, 3);
    heap.push(3, 7);
    heap.push(4, 9);
    heap.push(5, 1);
    heap.push(6, 2);

    heap.print();

    assert (heap.top() == 5);
    heap.pop();
    heap.print();

    assert (heap.top() == 6);
    heap.pop();
    heap.print();

    assert (heap.top() == 2);
    heap.pop();
    heap.print();

    assert (heap.top() == 1);
    heap.pop();

    heap.print();
    heap.update(3,100);
    heap.print();

    assert (heap.top() == 4);
    heap.pop();
    heap.print();

    assert (heap.top() == 0);
    heap.pop();
    heap.print();

    assert (heap.top() == 3);
    heap.pop();
    heap.print();

    std::cout << "Success!" << std::endl;

    return 0;
}
