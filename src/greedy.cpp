#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <algorithm>
#include "../lib/MinHeap.hpp"
using namespace std;

int main(){
    string filename;
    cin >> filename;
    ifstream f(filename);
    if (!f) { cerr << "File not opened" << endl; return -1;};

    int nProc, nTasks;  // liczba procesorow, zadan
    f >> nProc >> nTasks;
    int *tasks= new int[nTasks];
    for (int i = 0; i < nTasks; i++){ f >> tasks[i]; }
    f.close();
    MinHeap<int> proc(nProc); // kopiec samych zer
    for(int i = 0; i < nTasks; i++){
        // Dodawanie czasu przetwarzania kolejnych procesów do szczytu kopca(pierwszy wolny procesor)
        // Naprawianie kopca po dodaniu każdego procesu
        // Wynikiem jest czas przetwarzania na wszystkich procesorach (kolejność procesorów nie jest zachowana)
        // JEŻELI W ROZWIĄZANIU ISTOTNA JEST KOLEJNOŚĆ PROCESORÓW TO TO ROZWIĄZANIE JEST BŁĘDNE
        proc[0] += tasks[i];
        proc.fixHeap();
    }
    /*for(int i = 0; i < nProc; i++){
        cout << proc[i] << endl;
    }*/
    proc.max_heap_element();
    return 0;
}
