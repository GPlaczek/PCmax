#include "../lib/MinHeap.hpp"
#include "../lib/PCmax.hpp"
#include<vector>
using namespace std;

vector<int> PCmax::greedy(int nProc, int nTasks, int *tasks){
    MinHeap<int> proc(nProc);
    for(int i = 0; i < nTasks; i++){
        proc[0] += tasks[i];
        proc.fixHeap();
    }
    // return proc.maxValue();
    vector<int> ordering;
    for(int i = 0; i < nProc; i++) ordering.push_back(proc[i]);

    return ordering;
}
