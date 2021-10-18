#include <iostream>
#include <algorithm>  
#include <cstdlib>
#include <fstream>
#include <cmath>
using namespace std;

void quickSortE(int* arr, int b, int e){ // Sort malejaco
    int i = b, j = e, m = arr[e];
    while(i <= j){
        while(arr[i] > m){i++;}
        while(arr[j] < m){j--;}
        if(i <= j){swap(arr[i++], arr[j--]);}
    }
    if(i < e){quickSortE(arr, i, e);}
    if(b < j){quickSortE(arr, b, j);}
}

int sum(int* arr, int n){
    int sum = 0;
    for(int i = 0; i < n; i++) sum += arr[i];
    return sum; 
}

int main(){
    srand(time(NULL));
    ifstream f("file1");
    int nProc, nTasks;
    f >> nProc >> nTasks;

    int *proc = new int[nProc];
    int *task = new int[nTasks];

    for (int i = 0; i < nTasks; i++){ f >> task[i]; }
    for (int i = 0; i < nProc; i++) proc[i] = 0;

    quickSortE(task, 0, nTasks-1);

    clock_t start, stop;
    start = clock();

    int Cmax = ceil(max(task[0], sum(task, nTasks-1) / nProc));
    cout << "Cmax : " << Cmax << endl;

    int i = 0, j = 0;
    while (j < nProc){
        while(1){
            if (proc[j] + task[i] < Cmax) proc[j] += task[i++];
            else break;
        } j++;
    } j = 0;
    while(i < nTasks){
        if (j == nProc) j = 0;
        proc[j] += task[i];
        j++; i++;
    }
    // for (int i = 0; i < nTasks; i++){ cout << task[i] << ' '; } cout << endl;
    // cout << endl << endl << endl << endl;

    stop = clock();

    cout << "Zapelnienie procesorow: ";
    for (i = 0; i < nProc; i++) cout << proc[i] << " ";
    // cout << endl << "Cmax : " << Cmax << endl;

    delete[] proc;
    delete[] task;
    f.close();
    return 0;
}