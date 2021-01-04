//
// Created by 1912m on 04/01/2021.
//

#define N 10

class Barrier {
private:
    int arr1[N];
    int arr2[N];
    int working;
public:
    Barrier() {
        for (int i = 0; i < N; ++i) {
            arr1[i] = 0;
            arr2[i] = 0;
        }
        working = 0;
    }

    increase() {
        if (CAS())
        working++;

    }

    decrease() {

        working--;

    }

    wait() {
        while (working != 0) {}
    }
};