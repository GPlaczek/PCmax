#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <algorithm>
#define N_INSTANCES 10
using namespace std;

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

void solve(int* prcs, int *tsk, int prcs_n, int task_n){
    int i = 0, j = 0;
    while(i < task_n){
        j = 0;
        while (j < prcs_n && i < task_n){
            prcs[j++] += tsk[i++];
        } j--;
        while (j >= 0 && i < task_n){
            prcs[j--] += tsk[i++];
        }
    }
}

int main(){
    srand(time(NULL));
    int proc_n, tasks_n;  // liczba procesorow, zadan
    ifstream f;
    int *tasks, *procs;
    int max_el;
    char buffer[50];
    ofstream f_out("output_upDown");

    for (int i = 1; i <= N_INSTANCES; i++){
        sprintf(buffer, "instance_%d", i);
        f.open(buffer);
        if (!f) { cerr << "File not opened" << endl; return -1;};

        f >> proc_n >> tasks_n;
        tasks = new int[tasks_n];
        procs = new int[proc_n];
        for (int i = 0; i < tasks_n; i++){ f >> tasks[i]; }
        for (int i = 0; i < proc_n; i++) procs[i] = 0;

        quickSortE(tasks, 0, tasks_n-1);
        solve(procs, tasks, proc_n, tasks_n);

        max_el = *max_element(procs, procs + proc_n);
        f_out << max_el << endl;

        delete[] procs;
        delete[] tasks;
        f.close();
    }
    f_out.close();
    
    return 0;
}
