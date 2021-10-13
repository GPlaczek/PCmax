#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <algorithm>
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

void solve(int* prcs, int *tim, int prcs_n, int task_n){
    int i = 0, j = 0;
    while(i < task_n){
        j = 0;
        while (j < prcs_n && i < task_n){
            prcs[j++] += tim[i++];
        } j--;
        while (j >= 0 && i < task_n){
            prcs[j--] += tim[i++];
        }
    }
}

int main(){
    srand(time(NULL));
    ifstream f("file1");
    if (!f) { cerr << "File not opened" << endl; return -1;};

    int proc_n, tasks_n;  // liczba procesorow, zadan
    f >> proc_n >> tasks_n;
    int *times = new int[tasks_n];
    int *procs = new int[proc_n];
    for (int i = 0; i < tasks_n; i++){ f >> times[i]; }
    for (int i = 0; i < proc_n; i++) procs[i] = 0;

    quickSortE(times, 0, tasks_n-1);
    clock_t start, stop;
    start = clock();
    solve(procs, times, proc_n, tasks_n);
    stop = clock();
	
    cout << "Zadania: ";
    for (int i = 0; i < proc_n; i++) cout << procs[i] << " ";


    double a_time = (double) (stop - start) / CLOCKS_PER_SEC;
    cout << "\nCzas wykonywania: " << setprecision(1) << a_time << endl;

    int min_el = *min_element(procs, procs + proc_n), max_el = *max_element(procs, procs + proc_n);
    cout << "Roznica czasu miedzy najdluzszym i najkrotszym zad: " << max_el - min_el << endl;
    
    int empty = 0;
    for (int i = 0; i < proc_n; i++) empty += (procs[i] - min_el);
    cout << "Niezagospodarowane jednostki czasu: " << empty << endl;

    delete[] procs;
    delete[] times;
    f.close();
    return 0;
}
