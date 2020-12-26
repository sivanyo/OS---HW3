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


struct mutex_pipe {
/* 1*/      char bbuf_[BUFSIZ];
/* 2*/      size_t bpos_;
/* 3*/      size_t blen_;

    mutex_pipe() {
/* 4*/          this->bpos_ = this->blen_ = 0;
/* 5*/          memset(this->bbuf_, 0, BUFSIZ);
    }

    // Read up to `sz` bytes from this mutex_pipe into `buf` and return the number of bytes
    // read. If no bytes are available, wait until at least one byte can be read.
    ssize_t read(char* buf, size_t sz) {
/* 6*/           size_t pos = 0;
/* 7*/           while (pos < sz && (pos == 0 || this->blen_ != 0)) {
/* 8*/               if (this->blen_ != 0) {
/* 9*/                   buf[pos] = this->bbuf_[this->bpos_];
/*10*/                   ++this->bpos_;
/*11*/                   this->bpos_ = this->bpos_ % BUFSIZ;
/*12*/                   --this->blen_;
/*13*/                   ++pos;
/*14*/               }
/*15*/           }
/*16*/           return pos;
    }

    // Write up to `sz` bytes from `buf` into this mutex_pipe and return the number of bytes
    // written. If no space is available, wait until at least one byte can be written.
    ssize_t write(const char* buf, size_t sz) {
/*17*/          size_t pos = 0;
/*18*/          while (pos < sz && (pos == 0 || this->blen_ < BUFSIZ)) {
/*19*/              if (this->blen_ != BUFSIZ) {
/*20*/                  size_t bindex = this->bpos_ + this->blen_;
/*21*/                  bindex = bindex % BUFSIZ;
/*22*/                  this->bbuf_[bindex] = buf[pos];
/*23*/                  ++this->blen_;
/*24*/                  ++pos;
/*25*/              }
/*26*/          }
/*27*/          return pos;
    }
};
