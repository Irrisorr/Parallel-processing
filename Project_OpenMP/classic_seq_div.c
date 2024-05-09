#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include <omp.h>

int main()
{

    clock_t spstart, spstop;
	double sswtime, sewtime;

    int m = 1;
    int n = 30;

    bool *result = (bool *)malloc((n - m + 1) * sizeof(bool));
    memset(result, true, (n - m + 1) * sizeof(bool));

    bool *primeArray = (bool *)malloc((sqrt(n) + 1) * sizeof(bool));
    memset(primeArray, true, (sqrt(n) + 1) * sizeof(bool));

    sswtime = omp_get_wtime();
	spstart = clock();

    for (int i = 2; i * i <= n; i++)
    {
        for (int j = 2; j * j <= i; j++)
        {
            if (primeArray[j] == true && i % j == 0)
            {
                primeArray[i] = false;
                break;
            }
        }
    }

    for (int i = m; i <= n; i++)
    {
        for (int j = 2; j * j <= i; j++)
        {
            if (primeArray[j] == true && i % j == 0)
            {
                result[i - m] = false;
                break;
            }
        }
    }


    spstop = clock();
    sewtime = omp_get_wtime();

    printf("Czas procesorów przetwarzania sekwencyjnego  %f sekund \n", ((double)(spstop - spstart)/CLOCKS_PER_SEC));
	printf("Czas trwania obliczen sekwencyjnych - wallclock %f sekund \n",  sewtime-sswtime);
	
    printf("Proste liczby w zakresie od %d do %d:\n", m, n);
    for (int i = m+1; i <= n; i++) {
        if (result[i - m]) {
            printf("%d ", i);
        }
    }

    free(result);
    free(primeArray);

    return 0;
}
