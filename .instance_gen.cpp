#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#include <string>
#define LO 0.2
#define HI 0.5
#define MIN_TASK 50
#define MAX_TASK 10000
#define MIN_TIME 20
#define MAX_TIME 500
#define N_INSTANCES 10
using namespace std;

int main(){
    srand(time(NULL));
    int proc_n, tasks_n; // liczba zadan, procesorow
    float fract; // wspolczynnik fract = procesory / zadania
    ofstream f;
    char path[100];

    for (int i = 1; i <= N_INSTANCES; i++){
        fract = LO + (float) (rand()) / ((float) (RAND_MAX / (HI - LO)));
        tasks_n = rand() % (MAX_TASK - MIN_TASK) + MIN_TASK;
        proc_n = (int) (fract * tasks_n);

        sprintf(path, "\\instances\\instance_%d",i);
        f.open(path);
        if (!f) { cerr << "File not opened" << endl; return -1; }

        f << proc_n << endl << tasks_n << endl; 
        cout << "Creating instance " << i << " ..." << endl;

        for (int i = 0; i < tasks_n; i++) {
            proc_n = rand() % (MAX_TIME - MIN_TIME) + MIN_TIME;
            f << proc_n << endl;
        }
        f.close();
    }

    return 0;
}