#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 1000000000;
double step;

int main(int argc, char *argv[])
{
    clock_t ppstart, ppstop;
    double pswtime, pewtime;

    int thread_counts[] = {1, 2, 4, 8, 16};

    for (int j = 0; j < 5; j++)
    {
        int num_threads = thread_counts[j];

        // volatile
        double x, pi;
        int i;
        // RÓWNOLEGLE
        pswtime = omp_get_wtime();
        ppstart = clock();
        step = 1. / (double)num_steps;

        volatile double sum[16] = {0};

        #pragma omp parallel num_threads(num_threads)
        #pragma omp for
        for (i = 0; i < num_steps; i++)
        {
            x = (i + .5) * step;
            sum[omp_get_thread_num()] += 4.0 / (1. + x * x);
        }

        double full_sum = 0.0;
        for (int k = 0; k < num_threads; k++)
        {
            full_sum += sum[k];
        }
        pi = full_sum * step;

        ppstop = clock();
        pewtime = omp_get_wtime();

        printf(">==========> threads = %d <==========<\n", num_threads);
        printf("%15.12f Wartosc liczby PI rownolegle \n", pi);
        printf("Czas procesorów przetwarzania równoleglego  %f sekund \n", ((double)(ppstop - ppstart) / CLOCKS_PER_SEC));
        printf("Czas trwania obliczen rownoleglych - wallclock %f sekund \n\n", pewtime - pswtime);
    }

    return 0;
}