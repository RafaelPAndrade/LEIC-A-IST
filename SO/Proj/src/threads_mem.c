/*
// Projeto SO
// Sistemas Operativos, DEI/IST/ULisboa 2017-18
// Ficheiro: thread_mem.c
*/

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <math.h>
# include "simul.h"

# define matrix_exch(A, B) { DoubleMatrix2D *t = A; A = B; B = t; }


typedef struct thread_args {
	int lines;         // Number of lines to CALCULATE (N//nThreads)
	int columns;       // Number of collums to CALCULATE(N)
	double maxD;       // minumum Deviation allowed for each cell
} pThread_args;

pThread_args init_args;

DoubleMatrix2D *m, *aux;

pthread_mutex_t mutex; // Mutex to protect global variables

pthread_cond_t barrier; // Cond for worker threads
pthread_cond_t master;  // Cond for master thread

int nWorkingThreads;   // number of threads working at a given time
int stop_workers;      // boolean(1-true, 0-false) - if threads shall terminate
int deviated;          // boolean(0-false, 1-true) - if passed the threshold
int globalIterNumber;  // number of the current iteraction to calculate (for sync)


static void * thread_worker(void * received_id);


/*--------------------------------------------------------------------
| Function: thread_worker
---------------------------------------------------------------------*/

void * thread_worker(void * received_id) {

	/*------------------*\
	|   Thread Startup   |
	\*------------------*/
	// Gathering information and setting variables

	// General information on the size of the simulation
	int id, lines, columns;
	double orig, next, maxD;


	// Information we have: id
	id = * (int*) received_id;


	// Information on matrix size to simulate
	lines = init_args.lines;
	columns = init_args.columns;
	maxD = init_args.maxD;


	// General variables
	int i, j, retVal;
	int offset = (id-1)*lines;
	int delta;
	int iteration = 0;


	/*------------------------*\
	| Thread Iterations's loop |
	\*------------------------*/
	retVal=pthread_mutex_lock(&mutex);
	if(retVal) {
		errMutex(retVal);
		exit(EXIT_MUTEX_ERR);
	}
	while (!stop_workers) {
		retVal = pthread_mutex_unlock(&mutex);
		if(retVal) {
			errMutex(retVal);
			exit(EXIT_MUTEX_ERR);
		}

		++iteration;
		// Step 1: get the new temps to matrix aux, using info from matrix m
		// at the same time, verifying if we already passed maxD
		delta = 0;
		for (i = 1; i <= lines; ++i) {
			for (j = 1; j <= columns; ++j) {
				orig = dm2dGetEntry(m, offset+i, j);
				next = next_value(m, offset+i, j)

				if (!delta && fabs(next - orig) >= maxD)
					delta = 1;

				dm2dSetEntry(aux, offset+i, j, next);
			}
		}


		retVal=pthread_mutex_lock(&mutex);
		if(retVal) {
			errMutex(retVal);
			exit(EXIT_MUTEX_ERR);
		}
		if (delta) deviated = 1;
		if (--nWorkingThreads == 0) {
			retVal = pthread_cond_signal(&master);
			if (retVal) {
				errCondVar(retVal);
				exit(EXIT_COND_ERR);
			}
		}
		do {
			retVal = pthread_cond_wait(&barrier, &mutex);
			if(retVal) {
				errCondVar(retVal);
				exit(EXIT_COND_ERR);
			}
		} while(iteration >= globalIterNumber); // globalIterNumber is a global
	}
	retVal = pthread_mutex_unlock(&mutex);
	if(retVal) {
		errMutex(retVal);
		exit(EXIT_MUTEX_ERR);
	}

	/*------------------*\
	| Thread termination |
	\*------------------*/
	pthread_exit(0);
}

/*--------------------------------------------------------------------
| Function: simul_t_m
---------------------------------------------------------------------*/

DoubleMatrix2D *simul_t_s(DoubleMatrix2D *matrix, int linhas, int colunas, int nIter, int nThreads, double maxD) {
	// This function acts as the master thread

	// Step 0: Verifying conditions to proceed
	if(linhas < 2 || colunas < 2)
		exit(EXIT_WRONG_ARGS);


	// Step 1: Gather information to send to slave threads +
	//         setting up varibles

	//	Info on matrix size for each thread
	init_args.lines = (linhas-2) / nThreads;
	init_args.columns = colunas-2;
	init_args.maxD = maxD;

	// Arrays for thread control
	pthread_t threadArray[nThreads]; // Thread id
	int id_array[nThreads];

	// Setting up global matrixes
	m = matrix;
	aux = dm2dNew(linhas, colunas);
	dm2dCopy(aux, m);

	// Initialize mutexes and cond variables
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&master, NULL);
	pthread_cond_init(&barrier, NULL);

	// General variables
	int i, retVal;


	// Step 2: Launching and managing worker threads
	// Launching workers
	retVal=pthread_mutex_lock(&mutex);
	if(retVal) {
		errMutex(retVal);
		exit(EXIT_MUTEX_ERR);
	}
	// Setting up global variables
	nWorkingThreads = nThreads;
	deviated = 0;
	stop_workers = 0;
	globalIterNumber = 1;

	for( i=0; i<nThreads; ++i ) {
		// Thread n.0 is for the master
		id_array[i] = i+1;
		retVal = pthread_create(threadArray+i,NULL,thread_worker, (void*) (id_array+i));
		if(retVal) {
			errThrCreate(retVal);
			exit(EXIT_THR_ERR);
		}
	}


	// Verifier loop
	for (; nIter>0; --nIter) {
		do {
			retVal = pthread_cond_wait(&master, &mutex);
			if (retVal) {
				errCondVar(retVal);
				exit(EXIT_COND_ERR);
			}
		} while(nWorkingThreads);

		// Swapping matrixes - now matrix m has the values for this iteration
		matrix_exch(m,aux);


		// If no thread has passed maxD, we stop the simulation
		if (deviated == 0) break;

		// Resetting variables for new iteration
		deviated = 0;
		nWorkingThreads = nThreads;
		++globalIterNumber;
		retVal = pthread_cond_broadcast(&barrier);
		if(retVal) {
			errCondVar(retVal);
			exit(EXIT_COND_ERR);
		}
	}

	// kill the threads
	stop_workers = 1;
	++globalIterNumber;
	retVal = pthread_cond_broadcast(&barrier);
	if(retVal) {
		errCondVar(retVal);
		exit(EXIT_COND_ERR);
	}
	retVal = pthread_mutex_unlock(&mutex);
	if(retVal) {
		errMutex(retVal);
		exit(EXIT_MUTEX_ERR);
	}


	// Step 3: Joining the workers
	for( i=0; i<nThreads; ++i ) {
		// Join worker thread
		retVal = pthread_join(threadArray[i], NULL);
		if(retVal) {
			errThrJoin(retVal);
			exit(EXIT_THR_ERR);
		}
	}

	// Cleanup and return
	// Destroy mutexes and cond variables
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&master);
	pthread_cond_destroy(&barrier);

	// Free auxiliary matrix
	dm2dFree(aux);

	return m;
}
