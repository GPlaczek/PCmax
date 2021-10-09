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
    fstream f;
    f.open("file1", ios::in);
    if (!f) cerr << "No such file" << endl;

    // liczba procesorów, liczba zadań
    int proc_num, tasks_num;
    f >> proc_num >> tasks_num;
    int times[tasks_num], procs[proc_num];
    for (int i = 0; i < tasks_num; i++){ f >> times[i]; }
    for (int i = 0; i < proc_num; i++) procs[i] = 0;

    quickSortE(times, 0, tasks_num-1);
    clock_t start, stop;
    start = clock();
    solve(procs, times, proc_num, tasks_num);
    stop = clock();
	
    cout << "Zadania: ";
    for (int i = 0; i < proc_num; i++) cout << procs[i] << " ";

    double a_time = (double) (stop - start) / CLOCKS_PER_SEC;
    cout << "\nCzas wykonywania: " << setprecision(1) << a_time << endl;
    cout << "Roznica czasu miedzy najdluzszym i najkrotszym zad: " << *max_element(procs, procs + proc_num) - *min_element(procs, procs + proc_num) << endl;

    f.close();
    return 0;
}
