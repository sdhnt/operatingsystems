#include <stdio.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/////////////////////////////////////////////GLOBAL VARIABLES
static double pi =0.0;
long num_steps;
static double step;
static int NUM_THREADS;
//////////////////////////////////////THREADTYPEDEF
typedef struct _thread_data_t {
	pthread_t tid;
	int num_threads;
	double num_steps;
} thread_data_t;
/////////////////////////////////////////THREAD FUNCTION
void *thr_func(void *arg) {
	long i; double x, sum = 0.0;

	thread_data_t *data = (thread_data_t *)arg;
	//int k=(int)data->tid;
	int start= ((data->num_steps/data->num_threads) * (data->tid-1))+1;
	int end= (data->num_steps/data->num_threads) * (data->tid);
	step = 1.0/((double) (data->num_steps));

	for (i=start;i<= end; i++){
		x = (i-0.5)*step;
		sum = sum + 4.0/(1.0+x*x);
	}
	//printf("SUM at from thr_func, thread id: %d is %f from %d to %d\n", k, sum, start, end);

	//pi = step * sum;
	long long *answer = malloc(sizeof(*answer));
	*answer = sum;
	pthread_exit(answer);
}

///////////////////////////////////////////////MAIN FUNCTION
int main (int argc, char **argv)
{


	if (argc < 3) {
		printf("Usage: %s <num of steps> <num of threads>\n", argv[0]);
		return EXIT_SUCCESS;
	}
	num_steps = atoll(argv[1]);
	NUM_THREADS = atoi(argv[2]);
	//printf("%d %ld \n", NUM_THREADS, num_steps );

	pthread_t thr[NUM_THREADS];
	long i, rc;
	/* create a thread_data_t argument array */
	thread_data_t thr_data[NUM_THREADS];
  double start_time, run_time;

step = 1.0/(double) num_steps;
//printf("%f \n", step );
 start_time = omp_get_wtime();
	/* create threads */

	for (i = 0; i < NUM_THREADS; ++i) {
		thr_data[i].tid = i +1;
		thr_data[i].num_steps = num_steps;
		thr_data[i].num_threads = NUM_THREADS;
		if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
			fprintf(stderr, "error: pthread_create, ");
			return EXIT_FAILURE;
		}
	}

	/* block until all threads complete */
	double sum=0.0;
	long long *thread_sum;
	for (i = 0; i < NUM_THREADS; ++i) {
		pthread_join(thr[i], (void**) &thread_sum);
		sum += *thread_sum;
	}
	pi = step * sum;
	  run_time = omp_get_wtime() - start_time;
	  printf("pi with %ld steps with %d threads is %lf in %lf seconds\n",num_steps,NUM_THREADS,pi,run_time);

	return EXIT_SUCCESS;



}
