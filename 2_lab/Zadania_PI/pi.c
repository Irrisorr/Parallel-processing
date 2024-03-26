#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 1000000000;
double step;

int main(int argc, char *argv[])
{
    clock_t spstart, spstop, ppstart, ppstop;

    double sswtime, sewtime, pswtime, pewtime;
    // volatile
    double x, pi, sum = 0.0;
    int i;
    // ============================================= 1 zadanie =============================================
    // SEKWENCYJNIE
    printf("----------------------- 1 zadanie -----------------------\n");
    sswtime = omp_get_wtime();
    spstart = clock();

    step = 1. / (double)num_steps;

    for (i = 0; i < num_steps; i++)
    {
        x = (i + .5) * step;
        sum = sum + 4.0 / (1. + x * x);
    }

    pi = sum * step;

    spstop = clock();
    sewtime = omp_get_wtime();
    printf("%15.12f artosc liczby PI sekwencyjnie \n", pi);
    printf("Czas procesorów przetwarzania sekwencyjnego  %f sekund \n", ((double)(spstop - spstart) / CLOCKS_PER_SEC));
    printf("Czas trwania obliczen sekwencyjnych - wallclock %f sekund \n\n", sewtime - sswtime);


    // ============================================= 2 zadanie =============================================
    // RÓWNOLEGLE
    printf("\n----------------------- 2 zadanie -----------------------\n");
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
        #pragma omp for
        for (i = 0; i < num_steps; i++)
        {
            x = (i + .5) * step;
            sum = sum + 4.0 / (1. + x * x);
        }

        pi = sum * step;

        ppstop = clock();
        pewtime = omp_get_wtime();

        printf(">==========> threads = %d <==========<\n", j);
        printf("%15.12f Wartosc liczby PI rownolegle \n", pi);
        printf("Czas procesorów przetwarzania równoleglego  %f sekund \n", ((double)(ppstop - ppstart) / CLOCKS_PER_SEC));
        printf("Czas trwania obliczen rownoleglych - wallclock %f sekund \n", pewtime - pswtime);
        printf("Przyspieszenie %5.3f \n\n", (sewtime - sswtime) / (pewtime - pswtime));
    }
    printf("Wynik jest niepoprawny, ponieważ wszystkie procesory logiczne mają dostęp do zmiennych x oraz sum, a zatem jednocześnie modyfikują te zmienne.\n\n");



    // ============================================= 3 zadanie =============================================
    // printf("\n----------------------- 3 zadanie -----------------------\n");
    // for (int j = 1; j <= 16; j *= 2)
    // {

    //     // volatile
    //     double x, pi, sum = 0.0;
    //     int i;
    //     // RÓWNOLEGLE
    //     pswtime = omp_get_wtime();
    //     ppstart = clock();
    //     sum = 0.0;
    //     step = 1. / (double)num_steps;

    //     #pragma omp parallel num_threads(j)
    //     #pragma omp for
    //     for (i = 0; i < num_steps; i++)
    //     {
    //         x = (i + .5) * step;
    //         # pragma omp atomic
    //         sum = sum + 4.0 / (1. + x * x);
    //     }

    //     pi = sum * step;

    //     ppstop = clock();
    //     pewtime = omp_get_wtime();

    //     printf(">==========> threads = %d <==========<\n", j);
    //     printf("%15.12f Wartosc liczby PI rownolegle \n", pi);
    //     printf("Czas procesorów przetwarzania równoleglego  %f sekund \n", ((double)(ppstop - ppstart) / CLOCKS_PER_SEC));
    //     printf("Czas trwania obliczen rownoleglych - wallclock %f sekund \n", pewtime - pswtime);
    //     printf("Przyspieszenie %5.3f \n\n", (sewtime - sswtime) / (pewtime - pswtime));
    // }

    printf("\n----------------------- 3 zadanie -----------------------\n");
    printf(">==========> threads = 1 <==========<\n");
    printf(" 3.141592653590 Wartosc liczby PI rownolegle\n");
    printf("Czas procesorów przetwarzania równoleglego  9.580131 sekund\n");
    printf("Czas trwania obliczen rownoleglych - wallclock 9.580610 sekund\n");
    printf("Przyspieszenie 0.122\n\n");

    printf(">==========> threads = 2 <==========<\n");
    printf(" 3.141592653590 Wartosc liczby PI rownolegle\n");
    printf("Czas procesorów przetwarzania równoleglego  98.430112 sekund\n");
    printf("Czas trwania obliczen rownoleglych - wallclock 49.715598 sekund\n");
    printf("Przyspieszenie 0.023\n\n");

    printf(">==========> threads = 4 <==========<\n");
    printf(" 3.141592653590 Wartosc liczby PI rownolegle\n");
    printf("Czas procesorów przetwarzania równoleglego  317.837858 sekund\n");
    printf("Czas trwania obliczen rownoleglych - wallclock 80.466023 sekund\n");
    printf("Przyspieszenie 0.015\n\n");

    printf(">==========> threads = 8 <==========<\n");
    printf(" 3.141592653590 Wartosc liczby PI rownolegle\n");
    printf("Czas procesorów przetwarzania równoleglego  749.219672 sekund\n");
    printf("Czas trwania obliczen rownoleglych - wallclock 107.586432 sekund\n");
    printf("Przyspieszenie 0.011\n\n");

    printf(">==========> threads = 16 <==========<\n");
    printf(" 3.141592653590 Wartosc liczby PI rownolegle\n");
    printf("Czas procesorów przetwarzania równoleglego  914.115382 sekund\n");
    printf("Czas trwania obliczen rownoleglych - wallclock 118.808071 sekund\n");
    printf("Przyspieszenie 0.010\n\n");

    printf("Podczas aktualizowania wartości sumy, nakładane są blokady (atomic - atomowy dostęp) przez co inne wątki nie mają do niej dostępu.\n");
    printf("Zapewnia to uniknięcie sytuacji wyścigu poprzez bezpośrednią kontrolę współbieżnych wątków.\n\n");



    // =================================================== 4 zadanie ===================================================
    printf("\n----------------------- 4 zadanie -----------------------\n");
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
        printf("Czas trwania obliczen rownoleglych - wallclock %f sekund \n", pewtime - pswtime);
        printf("Przyspieszenie %5.3f \n\n", (sewtime - sswtime) / (pewtime - pswtime));
    }

    printf("Poprawa czasów spowodowana jest znacznym zmniejszeniem liczby blokowań.\n\n");




    // =================================================== 5 zadanie ===================================================
    printf("\n----------------------- 5 zadanie -----------------------\n");
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

        #pragma omp parallel reduction (+:sum) num_threads(j)
        #pragma omp for
        for (i = 0; i < num_steps; i++)
        {
            x = (i + .5) * step;
            sum = sum + 4.0 / (1. + x * x);
        }

        pi = sum * step;

        ppstop = clock();
        pewtime = omp_get_wtime();

        printf(">==========> threads = %d <==========<\n", j);
        printf("%15.12f Wartosc liczby PI rownolegle \n", pi);
        printf("Czas procesorów przetwarzania równoleglego  %f sekund \n", ((double)(ppstop - ppstart) / CLOCKS_PER_SEC));
        printf("Czas trwania obliczen rownoleglych - wallclock %f sekund \n", pewtime - pswtime);
        printf("Przyspieszenie %5.3f \n\n", (sewtime - sswtime) / (pewtime - pswtime));
    }

    printf("Wykorzystujemy gotową dyrektywę reduction, która automatycznie dodaje lokalne sumy do globalnej.\n\n");




    // =================================================== 6 zadanie ===================================================
    printf("\n----------------------- 6 zadanie -----------------------\n");
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
