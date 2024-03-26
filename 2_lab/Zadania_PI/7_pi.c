#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 1000000000;
double step;

int main(int argc, char *argv[])
{
    clock_t ppstart, ppstop;
    double pswtime, pewtime;

    // volatile
    double x, pi;
    int i;
    // RÓWNOLEGLE
    ppstart = clock();
    step = 1. / (double)num_steps;

    volatile double sum[50];

    for (int j = 0; j < 49; j++)
    {
        sum[j] = 0.0;
        sum[j + 1] = 0.0;

        pswtime = omp_get_wtime();

        #pragma omp parallel num_threads(2)
        {
            int id = omp_get_thread_num();
            #pragma omp for
            for (i = 0; i < num_steps; i++)
            {
                x = (i + .5) * step;
                sum[j+id] = sum[j+id] + 4.0 / (1. + x * x);
            }
        }

        pi = (sum[j] + sum[j+1]) * step;

        pewtime = omp_get_wtime();

        printf("%d iteracja, ", j+1);
        printf("%15.12f Wartosc liczby PI rownolegle, ", pi);
        printf("wallclock %f sekund \n", pewtime - pswtime);
    }

    ppstop = clock();
    printf("Czas procesorów przetwarzania równoleglego  %f sekund \n", ((double)(ppstop - ppstart) / CLOCKS_PER_SEC));
    return 0;
}