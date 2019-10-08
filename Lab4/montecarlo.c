#include <stdio.h>        // printf()
#include <stdlib.h>       // atoi(), exit(), ...
#include <pthread.h>      // pthread types and functions
#include <sys/time.h>
#define NUM_THREADS 16
#define SAMPLE_POINTS_PER_THREAD 10000

void *compute_pi (void *s) {

	int seed, i, *hit_pointer;
	double x_coord, y_coord;
	int local_hits;
	hit_pointer = (int *) s;
	seed = *hit_pointer;
	local_hits = 0;
	for (int i = 0; i < SAMPLE_POINTS_PER_THREAD; i++) {
		x_coord = (double) (rand_r(&seed))/(RAND_MAX) - 0.5;
		y_coord = (double) (rand_r(&seed))/(RAND_MAX) - 0.5;
		if((x_coord * x_coord + y_coord * y_coord) < 0.25)
			local_hits++;
	}
	*hit_pointer = local_hits;
	pthread_exit(0);

}

int main(int argc, char** argv) {

	int hits[NUM_THREADS], i, total_hits;
	double pi;
	struct timeval start, end;

	pthread_t p_threads[NUM_THREADS];
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	gettimeofday(&start, NULL);

	for (i = 0; i < NUM_THREADS; i++) {	
		hits[i] = i;
		pthread_create(&p_threads[i], &attr, compute_pi, (void*) &hits[i]);
	}

	for (i = 0; i < NUM_THREADS; i++) {
		pthread_join(p_threads[i], NULL);
		total_hits += hits[i];
	}
	pi = (double) 4 * total_hits / (NUM_THREADS * SAMPLE_POINTS_PER_THREAD);
	gettimeofday(&end, NULL);
  	printf("ms: %ld\n", (end.tv_usec - start.tv_usec));
	printf("ESTIMATE FOR PI: %f\n", pi);

}