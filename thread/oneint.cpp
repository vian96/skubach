#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <chrono>

inline double f(double x) {
    return sqrt(4 - x*x);
}

struct CalcArgs {
    double a, b, h, sum;
    int n;
};

void calc_int (CalcArgs *args) {
    for (int i = 1; i < args->n; i++)
        args->sum += f(args->a + i * args->h);

    args->sum += (f(args->a) + f(args->b)) / 2;
}

int main (int argc, char **argv) {
    int n = 0;
    printf ("Input N\n");
    scanf ("%d", &n);

    auto t1 = std::chrono::high_resolution_clock::now();

    CalcArgs args = {};
    args.a = 0;
    args.b = 2;
    args.h = (args.b-args.a) / n;
    args.sum = 0;
    args.n = n;

    // printf ("%f %d %f %f %f\n", args.h,
    //     args.n,
    //     args.a,
    //     args.b,
    //     args.sum
    // );

    calc_int (&args);

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> dt = t2 - t1;

    printf ("Ans is %f with t = %f ms\n", args.sum * args.h, dt.count());
}
