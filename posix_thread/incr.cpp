#include <cstdio>

#include <pthread.h>

static int glob = 0;

static void* threadFunc(void* arg) {
    int loops = *static_cast<int*>(arg);
    int loc = 0;

    for (int j=0; j<loops; ++j) {
        loc = glob;
        loc++;
        glob = loc;
    }

    return nullptr;
}

int main(int agrc, char* argv[]) {
    pthread_t t1, t2;
    int loops = 10000000;

    int s;
    s = pthread_create(&t1, nullptr, threadFunc, &loops);

    s = pthread_create(&t2, nullptr, threadFunc, &loops);

    s = pthread_join(t1, nullptr);

    s = pthread_join(t2, nullptr);

    printf("glob = %d\n", glob);
    printf("less than 2*loops");

    return 0;
}