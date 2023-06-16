#ifndef ARRAYLIST
#define ARRAYLIST

#include <Function_objects.h>

template <class T, int size>
class ArrayList{
  private:
    T arr[size];
    int numElements = 0;

  public:
    void add(T obj){
      if (numElements == size) return;

      arr[numElements] = obj;
      numElements++;
    }
    void remove(T *obj){
      if (numElements == 0) return;

      for (int i = 0; i < numElements; i++){
        if (&(arr[i]) == obj){
          
          for (int j = i; j < numElements - 1; j++){
            arr[j] = arr[j + 1];
          }

          numElements--;

          break;
        }  
      }
    }

    void forEach(FunctionObject<void(T*)> callback){
      for(int i = 0; i < numElements; i++){
        callback(&(arr[i]));
      }
    }

    int getSize(){ return numElements; }
    int getMax(){ return size; }
};

#endif
