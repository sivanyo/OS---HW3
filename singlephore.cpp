//
// Created by sivan on 12/27/2020.
//
//Q2 part 1
typedef struct mutex {
    singlephore h;
} mutex;
void mutex_init (mutex * m) {
    singlefore_init(&(m->h));
}
// val meanings -
// 0 - the mutex is unlocked
// -1 - the mutex is locked
void mutex_lock (mutex * m) {
    // if someone using the lock, he will dec the value of h by 1, so if I want to use the lock,
    // I will need to wait until the val is 0, and than i will use the lock by singing the val to -1
    H(&(m->h), 0, -1);
}
void mutex_unlock (mutex * m) {
    // if i want to unlock the lock, i will wait until the val is -1 (this val shows that the lock is used,
    // and than i will change val to 0 to show that the lock is unlock
    H(&(m->h), -1, 1);
}

//Q2 part 2
typedef struct condvar {
    mutex m;
    singlephore h;
    int counter;
} condvar;
// Initilize the condition variable
void cond_init (condvar * c) {
    mutex_init(&(c->m));
    singlefore_init(&(c->h));
    // count the number of waiting threads
    c->counter = 0;
}
// Signal the condition variable
void cond_signal (condvar * c) {
    mutex_lock(c->m);
    // I want to get in to this code iff there are threads that waiting
    if(c->counter > 0){
        // MIN_INT is the min value integer can get
        H(&(c->h),MIN_INT, 1);
        // this thread is now no longer waiting, so i need to dec the number of waiting threads
        --c->counter;
    }
    mutex_unlock(c->m);
}
// Block until the condition variable is signaled. The mutex m must be locked by the
// current thread. It is unlocked before the wait begins and re-locked after the wait
// ends. There are no sleep-wakeup race conditions: if thread 1 has m locked and
// executes cond_wait(c,m), no other thread is waiting on c, and thread 2 executes
// mutex_lock(m); cond_signal(c); mutex_unlock(m), then thread 1 will always recieve the
// signal (i.e., wake up).
void cond_wait (condvar * c, mutex * m) {
    // i need to inc the number of waiting threads
    mutex_lock(c->m);
    ++c->counter;
    mutex_unlock(c->m);
    // now i need to wait, according to the notes, i need to unlock m, and relocked it after the wait ends
    mutex_unlock(m);
    // the wait ends when h->val == 0, and then we need to set h->val == -1
    H(&(c->h), 0, -1);
    mutex_lock(m);
}



