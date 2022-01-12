#ifndef PCMAX_HPP
#define PCMAX_HPP

#include <vector>

using namespace std;

class PCmax{
    static int evaluate(vector<int>*, int);
    static vector<int> *populate(int, int, int*, int);
    static vector<int> *repopulate(vector<int>*, int, int, int);
public:
    static vector<int> *evolutionary(int, int, int*);
    static vector<int> greedy(int, int, int*);
};
#endif