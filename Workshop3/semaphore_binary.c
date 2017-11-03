#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TOTAL_COUNT 10000


sem_t sem1;

int count = 0;

void *func(void *arg) {
	int i;
	for(i = 0; i < TOTAL_COUNT; i++) {
		sem_wait(&sem1);
		count++;
		if ((count % 2500) == 0) {
			int id = *((int*)arg);
			printf("Thread %d: current count = %d\n", id, count);
		}
		sem_post(&sem1);
	}
	pthread_exit(0);
}

int main() {
	sem_init(&sem1,0,1) ; 
	pthread_t thread1, thread2,thread3;

	int id1 = 1;
	if(pthread_create(&thread1, NULL, &func, (void*)&id1)) {
		printf("ERROR creating thread 1\n");
		exit(1);
	}  
	int id2 = 2;
	if(pthread_create(&thread2, NULL, &func, (void*)&id2)) {
		printf("ERROR creating thread 2\n");
		exit(1);
	}
	int id3 = 3;
	if(pthread_create(&thread3, NULL, &func, (void*)&id3)) {
		printf("ERROR creating thread 3\n");
		exit(1);
	}

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);

	if (count != 3 * TOTAL_COUNT)
		printf("Error! current count is %d. total count should be %d\n", 
				count, 2 * TOTAL_COUNT);
	else
		printf("OK. current count is %d\n", count);
	sem_destroy(&sem1);

	return 0;
}

