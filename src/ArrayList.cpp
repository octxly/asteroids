#ifndef ARRAYLIST
#define ARRAYLIST

template <class T>
class ArrayList{
  private:
    T arr[10];

  public:
    int numElements = 0;
    int max = 10;
  
    void add(T obj){
      if (numElements == max) return;

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

    template <typename Lambda>
    void forEach(Lambda callback){
      for(int i = 0; i < numElements; i++){
        callback(&(arr[i]));
      }
    }
};

#endif
