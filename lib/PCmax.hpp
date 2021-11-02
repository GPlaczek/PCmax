#include <vector>

using namespace std;

class PCmax{
public:
    static int evaluate(vector<int>*, int);
    static vector<int> *populate(int, int, int*, int);
    static int geneticG(int, int, int*);
    static int geneticO(int, int, int*);
    static int greedy(int, int, int*);
    static int brute(int, int, int*);
    static int lpt(int, int, int*);
};
