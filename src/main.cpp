#include <iostream>
#include <fstream>
#include <vector>
#include "../lib/PCmax.hpp"

using namespace std;

template <typename T>
bool checkFile(T &f){
    if (!f){
        cerr << "File not opened" << endl;
        return false;
    }
    return true;
}

int main(){
    int INSTANCES = 10;
    for (int i = 1; i <= INSTANCES; i++){
        string benchmark = "instances/benchmark_";
        benchmark += to_string(i);
        cout << benchmark << endl;
        ifstream f(benchmark);
        if (!checkFile(f)) return -1;

        int Cmax, nProc, nTasks, *tasks;
        f >> Cmax >> nProc >> nTasks;
        tasks = new int[nTasks];
        for(int i = 0; i < nTasks; i++) f >> tasks[i];
        f.close();

        string evInstanceName = "outputs/ev/evolutional_";
        string grInstanceName = "outputs/gr/greedy_";
        evInstanceName += to_string(i);
        grInstanceName += to_string(i);

        ofstream ev(evInstanceName);
        if(!checkFile(ev)) return -2;
        ev << Cmax << endl << nProc << endl << nTasks << endl;
        ofstream gr(grInstanceName);
        if(!checkFile(gr)) return -3;
        gr << Cmax << endl << nProc << endl << nTasks << endl;
        
        // cout << "CMAX : " << Cmax << endl << endl;
        cout << evInstanceName  << "..." << endl;
        vector<int>* E = PCmax::evolutional(nProc, nTasks, tasks);
        // E = PCmax::evolutional(nProc, nTasks, tasks);
        cout << grInstanceName  << "..." << endl;
        vector<int> G = PCmax::greedy(nProc, nTasks, tasks);
        for (int i = 0; i < nProc; i++) {
            //cout << E[i][0] << " " endl; 
            ev << E[i][0] << endl;
            gr << G[i] << endl;
        } 
        ev.close();
        gr.close();
    }

    return 0;
}

