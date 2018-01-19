# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include "error_handling.h"

void err_template(int n_error, char* error_string);


void err_template(int n_error, char* error_string) {
	fprintf(stderr, "%s", error_string);
	fprintf(stderr, "Erro: %s [error code %d]", strerror(n_error), n_error);
}

void errMsgExch(int origin, int destination) {
  fprintf(stderr, "\nError: Exchanging messages between threads %d and %d\n\n", origin, destination);
  exit(EXIT_MSG_EXCH);
}


void errThrCreate(int n_error) {
	err_template(n_error, "\nFalha ao criar threads.\n");
}

void errThrJoin(int n_error) {
	err_template(n_error, "\nFalha ao reunir threads.\n");
}

void errMutex(int n_error) {
	err_template(n_error, "\nFalha ao manipular mutex.\n");
}

void errCondVar(int n_error) {
	err_template(n_error, "\nFalha ao manipular variaveis de condicao.\n");
}

void errStream(int n_error, char *name) {
	err_template(n_error, "\nFalha ao abrir/fechar ficheiro\n");
	fprintf(stderr, "\nNome do ficheiro: %s\n", name);
}

void errFileSystem(int n_error, char *name) {
	err_template(n_error, "\nFalha ao mover/apagar ficheiros\n");
	fprintf(stderr, "\nNome do ficheiro: %s\n", name);
}

void errFork(int n_error) {
	err_template(n_error, "\nFalha ao criar processo filho\n");
}


void errWait(int n_error, long ppid, long cpid) {
	err_template(n_error, "\nFalha ao esperar por processo filho\n");
	fprintf(stderr, "\nPai: %ld, Filho: %ld\n", ppid, cpid);
}

void errInstSig(int n_error) {
	err_template(n_error, "\nErro ao instalar o sinal\n");
}

void errSigMask(int n_error, int how) {
	switch (how) {
		case SIG_UNBLOCK:
			err_template(n_error, "\nErro ao desbloquear signal set \n");
			break;
		case SIG_SETMASK:
			err_template(n_error, "\nErro ao definir mascara de sig set \n");
			break;
		case SIG_BLOCK:
			err_template(n_error, "\nErro ao bloquear signal set \n");
			break;
	}
}

void errAlloc(int n_error) {
	err_template(n_error, "\nFalha ao alocar memoria\n");
}
