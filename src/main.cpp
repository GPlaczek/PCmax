#include <iostream>
#include <fstream>
#include "../lib/PCmax.hpp"

using namespace std;

int main(){
    string filename;
    cin >> filename;
    ifstream f(filename);
    if(!f){
        cerr << "File not opened" << endl;
        return -1;
    }
    int nProc, nTasks, *tasks;
    f >> nProc >> nTasks;
    tasks = new int[nTasks];
    for(int i = 0; i < nTasks; i++) f >> tasks[i];
    f.close();
    cout << PCmax::genetic(nProc, nTasks, tasks) << endl;
    return 0;
}
