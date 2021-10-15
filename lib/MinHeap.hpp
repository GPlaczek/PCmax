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
    int find_max_heap_value() {
    //iterate only through leaves
        int max_value = array[size / 2]; //first leaf
        for(int i = (size / 2) + 1; i < size; i++) { //i = size / 2 + 1 <- second leaf
            max_value = max(max_value, array[i]);
        }
        return max_value;
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
    void max_heap_element(){
        cout << "Czas wykonania: " << find_max_heap_value();
    }

};
