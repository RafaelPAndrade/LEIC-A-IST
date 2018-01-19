/*
// Projeto SO
// Sistemas Operativos, DEI/IST/ULisboa 2017-18
// Ficheiro: thread_mem_save.c
*/

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <math.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include "simul.h"


# define matrix_exch(A, B) { DoubleMatrix2D *t = A; A = B; B = t; }

# define TEMP_NAME "~"

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

int flag_save; // number of the signal which requested a save; 0 if none


static void * thread_worker(void * received_id);
pid_t save_matrix(pid_t child_pid, DoubleMatrix2D *m, char* fichS, char* aux_fichS);
void sig_handler(int sig_n);

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
| Function: simul_t_s_f
---------------------------------------------------------------------*/

DoubleMatrix2D *simul_t_s_f(DoubleMatrix2D *matrix, int linhas, int colunas, int nIter, int nThreads, double maxD, char* fichS, int periodoS) {
	// This function acts as the master thread

	// Step 0: Verifying conditions to proceed
	if(linhas < 2 || colunas < 2)
		exit(EXIT_WRONG_ARGS);

	// PART I: Threads

	// Step 1: Gather information to send to slave threads +
	//         setting up variables

	//  General variables
	int i, retVal;

	//	Info on matrix size for each thread
	init_args.lines = (linhas-2) / nThreads;
	init_args.columns = colunas-2;
	init_args.maxD = maxD;

	// Arrays for thread control
	pthread_t threadArray[nThreads]; // Thread id
	int id_array[nThreads];


	// Setting up global matrixes

	//Opening file and see contents (assuming wellformed contents):
	FILE * f = fopen(fichS, "r");
	if(f != NULL) {
		DoubleMatrix2D * import = readMatrix2dFromFile(f,linhas,colunas);
		retVal = fclose(f);
		if(retVal) {
			errStream(errno, fichS);
		}
		if(import != NULL) {
			dm2dFree(matrix);
			matrix = import;
		}
	} else { //Error handling (report only)
		retVal = errno;
		if(retVal != ENOENT) { //ENOENT: File not found
			errStream(retVal, fichS);
		}

	}
	m = matrix;
	aux = dm2dNew(linhas, colunas);
	dm2dCopy(aux, m);

	// Initialize mutexes and cond variables
	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&master, NULL);
	pthread_cond_init(&barrier, NULL);

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

	// Block signals: SIGINT and SIGALRM
	// From now on, Ctrl-C will not kill the simulation
	sigset_t block_set;
	sigemptyset(&block_set);
	sigaddset(&block_set, SIGINT);
	sigaddset(&block_set, SIGALRM);
	retVal = pthread_sigmask(SIG_BLOCK, &block_set, NULL);
	if(retVal) {
		errSigMask(retVal, SIG_BLOCK);
		exit(EXIT_SIG_ERR);
	}



	for( i=0; i<nThreads; ++i ) {
		// Thread n.0 is for the master
		id_array[i] = i+1;
		retVal = pthread_create(threadArray+i,NULL,thread_worker, (void*) (id_array+i));
		if(retVal) {
			errThrCreate(retVal);
			exit(EXIT_THR_ERR);
		}
	}


	// PART II: Forks

	// Fork and matrix saving variables
	flag_save=0;
	pid_t child_pid=0;


	// Set a sigaction to deal with SIGINT and SIGALRM
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sig_handler;
	sa.sa_mask = block_set; // block other signals while in handler
	retVal = sigaction(SIGINT, &sa, NULL);
	if(retVal){
		errInstSig(retVal);
		exit(EXIT_SIG_ERR);
	}

	retVal = sigaction(SIGALRM, &sa, NULL);
	if(retVal){
		errInstSig(retVal);
		exit(EXIT_SIG_ERR);
	}


	// Unblock signals for this thread only
	retVal = pthread_sigmask(SIG_UNBLOCK, &block_set, NULL);
	if(retVal) {
		errSigMask(retVal, SIG_UNBLOCK);
		exit(EXIT_SIG_ERR);
	}



	// Construct temporary filename
	char * aux_fichS = (char*) calloc(sizeof(TEMP_NAME)+strlen(fichS), sizeof(char));
	if(aux_fichS == NULL) {
		errAlloc(errno);
		exit(EXIT_ALOC_ERR);
	}

	aux_fichS = memcpy(aux_fichS, fichS, strlen(fichS));
	aux_fichS = strncat(aux_fichS,TEMP_NAME, sizeof(TEMP_NAME));


	// First alarm
	alarm(periodoS);

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

		// Save matrix m to the file fichS
		if(flag_save) {
			retVal = pthread_sigmask(SIG_BLOCK, &block_set, NULL);
			if(retVal) {
				errSigMask(retVal, SIG_BLOCK);
				exit(EXIT_SIG_ERR);
			}

			child_pid = save_matrix(child_pid, m, fichS, aux_fichS);

			retVal = pthread_sigmask(SIG_UNBLOCK, &block_set, NULL);
			if(retVal) {
				errSigMask(retVal, SIG_UNBLOCK);
				exit(EXIT_SIG_ERR);
			}

		alarm(periodoS); // reset alarm
		}

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

	//Stop periodic saving
	alarm(0);

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

	// Wait for child
	if(child_pid) {
		retVal = waitpid(child_pid, NULL, 0); // blocking wait
		if(retVal == -1) {
			errWait(errno, (long) getpid(), (long) child_pid);
		}
	}

	// Free auxiliary matrix
	dm2dFree(aux);
	free(aux_fichS);
	return m;
}

// Matrix-saving routines
pid_t save_matrix(pid_t child_pid, DoubleMatrix2D *m, char* fichS, char* aux_fichS) {
	int child_status, retVal;

	// Check status of child, if it exists
	if(child_pid != 0) {
		retVal = waitpid(child_pid, &child_status, WNOHANG);
		if(retVal  == -1) {
			errWait(errno, (long) getpid(), (long) child_pid);
		}
	}

	// Fork if no child existed, or already exited
	if(child_pid == 0 || WIFEXITED(child_status)) {
		child_pid = fork();
		if(child_pid == 0) { // Child
			// Save the matrix to the file
			FILE *f = fopen(aux_fichS, "w");
			if(f == NULL) {
				errStream(errno, aux_fichS);
				exit(EXIT_FILE_ERR);
			}
			dm2dPrintToFile(m, f);
			retVal = fclose(f);
			if(retVal) {
				errStream(errno, fichS);
				exit(EXIT_FILE_ERR);
			}
			retVal = rename(aux_fichS, fichS);
			if(retVal) {
				errFileSystem(errno, aux_fichS);
				exit(EXIT_FILE_ERR);
			}
			exit(EXIT_SUCCESS);
		} else if(child_pid == -1) {
			errFork(errno);
		}
	}

	// At this point, at least a child is active
	if(flag_save == SIGINT) { //Received SIGINT, exit fast
		alarm(0); //Stop the clock
		retVal = waitpid(child_pid, &child_status, 0); // blocking wait
		if(retVal == -1) {
			errWait(errno, (long) getpid(), (long) child_pid);
		}
		exit(EXIT_SUCCESS);
	} else if(flag_save == SIGALRM) {
		flag_save = 0;
	}

	return child_pid;
}


// Signal handling routine - SIGINT and SIGALRM
void sig_handler(int sig_n) {
	// sig_n - number of the signal
	if(flag_save != SIGINT) { // SIGINT has priority
		flag_save = sig_n;
	}
}
