/*
// Projeto SO - exercicio 1, version 03
// Sistemas Operativos, DEI/IST/ULisboa 2017-18
// Ficheiro error_handling.h
// Bibliotecas de Erros especificos para o projeto
*/

# ifndef __ERROR__
# define __ERROR__

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_WRONG_ARGS 2
# define EXIT_MSG_EXCH 3
# define EXIT_MEM_ALLOC 4
# define EXIT_SIMUL 5
# define EXIT_LIB_ERR 6
# define EXIT_THR_ERR 7
# define EXIT_MUTEX_ERR 8
# define EXIT_COND_ERR 9
# define EXIT_FILE_ERR 10
# define EXIT_FORK_ERR 11
# define EXIT_SIG_ERR 12
# define EXIT_ALOC_ERR 13


void errMsgExch(int origin, int destination);
void errThrCreate(int n_error);
void errThrJoin(int n_error);
void errMutex(int n_error);
void errCondVar(int n_error);
void errStream(int n_error, char * name);
void errFileSystem(int n_error, char *name);
void errFork(int n_error);
void errWait(int n_error, long ppid, long cpid);
void errInstSig(int n_error);
void errSigMask(int n_error, int how);
void errAlloc(int n_error);

# endif
