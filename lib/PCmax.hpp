#include <vector>

using namespace std;

class PCmax{
public:
    static int evaluate(vector<int>*, int);
    static vector<int> *populate(int, int, int*, int);
    static int genetic(int, int, int*);
    static int greedy(int, int, int*);
    static int brute(int, int, int*);
};
