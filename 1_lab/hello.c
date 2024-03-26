#include <stdio.h>
#include <omp.h>

int main() {
	int i = 5;
#pragma omp parallel num_threads(3)
{
	//int i; //zmienna prywatna wątku
	//printf("my id= %d \n", omp_get_thread_num());
	//printf("Hello World\n");
	#pragma omp for schedule(guided, 1)
	for (i = 0; i < 6; i++)
		printf("Iter:%d, wykonał: %d\n", i, omp_get_thread_num());
	// bariera wątków i synchronizacja obrazów danych
	printf("GoodBye World\n");
}
printf("%d\n", i);
}