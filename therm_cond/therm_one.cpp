#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <chrono>

void calc_arr (double *cur, double *prev, int len, double k) {
    for (int i = 1; i + 1 < len; i++)
        cur[i] = prev[i] + k * (prev[i-1] + prev[i+1] - 2 * prev[i]);
}

int main() {
    double a = 0, b = 1, l = 1, T = 0;
    int len_steps = 0;

    printf ("Input N and T\n");
    scanf ("%d %lf", &len_steps, &T);

    double h = l / len_steps;
    double dt = 0.3 * h * h; // 0.3 is from Kurant's condition
    double k = dt/h/h;
    int time_steps = T/dt;
    printf ("Calculated len steps is %d, time steps is %d\n", len_steps, time_steps);
    
    double *cur = (double*) calloc (len_steps, sizeof(*cur));
    double *prev = (double*) calloc (len_steps, sizeof(*prev));

    cur[0] = a;
    prev[0] = a;
    cur[len_steps - 1] = b;
    prev[len_steps - 1] = b;

    auto t1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < time_steps; i++) {
        calc_arr (cur, prev, len_steps, k);
        std::swap (cur, prev);
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> mes_time = t2 - t1;
    printf ("Time is %f\n", mes_time.count());


    FILE *f_out = fopen ("out.txt", "w");
    for (int i = 0; i < len_steps; i++)
        fprintf (f_out, "%f %f\n", h*i, cur[i]);
    fclose (f_out);

    system ("python3 graph.py");
}