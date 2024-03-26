#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 1000000000;
double step;

int main(int argc, char *argv[])
{
    clock_t ppstart, ppstop;
    double pswtime, pewtime;

    for (int j = 1; j <= 16; j *= 2)
    {

        // volatile
        double x, pi, sum = 0.0;
        int i;
        // RÓWNOLEGLE
        pswtime = omp_get_wtime();
        ppstart = clock();
        sum = 0.0;
        step = 1. / (double)num_steps;

        #pragma omp parallel num_threads(j)
        {
            double private_sum = 0.0;
            #pragma omp for
            for (i = 0; i < num_steps; i++)
            {
                x = (i + .5) * step;
                private_sum = private_sum + 4.0 / (1. + x * x);
            }

            # pragma omp atomic
            sum = sum + private_sum;
        }

        pi = sum * step;

        ppstop = clock();
        pewtime = omp_get_wtime();

        printf(">==========> threads = %d <==========<\n", j);
        printf("%15.12f Wartosc liczby PI rownolegle \n", pi);
        printf("Czas procesorów przetwarzania równoleglego  %f sekund \n", ((double)(ppstop - ppstart) / CLOCKS_PER_SEC));
        printf("Czas trwania obliczen rownoleglych - wallclock %f sekund \n\n", pewtime - pswtime);
    }

    return 0;
}
