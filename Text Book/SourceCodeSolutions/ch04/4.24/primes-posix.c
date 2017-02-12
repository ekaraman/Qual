/**
 * Pthreads solution to exercise 4.24
 *
 * Compilation:
 *  gcc -lpthread primes-posix.c
 *
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <pthread.h>
#include <stdio.h>

/** we will only allow up to 256 prime numbers */
#define MAX_SIZE 256

int primes[MAX_SIZE];

void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
int i;
pthread_t tid; /* the thread identifier */
pthread_attr_t attr; /* set of attributes for the thread */

if (argc != 2) {
	fprintf(stderr,"usage: a.out <integer value>\n");
	return -1;
}

if (atoi(argv[1]) < 2) {
	fprintf(stderr,"Argument %d must be >= 2 \n",atoi(argv[1]));
	return -1;
}

/* get the default attributes */
pthread_attr_init(&attr);

/* create the thread */
pthread_create(&tid,&attr,runner,argv[1]);

/* now wait for the thread to exit */
pthread_join(tid,NULL);

/** now output the prime numbers */
for (i = 1; i <= atoi(argv[1]); i++)
	if (primes[i] > 0)
		printf("%d\n", i);
}

/**
 * Generate primes using the Sieve of Eratosthenes.
 */
void *runner(void *param) 
{
int i, j;
int upper = atoi(param);

	primes[1] = 0;
	for (i = 2; i <= upper; i++)
		primes[i] = 1;

	for (i = 2; i <= upper/2; i++)
		for (j = 2; j <= upper/i; j++)
			primes[i*j] = 0;

	pthread_exit(0);
}
