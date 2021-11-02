#include "../lib/PCmax.hpp"
#include <iomanip>
#include <algorithm>

void quickSortE(int* arr, int b, int e){
    int i = b, j = e, m = arr[e];
    while(i <= j){
        while(arr[i] > m){i++;}
        while(arr[j] < m){j--;}
        if(i <= j){swap(arr[i++], arr[j--]);}
    }
    if(i < e){quickSortE(arr, i, e);}
    if(b < j){quickSortE(arr, b, j);}
}

int PCmax::lpt(int nProcs, int nTasks, int *tasks){
    int *procs = new int[nProcs]; 
    for (int i = 0; i < nProcs; i++) procs[i] = 0;
    quickSortE(tasks, 0, nTasks-1);

    int i = 0, j = 0;
    while(i < nTasks){
        j = 0;
        while (j < nProcs && i < nTasks){
            procs[j++] += tasks[i++];
        } j--;
        while (j >= 0 && i < nTasks){
            procs[j--] += tasks[i++];
        }
    }
    int max = *max_element(procs, procs + nProcs);
    delete [] procs;

    return max;
}