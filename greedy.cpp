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

void solve(int* p, int *t, int m, int n){
    int i = 0, j = 0;
    while(i < n){
        j = 0;
        while (j < m && i < n){
            p[j++] += t[i++];
        } j--;
        while (j >= 0 && i < n){
            p[j--] += t[i++];
        }
    }
}

int main(){
    srand(time(NULL));
    fstream f;
    f.open("file1", ios::in);
    if (!f) cerr << "No such file" << endl;

    // m procesorów, n zadań
    int m, n;
    f >> m >> n;
    int times[n], proc[m];
    for (int i = 0; i < n; i++){ f >> times[i]; }
    for (int i = 0; i < m; i++) proc[i] = 0;

    quickSortE(times, 0, n-1);
    clock_t start, stop;
    start = clock();
    solve(proc, times, m, n);
    stop = clock();
    
    // cout << "Zadania: ";
    // for (int i = 0; i < m; i++) cout << proc[i] << " ";

    double a_time = (double) (stop - start) / CLOCKS_PER_SEC;
    cout << "\nCzas wykonywania: " << setprecision(1) << a_time << endl;
    cout << "Roznica czasu miedzy najdluzszym i najkrotszym zad: " << *max_element(proc, proc + m) - *min_element(proc, proc + m) << endl;

    f.close();
    return 0;
}