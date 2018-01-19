/*
// Projeto SO - exercicio 1, version 03
// Sistemas Operativos, DEI/IST/ULisboa 2017-18
// Ficheiro: sequential.c
*/

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include "simul.h"
# include "../lib/mplib3.h"

typedef struct thread_args {
	int lines;         // Number of lines to CALCULATE (N//nThreads)
	int columns;       // Number of collums to CALCULATE(N)
	int iter;          // Number of interactions
	double tEsq, tSup, tDir, tInf;  // Border initial values
} pThread_args;


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
	pThread_args args;
	int id, lines, columns, iter;

	// Information we have: id
	id = * (int*) received_id;


	// The main thread sends the rest of the info via messages
	if (receberMensagem(0, id, &args, sizeof(args))!=sizeof(args))
		errMsgExch(0, id);

	// Information on matrix size to simulate
	lines = args.lines;
	columns = args.columns;
	iter = args.iter;

	// Information about threads
	int notTopThread, notBottomThread, isOddThread;
	notTopThread = (id != 1);
	notBottomThread = (id != (columns/lines));
	isOddThread = (id % 2);

	// Creating buffers of appropriate size
	double line_buffer[columns+2];
	int sizeof_line = sizeof(line_buffer);
	DoubleMatrix2D *m, *aux, *tmp;

	m = dm2dNew(lines+2, columns+2);
	aux = dm2dNew(lines+2, columns+2);

	// General variables
	int i, j;

	// Matrix Reconstruction
	if(!notTopThread) {                        //tSup
		dm2dSetLineTo(m, 0, args.tSup);
	}
	if(!notBottomThread) {                     //tInf
		dm2dSetLineTo(m, lines+1, args.tInf);
	}
	dm2dSetColumnTo(m, 0, args.tEsq);         //tEsq
	dm2dSetColumnTo(m, columns+1, args.tDir); //tDir


	// copy the border to aux matrix
	dm2dCopy(aux, m);


	/*------------------------*\
	| Thread Iterations's loop |
	\*------------------------*/
	for (; iter > 0; iter--) {

		// Step 1: get the new temps to matrix aux, using info from matrix m
		for (i = 1; i <= lines; ++i) {
			for (j = 1; j <= columns; ++j) {
				dm2dSetEntry(aux, i, j, next_value(m, i, j));
			}
		}

		// Swapping matrixes - now matrix m has the values for this iteration
		tmp = m;
		m = aux;
		aux = tmp;

		/* Step 2: send/get results to/from neighbors on the borders
		* To avoid deadlock:
		* - If the thread is odd: first receive, then send
		* - If the thread is even: first send, then receive
		* Caveats:
		* -	If we have a topThread, it does not need to send nor receive info
		*  	on its upper border, because it is constant (tSup)
		* - The same logic applies to bottomThread: last line is constant
		*/
		if (isOddThread) {
			goto receive;
		}

		send: // Send results to neighbors
		if(notTopThread)
			if (enviarMensagem(id, id-1, dm2dGetLine(m, 1), sizeof_line)!=sizeof_line)
				errMsgExch(id, id-1);

		if(notBottomThread)
			if (enviarMensagem(id, id+1, dm2dGetLine(m, lines), sizeof_line)!=sizeof_line)
				errMsgExch(id, id+1);

		if (isOddThread)
			continue; // Jumps to the next cycle/iteration

		receive: // Get results from neighbors and change values accordingly
		if(notTopThread) {
			if (receberMensagem(id-1, id, (void*) line_buffer, sizeof_line)!=sizeof_line)
				errMsgExch(id-1, id); // error handling
			dm2dSetLine(m, 0, line_buffer);
		}

		if(notBottomThread) {
			if (receberMensagem(id+1, id, (void*) line_buffer, sizeof_line)!=sizeof_line)
				errMsgExch(id+1, id); // error handling
			dm2dSetLine(m, lines+1, line_buffer);
		}

		if (isOddThread)
			goto send;

		/* ---------------------------
		 /!\ Do not add code beyond
		 this point due to the gotos
		-----------------------------*/

	} //Iteration loop ends here


	/*------------------*\
	| Thread termination |
	\*------------------*/
	// Send thread's matrix lines to the main thread
	for (i = 1; i <= lines; ++i) {
		if (enviarMensagem(id, 0, dm2dGetLine(m, i), sizeof_line)!=sizeof_line)
			errMsgExch(id, 0); // error handling
	}

	// Freeing matrixes memory
	dm2dFree(m);
	dm2dFree(aux);

	pthread_exit(0);
}

