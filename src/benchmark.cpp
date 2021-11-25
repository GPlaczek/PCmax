#include <iostream>
#include <fstream>
#include <random>

using namespace std;

int main(int argc, char *argv[]){
    int nProc, nTasks, PCmax;
    cin >> nProc >> nTasks >> PCmax;
    int **opt = new int*[nProc];
    int cuts = nTasks / nProc;
    random_device rd;
    mt19937 gen(rd());
    for(int i = 0; i < nProc; i++){
        opt[i] = new int[cuts];
        int sum = 0;
        for(int j = 0; j < cuts - 1; j++){
            uniform_int_distribution<int> distr(1, PCmax / cuts*2);
            int cut = distr(gen);
            opt[i][j] = cut;
            sum += cut;
        }
        if(PCmax - sum < 0){
            i--;
            continue;
        }
        opt[i][cuts - 1] = PCmax - sum;
    }
    ofstream f(argv[1]);
    f << nProc << endl;
    f << nTasks << endl;
    for(int i = 0; i < nProc; i++){
        for(int j = 0; j < cuts; j++){
            f << opt[i][j] << endl;
            if(opt[i][j] == 0) cout << i << " " << j << endl;
        }
    }
    return 0;
}
