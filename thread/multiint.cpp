#include <stdio.h>
#include <math.h>

#include <chrono>

#include <pthread.h>
#include <unistd.h>

inline double f(double x) {
    return sqrt(4 - x*x);
}

struct CalcArgs {
    double a, b, h, sum;
    int n;
};

void *calc_int (void *_args) {
    CalcArgs *args = (CalcArgs*)_args;

    for (int i = 1; i < args->n; i++)
        args->sum += f(args->a + i * args->h);

    args->sum += (f(args->a) + f(args->b)) / 2;
    pthread_exit(NULL);
}

int main (int argc, char **argv) {
    int n = 0, t = 0;
    printf ("Input N and T\n");
    scanf ("%d %d", &n, &t);

    CalcArgs *args = (CalcArgs*) calloc(t, sizeof(*args));
    pthread_t *threads = (pthread_t*) calloc (t, sizeof (*threads));

    auto t1 = std::chrono::high_resolution_clock::now();
    double a = 0, b = 2;
    double h = (b-a)/n;
        
    // TODO add if n%t != 0

    for (int k = 0; k < t; k++) {
        args[k].h = h;
        args[k].n = n/t;
        args[k].a = a + k * (n/t) * h;
        args[k].b = args[k].a + n/t * h;
        args[k].sum = 0;
        
        // printf ("%f %d %f %f %f\n", args[k].h,
        //     args[k].n,
        //     args[k].a,
        //     args[k].b,
        //     args[k].sum
        // );

        pthread_create (threads + k, NULL, calc_int, args + k);
    }

    double sum = 0;
    for (int k=0; k < t; k++) {
        pthread_join (threads[k], NULL);
        // printf ("%d's ans is %f\n", k, args[k].sum);
        sum += args[k].sum;
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dt = t2 - t1;

    printf ("Ans is %f with t = %f ms\n", sum * h, dt.count());

    free(args);
    free(threads);
}
