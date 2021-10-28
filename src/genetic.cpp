#include "../lib/PCmax.hpp"
#include <iostream>
#include <random>

using namespace std;

int genetic(int nProcs, int nTasks, int *tasks){
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

    // Tablica na aktualne uszeregowanie i na najlepsze dotychczasowe uszeregowanie
    vector<int> *bestShuffle = new vector<int>[nProc];
    vector<int> *shuffle;
    int value, minValue; // zmienne przechowujące najlepszą dotychczasową wartość i aktualną wartość

    // Wartość pierwszego uszeregowania jest na początku najlepsza
    for (int i = 0; i < nProc; i++) {
        bestShuffle[i].push_back(0);
    }
    for(int i = 0; i < nTasks; i++){
        int rand_num = distr(gen);
        bestShuffle[rand_num].push_back(tasks[i]);
        bestShuffle[rand_num][0] += tasks[i];
    }
    minValue = evaluate(bestShuffle, nProc);

    for(int i = 1; i < populationSize; i++){
        // Generowanie kolejno nowych uszeregowań
        shuffle = new vector<int>[nProc];
        for (int j = 0; j < nProc; j++) {
            shuffle[j].push_back(0);
        }
        for(int j = 0; j < nTasks; j++){
            int rand_num = distr(gen);
            shuffle[rand_num].push_back(tasks[j]);
            shuffle[rand_num][0] += tasks[j];
        }
        value = evaluate(shuffle, nProc);
        if(value < minValue){
            // Jeśli nowe uszeregowanie jest najlepsze to podmieniamy
            minValue = value;
            for(int a = 0; a < nProc; a++) bestShuffle[a] = move(shuffle[a]);
        }
        delete [] shuffle; // czyszczenie tablicy po każdej iteracji
    }
    return bestShuffle;
}
