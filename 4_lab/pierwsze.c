#include <stdio.h>
#include <omp.h>

#define NUM 100000000

int isprime( int x )
{
    for( int y = 5; y * y <= x; y=y+2 )
    {
        if( x % y == 0 )
            return 0;
    }

    return 1;
}

int main( )
{
    int sum = 0;

#pragma omp parallel num_threads(4)
#pragma omp parallel for schedule(static, 1) reduction (+:sum)
    for( int i = 3; i <= NUM ; i=i+2 )
    {
        sum += isprime ( i );
    }

    printf( "Number of primes numbers: %d", sum );

    return 0;
}

