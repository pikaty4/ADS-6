// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <cassert>

template<typename T, int size>
class TPQueue {
 private:
    T* arr = new T[size+1];
    int top;
    int checkInd(int ind) {
        while (ind < 0) ind += size;
        while (ind > size) ind -= size;
        return ind;
    }

 public:
    TPQueue(): top(0) {}
    ~TPQueue() { delete[] arr; }

    T pop() {
        return arr[checkInd(top++)];
    }

    void push(const T &data) {
        if (arr[checkInd(top)].prior == -1) {
            arr[checkInd(top)] = data;
        } else {
            int i = top;
            int f = 0;
            while (data.prior <= arr[checkInd(i)].prior) {
                i++;
                f = 1;
            }
            if (f == 1) {
                if (arr[checkInd(i)].prior == -1) {
                    arr[checkInd(i)] = data;
                } else {
                    int k = i+1;
                    while (arr[checkInd(k)].prior != -1 &&
                        checkInd(k) != checkInd(top)) k++;
                    if (checkInd(k) == checkInd(top)) top++;
                    arr[checkInd(k)] = arr[checkInd(k - 1)];
                    arr[checkInd(i)] = data;
                }
                return;
            }
            arr[checkInd(--top)] = data;
        }
    }
};

struct SYM {
    char ch;
    int prior = -1;
};

#endif  // INCLUDE_TPQUEUE_H_
