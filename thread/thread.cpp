#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *func (void *c) {
    int *num = (int*)c;
    printf ("I am no %d\n", *num);
    pthread_exit(NULL);
}

int main (int argc, char **argv) {
    printf ("My argc is %d, argv is %p\n", argc, argv);
    sleep(1);
    
    pthread_t t[4];
    for (int i=0; i < 4; i++) {
        pthread_create (t+i, NULL, (void *(*)(void *)) main, (void*)i);
        sleep(1);
    }
// argument of type "int (*)(int argc, char **argv)" is incompatible with parameter of type "void *(*)(void *)"
    for (int i=0; i < 4; i++) {
        pthread_join (t[i], NULL);
    }
}
