#ifndef ARRAYLIST
#define ARRAYLIST

#include <Arduino.h>

//Wrapper for an array that gives me more utility
template <class T, uint8_t size>
class List{
  private:
    T arr[size];
    uint8_t numElements = 0;

  public:
    void add(T obj){
      if (numElements == size) return;

      arr[numElements] = obj;
      numElements++;
    }
    void remove(T *obj){
      if (numElements == 0) return;

      for (uint8_t i = 0; i < numElements; i++){
        if (&(arr[i]) == obj){
          
          for (uint8_t j = i; j < numElements - 1; j++)
            arr[j] = arr[j + 1];

          numElements--;

          break;
        }  
      }
    }

    template <typename Lambda>
    void forEach(Lambda callback){
      for(uint8_t i = 0; i < numElements; i++)
        callback(&(arr[i]));
    }

    int getSize(){ return numElements; }
    int getMax(){ return size; }
};

#endif
