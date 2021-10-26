#include "../lib/PCmax.hpp"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

int PCmax::genetic(int nProcs, int nTasks, int *tasks){
    // Tu kiedyś zadzieje się magia
    int max = 0, max_index = -1;
    vector <int> *processors = new vector <int>[nProcs];

    //zeruję zerowy indeks każdego z procesorów - to będzie suma długości zadań na każdym procesorze
    for (int i = 0; i < nProcs; i++) {
        processors[i].push_back(0);
    }

    //randomowa liczba z przedziału od 0 do liczba procesorów - 1
    //https://www.delftstack.com/howto/cpp/generate-random-number-in-range-cpp/ - warto przeczytać
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<int> distr(0, nProcs - 1); // define the range

    //każdy proces dodaję do randomowo wybranego procesora
    for (int i = 0; i < nTasks; i++) {
        int rand_num = distr(gen);
        processors[rand_num].push_back(tasks[i]);
        processors[rand_num][0] += tasks[i];
        //aktualizuję maksymalną wartość na bieżąco
        if (processors[rand_num][0] > max) {
            max = processors[rand_num][0];
            max_index = rand_num;
        }
    }

    //szukam min wartości sumy
    int min = processors[0][0]; //ustawiam min na pierwszą sumę 
    int min_index = 0; //indeks minimalnej sumy w tablicy processors
    for (int i = 1; i < nProcs; i++) {
        if (processors[i][0] < min) {
            min = processors[i][0];
            min_index = i;
        }
    }
        
    //int difference = max - min;
    //dążę do tego, żeby nowa różnica max - min była lepsza od poprzedniej (wartości będą "bliżej" siebie)
    //while (processors[max][0] - processors[min][0] < difference) {
  
    //}
    
    //wykonuję zamianę 5 razy, bo tak mi się zachciało
    for (int j = 0; j < 5; j++) {
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

    return max;
}
