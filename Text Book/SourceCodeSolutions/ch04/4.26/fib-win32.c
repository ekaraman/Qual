/*
 * Windows solution to exercise 4.26
 *
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013.
 */

#include <stdio.h>
#include <windows.h>


/** we will only allow up to 256 Fibonacci numbers */
#define MAX_SIZE 256

int fibs[MAX_SIZE];


/* the thread runs in this separate function */
DWORD WINAPI Summation(PVOID Param)
{
    DWORD upper = *(DWORD *)Param;
	int i;


	if (upper== 0)
		return 0;
	else if (upper == 1)
		fibs[0] = 0;
	else if (upper== 2) {
		fibs[0] = 0;
		fibs[1] = 1;
	}
	else { // sequence > 2
		fibs[0] = 0;
		fibs[1] = 1;

		for (i = 2; i < upper; i++)
			fibs[i] = fibs[i-1] + fibs[i-2];
	}

	return 0;
}


int main(int argc, char *argv[])
{
	DWORD ThreadId;
	HANDLE ThreadHandle;
	int Param;

	// do some basic error checking
	if (argc != 2) {
		fprintf(stderr,"An integer parameter is required\n");
		return -1;
	}

	Param = atoi(argv[1]);

	if ( (Param < 0) || (Param > 256) ) {
		fprintf(stderr, "an integer >= 0 and < 256 is required \n");
		return -1;
	}

	// create the thread
	ThreadHandle = CreateThread(NULL, 0, Summation, &Param, 0, &ThreadId);

	if (ThreadHandle != NULL) {
		WaitForSingleObject(ThreadHandle, INFINITE);
		CloseHandle(ThreadHandle);

                /** now output the Fibonacci numbers */
                for (int i = 0; i < Param; i++)
                    printf("%d\n", fibs[i]);
	}
}
