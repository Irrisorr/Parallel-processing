#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 1000000000;
double step;

int main(int argc, char *argv[])
{
    clock_t ppstart, ppstop;
    double pswtime, pewtime;

    for (int j = 1; j <= 16; j*=2)
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
        #pragma omp for
        for (i = 0; i < num_steps; i++)
        {
            x = (i + .5) * step;
            #pragma omp atomic
            sum = sum + 4.0 / (1. + x * x);
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









/*
----------------------- 3 zadanie -----------------------
>==========> threads = 1 <==========<
 3.141592653590 Wartosc liczby PI rownolegle 
Czas procesorów przetwarzania równoleglego  9.580131 sekund 
Czas trwania obliczen rownoleglych - wallclock 9.580610 sekund 
Przyspieszenie 0.122 

>==========> threads = 2 <==========<
 3.141592653590 Wartosc liczby PI rownolegle 
Czas procesorów przetwarzania równoleglego  98.430112 sekund 
Czas trwania obliczen rownoleglych - wallclock 49.715598 sekund 
Przyspieszenie 0.023 

>==========> threads = 4 <==========<
 3.141592653590 Wartosc liczby PI rownolegle 
Czas procesorów przetwarzania równoleglego  317.837858 sekund 
Czas trwania obliczen rownoleglych - wallclock 80.466023 sekund 
Przyspieszenie 0.015 

>==========> threads = 8 <==========<
 3.141592653590 Wartosc liczby PI rownolegle 
Czas procesorów przetwarzania równoleglego  749.219672 sekund 
Czas trwania obliczen rownoleglych - wallclock 107.586432 sekund 
Przyspieszenie 0.011 

>==========> threads = 16 <==========<
 3.141592653590 Wartosc liczby PI rownolegle 
Czas procesorów przetwarzania równoleglego  914.115382 sekund 
Czas trwania obliczen rownoleglych - wallclock 118.808071 sekund 
Przyspieszenie 0.010 

*/