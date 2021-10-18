#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include "../lib/MinHeap.hpp"
#define N_INSTANCES 10
using namespace std;

int main(){
    int nProc, nTasks;  // liczba procesorow, zadan
    ifstream f;
    int *tasks;
    char buffer[100];
    ofstream f_out("output_Heap");

    for (int i = 1; i <= N_INSTANCES; i++){
        sprintf(buffer, "instance_%d", i);
        f.open(buffer);
        if (!f) { cerr << "File not opened" << endl; return -1;};

        f >> nProc >> nTasks;
        tasks = new int[nTasks];
        for (int i = 0; i < nTasks; i++){ f >> tasks[i]; }
        f.close();

        MinHeap<int> proc(nProc); // kopiec samych zer
        for(int i = 0; i < nTasks; i++){
            proc[0] += tasks[i];
            proc.fixHeap();
        }
        proc.insertData(f_out);
    }
    f_out.close();
    
    return 0;
}