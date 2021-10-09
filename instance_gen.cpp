#include <iostream>
#include <time.h>
#include <cstdlib>
#include <fstream>
#define LO 0.2
#define HI 0.5
#define MIN_TASK 50
#define MAX_TASK 10000
#define MIN_TIME 20
#define MAX_TIME 500
using namespace std;

int main(){
    srand(time(NULL));
    // m - liczba procesorow
    // n - liczba zadan
    int m, n;
    // wspolczynnik fract = m/n
    float fract = LO + (float) (rand()) / ((float) (RAND_MAX / (HI - LO))); // (LO, Hi)

    // liczba zadan 50 < n < 10000
    n = rand() % (MAX_TASK - MIN_TASK) + MIN_TASK;
    m = (int) (fract * n);

    fstream f;
    f.open("file1", ios::out);
    if (!f) { cerr << "File not opened" << endl; }

    f << m << endl << n << endl;

    // czasy zadan 20 << n << 500
    for (int i = 0; i < n; i++) {
        m = rand() % (MAX_TIME - MIN_TIME) + MIN_TIME;
        f << m << endl;
    }

    f.close();

    return 0;
}