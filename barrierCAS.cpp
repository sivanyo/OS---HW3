//
// Created by 1912m on 04/01/2021.
//

#define N 10

class Barrier {
private:
    int prodArr[N];
    int consumArr[N];
public:
    Barrier() {
        for (int i = 0; i < N; ++i) {
            // At the start producer can just work
            prodArr[i] = 1;
            // Consumer has no jobs, so it just waits
            consumArr[i] = 0;
        }
    }

    increase() {
        // we want to give consumer work
        bool switchConsume = false;
        bool switchProduce = false;
        int i = 0;
        int j = 0;
        while (!switchConsume && !switchProduce) {
            if (consumArr[i] == 0) {
                // this is an empty cell for consumer to get job
                if (prodArr[j] == 1) {
                    // this is a cell for producer to put job
                    if (!switchConsume && CAS(*consumArr + i, 0, 1) != 1) {
                        // We failed to change the value, so we try again
                        continue;
                    }
                    switchConsume = true;
                    if (!switchProduce && CAS(*prodArr + j, 1, 0) != 0) {
                        // We failed to change the value, so we try again
                        continue;
                    }
                    switchProduce = true;
                }
                j = inc_iterator(j);
                if (switchConsume && switchProduce) {
                    return;
                }
                continue;
            }
            i = inc_iterator(i);
        }
    }

    decrease() {
        // we want to mark that a consumer has finished it's work
        // we want to give consumer work
        bool switchConsume = false;
        bool switchProduce = false;
        int i = 0;
        int j = 0;
        while (!switchConsume && !switchProduce) {
            if (consumArr[i] == 1) {
                // this is a cell consumer used to get work from
                if (prodArr[j] == 0) {
                    // this is an empty cell for producer to later use for work
                    if (!switchConsume && CAS(*consumArr + i, 1, 0) != 0) {
                        // We failed to change the value, so we try again
                        continue;
                    }
                    switchConsume = true;
                    if (!switchProduce && CAS(*prodArr + j, 0, 1) != 1) {
                        // We failed to change the value, so we try again
                        continue;
                    }
                    switchProduce = true;
                }
                j = inc_iterator(j);
                if (switchConsume && switchProduce) {
                    return;
                }
                continue;
            }
            i = inc_iterator(i);
        }
    }

    wait() {
        bool canContinue = false;
        while (!canContinue) {
            for (int i = 0; i < N; ++i) {
                if (prodArr[i] == 0) {
                    // producer can't continue yet
                    break;
                }
            }
            // All consumers have finished, so producer can continue
            canContinue = true;
        }
    }

    inc_iterator(int i) {
        if (i == N - 1) {
            return 0;
        } else {
            return ++i;
        }
    }
};