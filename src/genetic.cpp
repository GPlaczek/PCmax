#include "../lib/PCmax.hpp"
#include <iostream>
#include <random>

using namespace std;




int PCmax::genetic(int nProcs, int nTasks, int *tasks){
    // Tu kiedyś zadzieje się magia
    int max = 0, max_index = -1;
    vector <int> *processors = new vector <int>[nProcs];

    //zeruję zerowy indeks każdego z procesorów - to będzie suma długości zadań na każdym procesorze
    //wykonuję zamianę 5 razy, bo tak mi się zachciało
    /*for (int j = 0; j < 5; j++) {
        //ilość procesów tablicy processors o indeksie max - przedział od 1 (bo bez sumy)
        uniform_int_distribution<int> rand_process(1, processors[max_index].size() - 1);
        //randomowy indeks procesu
        int rand_num = rand_process(gen); 
        //do tablicy z minimalną sumą dodaję wylosowany element
        processors[min_index].push_back(processors[max_index][rand_num]);
        //dodaję tę wartość do sumy w tab min i odejmuję z tab max
        processors[min_index][0] += processors[max_index][rand_num];
        processors[max_index][0] -= processors[max_index][rand_num];
        //usuwam wylosowaną liczbę z tab max
        processors[max_index].erase(processors[max_index].begin() + rand_num);

        //na nowo szukam min i max
        min = max = processors[0][0];
        min_index = max_index = 0;
        for (int i = 1; i < nProcs; i++) {
            if (processors[i][0] < min) {
                min = processors[i][0];
                min_index = i;
            }
            else if (processors[i][0] > max) {
                max = processors[i][0];
                max_index = i;
            }
        }
    }
    */
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

    vector<int> **shuffles = new vector<int>*[populationSize];
    int value, minValue, bestIndex = 0;
    shuffles[0] = new vector<int>[nProc];
    for (int i = 0; i < nProc; i++) {
        shuffles[0][i].push_back(0);
    }
    for(int i = 0; i < nProc; i++){
        int rand_num = distr(gen);
        shuffles[0][rand_num].push_back(tasks[i]);
        shuffles[0][rand_num][0] += tasks[i];
    }
    minValue = evaluate(shuffles[0], nProc);

    for(int i = 1; i < populationSize; i++){
        shuffles[i] = new vector<int>[nProc];
        for (int j = 0; j < nProc; j++) {
            shuffles[i][j].push_back(0);
        }
 
        for(int j = 0; j < nTasks; j++){
            int rand_num = distr(gen);
            shuffles[i][rand_num].push_back(tasks[j]);
            shuffles[i][rand_num][0] += tasks[j];
        }
        if((value = evaluate(shuffles[i], nProc) < minValue)){
            minValue = value;
            bestIndex = i;
        }
    }
    // chyba trzeba dynamicznie jakoś usunąć tą tablicę wektorów ale nie wiem
    return shuffles[bestIndex];
}
