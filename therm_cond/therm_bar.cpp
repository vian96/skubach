#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <chrono>
#include <algorithm>

pthread_barrier_t barrier;

struct ThermArgs {
    int len_steps, time_steps;
    double k;
    double *cur, *prev;
};

inline void calc_arr (double *cur, double *prev, int len, double k) {
    for (int i = 0; i < len; i++)
        cur[i] = prev[i] + k * (prev[i-1] + prev[i+1] - 2 * prev[i]);
}

void *calc_part (void *_args) {
    ThermArgs *args = (ThermArgs*) _args;
    for (int i = 0; i < args->time_steps; i++) {
        calc_arr (args->cur, args->prev, args->len_steps, args->k);
        std::swap (args->cur, args->prev);
        pthread_barrier_wait (&barrier);
    }
    
    pthread_exit(NULL);
}

int main() {
    double a = 0, b = 1, l = 1, T = 0;
    int len_steps = 0, tnum = 0;

    printf ("Input N, T and P\n");
    scanf ("%d %lf %d", &len_steps, &T, &tnum);

    assert (("Not divisible or small P! i dont work yet", len_steps % tnum == 0 && tnum > 0));

    pthread_barrier_init (&barrier, NULL , tnum);

    double h = l / len_steps;
    double dt = 0.3 * h * h; // 0.3 is from Kurant's condition
    double k = dt/h/h;
    int time_steps = T/dt;
    int part_len = len_steps/tnum;
    
    printf ("Calculated len steps is %d, time steps is %d\nPart len is %d\n", len_steps, time_steps, part_len);

    double *cur = (double*) calloc (len_steps, sizeof (*cur));
    double *prev = (double*) calloc (len_steps, sizeof (*prev));

    cur[0] = a;
    prev[0] = a;
    cur[len_steps - 1] = b;
    prev[len_steps - 1] = b;

    ThermArgs *args = (ThermArgs*) calloc (tnum, sizeof (*args));
    pthread_t *threads = (pthread_t*) calloc (tnum, sizeof (*threads));

    auto t1 = std::chrono::high_resolution_clock::now();

    args[0] = (ThermArgs) {part_len - 1, time_steps, k, cur + 1, prev + 1};
    pthread_create (threads, NULL, calc_part, args);

    for (int i = 1; i < tnum; i++) {
        args[i] = (ThermArgs) {part_len, time_steps, k, cur + part_len*i, prev + part_len*i};
        if (i == tnum - 1)
            args[i].len_steps--;
        pthread_create (threads + i, NULL, calc_part, args + i);
    }

    for (int i = 0; i < tnum; i++) 
        pthread_join (threads[i], NULL);

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> mes_time = t2 - t1;
    printf ("Time is %f\n", mes_time.count());

    FILE *f_out = fopen ("out.txt", "w");
    for (int i = 0; i < len_steps; i++)
        fprintf (f_out, "%f %f\n", h*i, cur[i]);
    fclose (f_out);

    system ("python3 graph.py");
}