#include <iostream>
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
        for(int i = 0; i < size; i++){
            array[i] = 0;
        }
    }
    void fixHeap(){
        heapify(0);
    }
    T &operator[](int i){
        return array[i];
    }
};
