#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_LOOPS 1000000
long long counter = 0;
sem_t sem;
sem_t sem1;
void* counting_thread(void* arg) {

	int offset = *(int*) arg;
	//printf("Thread with offset: %d\n",offset);
	int i;
	for(i = 0; i < NUM_LOOPS; i++){
		counter += offset;
	}
	sem_post(&sem);

	pthread_exit(NULL);
}

int main() {
	sem_init(&sem, 0, 1);

	pthread_t th1;
	sem_wait(&sem);
	int offset = 1;
	pthread_create(&th1, NULL, counting_thread, &offset);

	pthread_t th2;
  sem_wait(&sem);
	offset = -1;
sem_post(&sem);
	pthread_create(&th2, NULL, counting_thread, &offset);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	printf("Finnal counter value: %lld\n", counter);
	sem_destroy(&sem);
	return 0;
}
