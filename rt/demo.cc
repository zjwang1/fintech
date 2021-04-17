#include <pthread.h>
#include <sched.h>

#include <cstdio>
#include <cstdlib>

struct ThreadArgs
{
    ThreadArgs(int num) : num_(num) {}
    int num_;
};

void print(int num) {
    for (int i = 0; i < num; ++i)
        printf("hello\n");
}

void *testThread(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *)args;
    print(thread_args->num_);
    return (void *)NULL;
}

int setPthreadAttrSchedParam(pthread_attr_t *attr, int pol, int prio) {
    int detS;
    detS = PTHREAD_EXPLICIT_SCHED;
    if (pthread_attr_setinheritsched(attr, detS) != 0) {
        perror("setPthreadAttrSchedParam");
        printf("ERROR: setPthreadAttrSchedParam failed %s:%d\n", __FILE__, __LINE__);
        return -1;
    }

    struct sched_param param;
    param.sched_priority = prio;

    if (pthread_attr_setschedpolicy(attr, pol) != 0) {
        perror("setPthreadAttrSchedParam");
        return -1;
    }
   
    if (pthread_attr_setschedparam(attr, &param) != 0) {
        perror("setPthreadAttrSchedParam");
        return -1;
    }

    return 0;
}

int main(int argc, char **argv) {
    pthread_t tid;
    pthread_attr_t *attr = (pthread_attr_t *) malloc(sizeof(pthread_attr_t));
    if (!attr) {
        printf("Alloc pthread attr failed!");
        abort();
    }
    pthread_attr_init(attr);
    setPthreadAttrSchedParam(attr, SCHED_FIFO, sched_get_priority_max(SCHED_FIFO) - 10);
    ThreadArgs args(5);
    if (pthread_create(&tid, attr, testThread, (void *) &args) == -1) {
        printf("Thread creation failed!");
    } else {
        pthread_join(tid, (void **) NULL);
    }
    if (attr != NULL) {
      pthread_attr_destroy(attr);
      free(attr);
    }
}