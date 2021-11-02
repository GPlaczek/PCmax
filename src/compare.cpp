#include <iostream>
#include <fstream>
#include <string>
#include "../lib/PCmax.hpp"
using namespace std;

int main(){
    int nInst; cin >> nInst;
    ifstream f;
    ofstream f_brute("../outputs/brute");
    ofstream f_greedy("../outputs/greedy");
    ofstream f_lpt("../outputs/lpt");
    ofstream f_genO("../outputs/geneticO");
    ofstream f_genG("../outputs/geneticG");
    string pattern = "../instances/instance_", temp;

    for(int i = 1; i <= nInst; i++){
        temp = pattern + to_string(i);
        f.open(temp);
        if (!f){ cerr << "File not opened" << endl; exit(0); }
        int nProc, nTasks, *tasks;
        f >> nProc >> nTasks;
        tasks = new int[nTasks];
        for(int i = 0; i < nTasks; i++) f >> tasks[i];
        f.close();

        f_brute << PCmax::brute(nProc,nTasks,tasks) << endl;
        f_greedy << PCmax::greedy(nProc,nTasks,tasks) << endl;
        f_lpt << PCmax::lpt(nProc,nTasks,tasks) << endl;
        f_genO << PCmax::geneticO(nProc,nTasks,tasks) << endl;
        f_genG << PCmax::geneticG(nProc,nTasks,tasks) << endl;
        
        delete[] tasks;
    }    

    fcloseall();
    return 0;
}
