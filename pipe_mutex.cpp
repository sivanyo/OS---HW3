//
// Created by sivan on 12/26/2020.
//
struct pope_mutex {
    int fd[2];

    pipe_mutex() {
        int r = pipe(this->fd);
        assert(r == 0);
        ssize_t n = write(this->fd, "!", 1);
        assert(n == 1);
    }

    void lock() {
        char ch;
        while (read(this->fd, &ch, 1) != 1) {
        }
    }

    void unlock() {
        ssize_t n = write(this->fd, "!", 1);
        assert(n == 1);
    }
};

