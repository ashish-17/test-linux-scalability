/*
 * main.c
 *
 *  Created on: 15-Aug-2015
 *      Author: ashish
 *
 *  Command line arguments: <nThreads> <objSize> <nIterations>
 */


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct _ThreadData {
	int nThreads;
	int objSize;
	int iterations;
	int repetitions;
	int threadId;
} ThreadData;


void workerNormal(void *data) {
	ThreadData* threadData = (ThreadData*) data;
	char **ptr = (char**) malloc(sizeof(char*) * threadData->iterations);
	for (int i = 0; i < threadData->iterations; i++) {
		ptr[i] = malloc(threadData->objSize);
	}
	for (int i = 0; i < threadData->iterations; i++) {
		free(ptr[i]);
	}
	free(ptr);
}

int main(int argc, char* argv[]) {

	int nThreads, objSize, iterations;

	if (argc == 4) {
		nThreads = atoi(argv[1]);
		objSize = atoi(argv[2]);
		iterations = atoi(argv[3]);
	}
	else {
		printf("Error: Not enough arguments provided\n");
		return 1;
	}

	struct timeval start, end;
	ThreadData *threadData = (ThreadData*)malloc(nThreads * sizeof(ThreadData));
	pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * nThreads);
	int rc;

	gettimeofday (&start, NULL);
	for (int t = 0; t < nThreads; t++) {
		threadData[t].nThreads = nThreads;
		threadData[t].objSize = objSize;
		threadData[t].iterations = iterations;
		threadData[t].threadId = t;

		rc = pthread_create((threads + t), NULL, workerNormal, (threadData + t));
		if (rc) {
			printf("ERROR; return code from pthread_create() is %d", rc);
			exit(-1);
		}
	}

	void *status;
	for (int t = 0; t < nThreads; t++) {
		rc = pthread_join(threads[t], &status);
	}
	gettimeofday (&end, NULL);

	long int timeTaken = ((end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec ));
	printf("%ld", timeTaken);

	free(threadData);
}
