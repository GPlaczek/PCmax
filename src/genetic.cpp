#include "../lib/PCmax.hpp"
#include <iostream>
#include <random>

#define POPULATION_SIZE 150
#define GENERATIONS 20

using namespace std;

int PCmax::genetic(int nProcs, int nTasks, int *tasks){
    vector<int> *strongest = populate(nProcs, nTasks, tasks, POPULATION_SIZE);
    vector<int> *child;
    const int SHUFFLES = 2*nProcs;
    for(int i = 0; i < GENERATIONS; i++){
        child = repopulate(strongest, nProcs, POPULATION_SIZE, SHUFFLES);
        if(evaluate(child, nProcs) < evaluate(strongest, nProcs)){
            delete [] strongest;
            strongest = new vector<int>[nProcs];
            for(int j = 0; j < nProcs; j++){
                strongest[j] = move(child[j]);
            }
            delete [] child;
        }
    }
    int max = strongest[0][0];
    for(int i = 0; i < nProcs; i++){
        if(strongest[i][0] > max) max = strongest[i][0];
    }
    return max;
}

int PCmax::evaluate(vector<int> *shuffle, int nProc){
    // Funkcja oceniająca wartość uszeregowania procesów (maksymalny czas na procesorze - minimalny czas na procesorze)
    int max = shuffle[0][0];
    int min = shuffle[0][0];
    for(int i = 1; i < nProc; i++){
        if(shuffle[i][0] > max) max = shuffle[i][0];
        else if(shuffle[i][0] < min) min = shuffle[i][0];
    }
    return max - min;
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
            for(int a = 0; a < nProc; a++) bestOrdering[a] = move(ordering[a]);
        }
        delete [] ordering; // czyszczenie tablicy po każdej iteracji
    }
    return bestOrdering;
}

vector<int> *PCmax::repopulate(vector<int> *parent, int nProc, int populationSize, int shuffles){
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<int> distr(0, nProc - 1); // define the range
    int firstProc, secondProc, longerProc, shorterProc;
    vector<int> *bestChild = NULL;
    vector<int> *child;
    for(int i = 0; i < populationSize; i++){
        child = new vector<int>[nProc];
        for(int j = 0; j < nProc; j++){ child[j] = parent[j]; } // kopiowanie uszeregowania
        for(int j = 0; j < shuffles; j++){
            firstProc = distr(gen);
            secondProc = distr(gen);
            if(firstProc == secondProc) continue;
            if(child[firstProc] > child[secondProc]){
                longerProc = firstProc;
                shorterProc = secondProc;
            }else if(child[firstProc] < child[secondProc]){
                longerProc = secondProc;
                shorterProc = firstProc;
            }else continue;

            uniform_int_distribution<int> distr_1(0, child[longerProc].size()-1);
            int task = distr_1(gen);
            swap(child[longerProc][task], child[longerProc].back());
            child[longerProc][0] -= child[longerProc].back();
            child[shorterProc][0] += child[longerProc].back();
            child[shorterProc].push_back(child[longerProc].back());
            child[longerProc].pop_back();
        }
        if(i == 0 || evaluate(child, nProc) < evaluate(bestChild, nProc)){
            delete [] bestChild;
            bestChild = new vector<int>[nProc];
            for(int j = 0; j < nProc; j++){
                bestChild[j] = move(child[j]);
            }
        }
        delete [] child;
    }
    return bestChild;
}
