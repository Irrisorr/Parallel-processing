#include <stdio.h>
#include <time.h>
#include <omp.h>

long long num_steps = 10000000;
double step;

int main(int argc, char* argv[])
{
	clock_t spstart, spstop,ppstart,ppstop;
	
	double sswtime, sewtime, pswtime, pewtime;
//volatile
	double x, pi, sum=0.0;
	int i;

double tab[50];
for (int j = 0; j < num_steps; j++)
{

//RÓWNOLEGLE 
	pswtime = omp_get_wtime();
	ppstart = clock();
	sum = 0.0;
	step = 1. / (double)num_steps;
# pragma omp parallel num_threads(4) // tworzy wiele wątków 

{int id = 2 * omp_get_thread_num();
    tab[j+id] = 0;

# pragma omp for schedule(dynamic, 1000)
	for (i = 0; i < num_steps; i++)
	{
		double x = (i + .5) * step;
        # pragma omp flush(tab) // odczyt sumy (odzcyt z pamięci)
 		    tab[j+id] = tab[j+id] + 4.0 / (1. + x * x);
        # pragma omp flush(tab) // synchronizacja sumy (zapis do pamięci)
	} // tutaj synchronizacja obrazów co wyliczył wątek (zapisuje do pamięci)
# pragma omp atomic 
sum += tab[j+id];

}

	pi = sum * step;

	ppstop = clock();
	pewtime = omp_get_wtime();

	printf("Czas trwania obliczen rownoleglych - wallclock %f sekund \n", pewtime-pswtime);
}
	return 0;
}



/*
1_sekw = 3
1_rown = 30
2_sekw (górne ograniczenie) = 3
2_rown (górne ograniczenie) = 6
*/


/*============================= liczenie czasu 

wątek * ile trzeba pracy

*/