//
// Created by 1912m on 04/01/2021.
//

class Barrier {
private:
    pthread_mutex_t mutex;
    int working;
public:
    Barrier() {
        working = 0;
        pthread_mutexattr_t attribute;
        pthread_mutexattr_init(&attribute);
        pthread_mutexattr_settype(&attribute, PTHREAD_MUTEX_ERRORCHECK);
        pthread_mutex_init(&mutex, &attribute);
    }

    increase() {
        pthread_mutex_lock(&mutex);
        working++;
        pthread_mutex_unlock(&mutex);
    }

    decrease() {
        pthread_mutex_lock(&mutex);
        working--;
        pthread_mutex_unlock(&mutex);
    }

    wait() {
        while (working != 0) {}
    }
};