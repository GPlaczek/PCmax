#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class MinHeap{
    T *array;
    int size;
    void heapify(int i){
        while(2*i+1 < size){
            if(2*i+2 < size && array[2*i+2] < array[2*i+1] && array[2*i+2] < array[i]){
                swap(array[i], array[2*i+2]);
                i=2*i+2;
            }else if(array[2*i+1] <= array[i]){
                swap(array[i], array[2*i+1]);
                i=2*i+1;
            }else break;
        }
    }
    
public:
    MinHeap(int size, T *array){
        this -> array = array;
        this -> size = size;
        for(int i = size/2 - 1; i >= 0; i--){
            heapify(i);
        }
    }
    MinHeap(int size){
        array = new T[size];
        this -> size = size;
        for(int i = 0; i < size; i++){
            array[i] = 0;
        }
    }
    ~MinHeap(){
        delete array;
    }
    void fixHeap(){
        heapify(0);
    }
    T &operator[](int i){
        return array[i];
    }
    int maxValue(){
    //iterate only through leaves
        if(size > 1) {
            int max_value = array[size / 2]; //first leaf
            for(int i = (size / 2) + 1; i < size; i++) { //i = size / 2 + 1 <- second leaf
                max_value = max(max_value, array[i]);
            }
            return max_value;
        }
        else return array[0]; //the only existing element is the biggest one
    }
};