/*--------------------------------------------------------------------
| Function: simul_t_m
---------------------------------------------------------------------*/

DoubleMatrix2D *simul_t_m(DoubleMatrix2D *matrix, int linhas, int colunas, int nIter, int nThreads, int csz) {
	// This function acts as the master thread

	// Step 0: Verifying conditions to proceed
	if(linhas < 2 || colunas < 2)
		exit(EXIT_WRONG_ARGS);

	 // MPlib3 Inicialization
	 // nThreads + 1 -> simul needs to send messages to threads
	if (inicializarMPlib(csz, nThreads+1)) {
		fprintf(stderr, "\nErro: inicializacao da biblioteca MPlib3\n\n");
		exit(EXIT_LIB_ERR);
	}


	// Step 1: Gather information to send to slave threads +
	//         setting up varibles
	pThread_args init_args;

	//	Info on matrix size for each thread
	init_args.lines = (linhas-2) / nThreads;
	init_args.columns = colunas-2;
	init_args.iter = nIter;

	// Info on the matrix initial values
	init_args.tEsq = dm2dGetEntry(matrix, 1, 0);
	init_args.tSup = dm2dGetEntry(matrix, 0, 1);
	init_args.tDir = dm2dGetEntry(matrix, 1, colunas-1);
	init_args.tInf = dm2dGetEntry(matrix, linhas-1, 1);

	// Arrays for thread control
	pthread_t threadArray[nThreads]; // Thread id
	int id_array[nThreads];

	// Buffers
	int sizeof_line = colunas*sizeof(double);
	double line_buffer[colunas];


	// General variables
	int i, j, k, retVal;


	// Step 2: Launching slave threads and distribute work


	// Launching workers
	for( i=0; i<nThreads; ++i ) {
		/* The last argument, instead of being a pointer, is a int,
		 * containing the channel number dedicated to this thread. 0 is the
		 * current thread.
		 */
		id_array[i] = i+1;
		retVal = pthread_create(threadArray+i,NULL,thread_worker, (void*) (id_array+i));
		if(retVal) {
			fprintf(stderr, "\nFalha ao criar threads.\n"
					"Erro: %s [error code %d]\n", strerror(retVal), retVal);
			exit(EXIT_THR_ERR);
		}
	}


	// Sending information to threads
	for (i=1; i<=nThreads; ++i ) {
		if (enviarMensagem(0,i, (void *) &init_args, sizeof(init_args)) \
		    !=sizeof(init_args))
			errMsgExch(0, i); // error handling
	}

	// Step 3: Collecting results and joining the workers

	k=0; // Number of the line that is being retrieved
	for( i=0; i<nThreads; ++i ) {
		// Collect results line-by-line
		for( j=1; j<=init_args.lines; ++j ) {
			if (receberMensagem(i+1, 0, line_buffer, sizeof_line)!=sizeof_line)
				errMsgExch(i+1, 0); // error handling
			dm2dSetLine(matrix, ++k, line_buffer);
		}
		// Join worker thread
		retVal = pthread_join(threadArray[i], NULL);
		if(retVal) {
			fprintf(stderr, "\nFalha ao reunir threads.\n"
					"Erro: %s [error code %d]\n", strerror(retVal), retVal);
			exit(EXIT_THR_ERR);
		}
	}


	// Last Step: Cleaning up memory and returning results
	libertarMPlib(); // free the library

	return matrix;
}
