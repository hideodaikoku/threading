/** 
 *	Author: RODNEY VAN METER
 * 	Modified: HIDEO DAIKOKU
 * 	Class: OPERATING SYSTEMS SPRING 2019
 * 	Assignment: Threads
 */

// Threads with enough work to hopefully have something interesting happen
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

#define NUM_THREADS 1000
#define THRESHOLD 1000
#define GCOUNTER 10000000

// this is the master lock for the thread, used later
pthread_mutex_t master_lock = PTHREAD_MUTEX_INITIALIZER;

//// Code from Ch. 29 in OSTEP

typedef struct __counter_t {
	// init: record threshold, init locks,
	int global;			// global count
	pthread_mutex_t glock;	// global lock
	int local[NUM_THREADS];	// local count (per cpu)
	pthread_mutex_t llock[NUM_THREADS];  // ... and locks
	int threshold; // update frequency
} counter_t;

/**
 * Intializes thee counter structure by locking the global thread, sets the global count to zero
 * Sets the threshold for printing
 * intializes all threads to zero
 * locks all threads
*/
void init(counter_t *c) {
	c->threshold = THRESHOLD; // keeps threshold as defined on the top
	c->global = 0; // starts global count at 0
	pthread_mutex_init(&c->glock, NULL); // locks the current thread
	int i;
	for (i=0;i<NUM_THREADS;i++){
		c->local[i] = 0; // sets all thread counts to zero 
		pthread_mutex_init(&c->llock[i], NULL); //locks all threads
	}
}

void getCPUCores(){
	long numofcpus = sysconf(_SC_NPROCESSORS_ONLN);
	printf("Number of CPU Cores is %lu\n",numofcpus);
}
// update: usually, just grab local lock
// once local count has risen by
// lock and transfer local values to it
void update(counter_t *c, int threadID, int amt) {
	int cpu = threadID % NUM_THREADS;
	// printf("in %d: %d\n", threadID, c->local[cpu]);
	pthread_mutex_lock(&c->llock[cpu]);
	c->local[cpu] += amt; // assumes amt > 0
	if (c->local[cpu] >= c->threshold) { // transfer to global
		pthread_mutex_lock(&c->glock);
		c->global += c->local[cpu];
		pthread_mutex_unlock(&c->glock);
		c->local[cpu] = 0;
	}
	pthread_mutex_unlock(&c->llock[cpu]);
	// printf("out %d: %d\n", threadID, c->local[cpu]);
}

// get: just return global amount (which may not be perfect)
int get(counter_t *c) {
	pthread_mutex_lock(&c->glock);
	int val = c->global;
	pthread_mutex_unlock(&c->glock);
	return val; // only approximate!
}

///// end of code from OSTEP

counter_t global_counter;

void *mythread(void *arg) {
    int lcounter = GCOUNTER/NUM_THREADS;
    int mythreadid = *(int *)arg;
    printf("%d: start\n", mythreadid);
    /* lcounter here is just the local loop -- how many times are we going to loop? */
    while (lcounter) {
	    if (get(&global_counter) % 1000000 == 0 && get(&global_counter) > 0)
		    printf("%d: lcounter: %d gcounter: %d\n",mythreadid, lcounter, get(&global_counter));
	    update(&global_counter, mythreadid, +1); /* call the shared counter's update routine */
	    lcounter--;
    }
    printf("lcounter: %d\n",lcounter);
    return NULL;
}

int main(int argc, char *argv[]) {
	getCPUCores();
    pthread_t threads[NUM_THREADS];
    int rc;
    int threadid = 0;
    printf("main: begin\n");

	// intialize the global counter
    init(&global_counter);

    /* create our threads and fire them off */
    for (int i = 0 ; i < NUM_THREADS ; i++ ) {
	    rc = pthread_create(&threads[i], NULL, mythread, &threadid); assert(rc == 0);
	    threadid++;
    }
    // join waits for the threads to finish
    printf("Okay, main() (our original thread) now waiting...\n");
    for (int i = 0 ; i < NUM_THREADS ; i++ ) {
	    rc = pthread_join(threads[i], NULL); assert(rc == 0);
    }
    printf("get(&global_counter): %d\n",get(&global_counter));
    printf("main: end\n");
    return 0; 
}
