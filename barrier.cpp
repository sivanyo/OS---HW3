//
// Created by 1912m on 04/01/2021.
//

class Barrier
{
private:
    pthread_mutex_t mutex;
    int working;

public:
    Barrier()
    {
        working = 0;
        pthread_mutex_init(&mutex, NULL);
    }

    increase()
    {
        pthread_mutex_lock(&mutex);
        working++;
        pthread_mutex_unlock(&mutex);
    }

    decrease()
    {
        pthread_mutex_lock(&mutex);
        working--;
        pthread_mutex_unlock(&mutex);
    }

    wait()
    {
        pthread_mutex_lock(&mutex);
        while (working != 0)
        {
            pthread_mutex_unlock(&mutex);
            /** opportunity for other threads to continue running and not block the program
             *  this will allow the wait to be more efficient and also avoid the race conditions
             *  regarding the working counter that existed in the previous implementation */
            pthread_mutex_lock(&mutex);
        }
        pthread_mutex_unlock(&mutex);
    }
};