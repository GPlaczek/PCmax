#include "../lib/PCmax.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

// rozwiazanie oparte na tablicy o dlugoci nTasks, w ktorej kazdy element jest numerem procesora,
// a kazdy indeks reprezentuje numer zadania do ktorego dany procesor zostanie przypisany
// tablica ta jest wygenerowana na podstawie permutacji z powtórzeniami pomocniczej tablicy z odpowiednimi numerami procesorow

int cmax = 1000000;

int Cmax(vector<int> &permuts, int *tasks, int nProc){
    vector<int> procs(nProc, 0);
    for (int i = 0; i < permuts.size(); i++){ 
        procs[permuts[i]-1] += tasks[i];
    }
    return *max_element(procs.begin(), procs.end());
}

void permute(vector<int> &procsID, vector<int> &permuts, int *tasks, int index){
    int currCmax;
    for(int i = 0; i < procsID.size(); i++){
        permuts[index] = procsID[i];
        if(index == permuts.size()-1){
            currCmax = Cmax(permuts, tasks, procsID.size());
            if (currCmax < cmax) cmax = currCmax;
        }
        else permute(procsID, permuts, tasks, index+1);
    }
}

int PCmax::brute(int nProcs, int nTasks, int *tasks){
    // procID - tablica z numerami procesorow
    // permuts - tablica ktorej wartosci beda permutowane, reprezentujaca przynaleznosc zadan do procesorow
    vector<int> procID(nProcs), permuts(nTasks);
    for (int i = 0; i < nProcs; i++) procID[i] = i+1;
    permute(procID, permuts, tasks, 0);
    cout << cmax << endl;
}