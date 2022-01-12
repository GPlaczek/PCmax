#include "../lib/PCmax.hpp"
#include <iostream>
#include <random>

using namespace std;

int PCmax::genetic(int nProcs, int nTasks, int *tasks){
    const int POPULATION_SIZE = 1000;
    const int GENERATIONS = nProcs*100;
    const int SHUFFLES = nProcs/8;
    vector<int> *strongest = populate(nProcs, nTasks, tasks, POPULATION_SIZE);
    vector<int> *child;
    for(int i = 0; i < GENERATIONS; i++){
        child = repopulate(strongest, nProcs, POPULATION_SIZE, SHUFFLES);
        if(evaluate(child, nProcs) < evaluate(strongest, nProcs)){
            // delete [] strongest; // nie mam pewności czy te dwie linijki nie są konieczne
            // strongest = new vector<int>[nProcs];
            for(int j = 0; j < nProcs; j++){
                strongest[j].clear();
                strongest[j] = move(child[j]);
            }
            delete [] child;
        }
    }
   int max = strongest[0][0];
    for(int i = 0; i < nProcs; i++){
        if(strongest[i][0] > max) max = strongest[i][0];
    }
    delete [] strongest;
    return max;
}

int PCmax::evaluate(vector<int> *shuffle, int nProc){
    // Funkcja oceniająca wartość uszeregowania procesów (maksymalny czas na procesorze - minimalny czas na procesorze)
    int max = shuffle[0][0];
    for(int i = 1; i < nProc; i++){
        if(shuffle[i][0] > max) max = shuffle[i][0];
    }
    return max;
}

vector<int> *PCmax::populate(int nProc, int nTasks, int *tasks, int populationSize){
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<int> distr(0, nProc - 1); // define the range

    // Tablica na aktualne uszeregowanie i na najlepsze dotychczasowe uszeregowanie

    vector<int> *bestOrdering = new vector<int>[nProc];
    vector<int> *ordering;
    int value, minValue; // zmienne przechowujące najlepszą dotychczasową wartość i aktualną wartość

    // Wartość pierwszego uszeregowania jest na początku najlepsza
    for (int i = 0; i < nProc; i++) {
        bestOrdering[i].push_back(0);
    }
    for(int i = 0; i < nTasks; i++){
        int rand_num = distr(gen);
        bestOrdering[rand_num].push_back(tasks[i]);
        bestOrdering[rand_num][0] += tasks[i];
    }
    minValue = evaluate(bestOrdering, nProc);

    for(int i = 1; i < populationSize; i++){
        // Generowanie kolejno nowych uszeregowań
        ordering = new vector<int>[nProc];
        for (int j = 0; j < nProc; j++) {
            ordering[j].push_back(0);
        }
        for(int j = 0; j < nTasks; j++){
            int rand_num = distr(gen);
            ordering[rand_num].push_back(tasks[j]);
            ordering[rand_num][0] += tasks[j];
        }
        value = evaluate(ordering, nProc);
        if(value < minValue){
            // Jeśli nowe uszeregowanie jest najlepsze to podmieniamy
            minValue = value;
            for(int a = 0; a < nProc; a++){
                bestOrdering[a].clear();
                bestOrdering[a] = move(ordering[a]);
            }
        }
        delete [] ordering; // czyszczenie tablicy po każdej iteracji
    }
    return bestOrdering;
}

vector<int> *PCmax::repopulate(vector<int> *parent, int nProc, int populationSize, int shuffles){
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<int> distr(0, nProc - 1); // define the range

    vector<int> *bestChild = parent;
    vector<int> *child;
    int value, bestValue = evaluate(parent, nProc);

    child = new vector<int>[nProc];
    for(int i = 0; i < populationSize; i++){
        for(int j = 0; j < nProc; j++){ child[j] = parent[j]; } // kopiowanie uszeregowania
        for(int j = 0; j < shuffles; j++){
            int min = 0;
            int max = 0;
            for(int k = 1; k < nProc; k++){
                if(child[k][0] > child[max][0]) max = k;
                else if(child[k][0] < child[min][0]) min = k;
            }
            uniform_int_distribution<int> distr(1, child[max].size() - 1);
            int elem = distr(gen);
            swap(child[max].back(), child[max][elem]);
            child[min].push_back(child[max].back());
            child[min][0]+=child[max].back();
            child[max][0]-=child[max].back();
            child[max].pop_back();
        }
        value = evaluate(child, nProc);
        if(value < bestValue){
            bestValue = value;
            // delete [] bestChild; // tu tak samo nie wiem czy brak tych dwóch linijek nie spowoduje memory leaka
            // bestChild = new vector<int>[nProc];
            for(int j = 0; j < nProc; j++){
                bestChild[j].clear();
                bestChild[j] = move(child[j]);
            }
        }else{
            for(int j = 0; j < nProc; j++){
                child[j].clear();
            }
        }
    }
    return bestChild;
}
