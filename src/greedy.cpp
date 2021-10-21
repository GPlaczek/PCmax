#include "../lib/MinHeap.hpp"
#include "PCmax.hpp"

int PCmax::greedy(int nProc, int nTasks, int *tasks){
    MinHeap<int> proc(nProc);
    for(int i = 0; i < nTasks; i++){
        proc[0] += tasks[i];
        proc.fixHeap();
    }
    return proc.maxValue();
}
