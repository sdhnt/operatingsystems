#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

#define NUM_CHOPSTICKS 3
#define NUM_PEOPLE 10


sem_t left_chopstick_sem;
sem_t right_chopstick_sem;

int count = 0;

void *eat(void *arg) {
	int tid = *(int*) arg;
	int isFull = 0;
	time_t t;
	/* Intializes random number generator */
	srand((unsigned) time(&t));
	while(isFull == 0)
	{
		sem_wait(&left_chopstick_sem);
		printf("Philosopher(%d) picks up left chopstick\n", tid);
		fflush(stdout);
		if(sem_trywait(&right_chopstick_sem) == 0)
		{
			t = time(NULL);
			printf("Philosopher(%d) picks up right chopstick\n", tid);
			fflush(stdout);
			printf("\tPhilosopher(%d): eating... \n", tid);
			fflush(stdout);
			sleep(rand() % 15);  // randomly sleep
			printf("\tPhilosopher(%d): Yummy yummy!\n", tid);
			fflush(stdout);
			isFull = 1;
			sem_post(&right_chopstick_sem);
			printf("Philosopher(%d) puts down right chopstick\n", tid);
			fflush(stdout);
		}
		sem_post(&left_chopstick_sem);
		printf("Philosopher(%d) puts down left chopstick\n", tid);
		fflush(stdout);
	}
	pthread_exit(0);
}

int main() {
	sem_init(&left_chopstick_sem, 0, NUM_CHOPSTICKS) ;
	sem_init(&right_chopstick_sem, 0, NUM_CHOPSTICKS) ;
	pthread_t threads[NUM_PEOPLE];
	int tids[NUM_PEOPLE];
	int i, rc;
	for( i = 0; i < NUM_PEOPLE; i++) {
		tids[i] = i;
		if ((rc = pthread_create(&threads[i], NULL, eat, &tids[i]))){
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return EXIT_FAILURE;
		}
	}

	for( i = 0; i < NUM_PEOPLE; i++) {
		pthread_join(threads[i], NULL);
	}
	sem_destroy(&left_chopstick_sem);
	sem_destroy(&right_chopstick_sem);

	return 0;
}
