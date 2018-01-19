/*
// Biblioteca de troca de mensagens, versao 3
// Sistemas Operativos, DEI/IST/ULisboa 2017-18
*/

#include "mplib3.h"
#include "leQueue.h"

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*--------------------------------------------------------------------
| Types
---------------------------------------------------------------------*/

typedef struct message_t {
  QueElem   elem;
  void      *contents;
  int       mess_size;
  int       consumed;
} Message_t;

typedef struct channel_t {
  QueHead   *message_list;
  pthread_mutex_t    mutex;
  pthread_cond_t     wait_for_free_space;
  pthread_cond_t     wait_for_messages;
} Channel_t;


/*--------------------------------------------------------------------
| Global Variables
---------------------------------------------------------------------*/

int                channel_capacity;
int                number_of_tasks;
Channel_t          **channel_array;


/*--------------------------------------------------------------------
| Function: createChannel
| Description: Cria e devolve um ponteiro para um canal de comunicacao.
|              Em caso de erro devolve NULL.
---------------------------------------------------------------------*/

Channel_t* createChannel () {
  Channel_t *channel = (Channel_t*) malloc (sizeof(Channel_t));

  if (channel == NULL) {
    fprintf(stderr, "\nErro ao alocar memoria para canal\n");
    return NULL;
  }

  channel->message_list = leQueNewHead();

  if (channel->message_list == NULL) {
    fprintf(stderr, "\nErro ao criar lista de mensagens\n");
    return NULL;
  }

  leQueHeadInit (channel->message_list, 0);

  // mutex and condition variables for each channel
  if(pthread_mutex_init(&(channel->mutex), NULL) != 0) {
    fprintf(stderr, "\nErro ao inicializar mutex\n");
    return NULL;
  }
  if(pthread_cond_init(&(channel->wait_for_free_space), NULL) != 0) {
    fprintf(stderr, "\nErro ao inicializar variavel de condicao\n");
    return NULL;
  }
  if(pthread_cond_init(&(channel->wait_for_messages), NULL) != 0){
    fprintf(stderr, "\nErro ao inicializar variavel de condicao\n");
    return NULL;
  }

  return channel;
}


/*--------------------------------------------------------------------
| Function: inicializarMPlib
| Description: Inicializa a MPlib com ntasks*ntasks canais, cada um com
|              capacidade igual a capacidade_de_cada_canal.
|              Em caso de sucesso devolve 0.
|              Em caso de erro devolve -1.
---------------------------------------------------------------------*/


int inicializarMPlib(int capacidade_de_cada_canal, int ntasks) {
  int i, j;
  Channel_t* channel;

  number_of_tasks  = ntasks;
  channel_capacity = capacidade_de_cada_canal;
  channel_array    = (Channel_t**) malloc (sizeof(Channel_t*)*ntasks*ntasks);

  if (channel_array == NULL) {
    fprintf(stdout, "\nErro ao alocar memoria para MPlib\n");
    return -1;
  }

  for (i=0; i<ntasks; i++) {
    for (j=0; j<ntasks; j++) {
      channel = createChannel();
      if (channel == NULL) {
        fprintf(stdout, "\nErro ocorreu no canal (%d,%d)", i, j);
        return -1;
      }
      channel_array[i*number_of_tasks+j] = channel;
    }
  }
  return 0;
}


/*--------------------------------------------------------------------
| Function: libertarMPlib
| Description: Liberta a memoria alocada pela MPlib. Devolve void.
|              Em caso de erro, o processo e terminado.
---------------------------------------------------------------------*/

void libertarMPlib() {
  int i,j;

  for (i=0; i<number_of_tasks; i++) {
    for (j=0; j<number_of_tasks; j++) {
      Channel_t   *channel = channel_array[i*number_of_tasks+j];
      Message_t   *mess    = (Message_t*) leQueRemFirst(channel->message_list);

      while (mess) {
        if (channel_capacity>0)
          free (mess->contents);
        free (mess);
        mess = (Message_t*) leQueRemFirst(channel->message_list);
      }

      /* delete message list header for this channel
       * as well as the mutex and condition variables */
      leQueFreeHead (channel->message_list);
      if(pthread_mutex_destroy(&(channel->mutex)) != 0) {
        fprintf(stderr, "\nErro ao destruir mutex do canal (%d,%d)\n",i,j);
        exit(EXIT_FAILURE);
      }
      if(pthread_cond_destroy(&(channel->wait_for_free_space)) != 0) {
        fprintf(stderr, "\nErro ao destruir variavel de condicao do canal (%d,%d)\n",i,j);
        exit(EXIT_FAILURE);
      }
      if(pthread_cond_destroy(&(channel->wait_for_messages)) != 0) {
        fprintf(stderr, "\nErro ao destruir variavel de condicao do canal (%d,%d)\n",i,j);
        exit(EXIT_FAILURE);
      }
      free (channel);
    }
  }
  free (channel_array);
}


/*--------------------------------------------------------------------
| Function: receberMensagem
| Description: Recebe uma mensagem da tarefaOrig para a tarefaDest,
|              com um dado tamanho maximo, e coloca a mensagem no buffer
|              recebido. Se o canal nao estiver vazio, uma mensagem e removida
|              e colocada no buffer. Caso contrario, o recetor e bloqueado
|              ate a tarefa de origem enviar mensagens para o canal.
|              Em caso de sucesso devolve o tamanho da mensagem recebida.
|              Em caso de erro devolve -1.
---------------------------------------------------------------------*/

int receberMensagem(int tarefaOrig, int tarefaDest, void *buffer, int tamanho) {
  Channel_t      *channel;
  Message_t      *mess;
  int            copysize;

  channel = (Channel_t*) channel_array[tarefaDest*number_of_tasks+tarefaOrig];

  if(pthread_mutex_lock(&(channel->mutex)) != 0) {
    fprintf(stderr, "\nErro ao bloquear mutex do canal (%d,%d)\n", tarefaOrig, tarefaDest);
    return -1;
  }

  mess    = (Message_t*) leQueRemFirst (channel->message_list);


  while (!mess) {
    if(pthread_cond_wait(&(channel->wait_for_messages), &(channel->mutex)) != 0) {
        fprintf(stderr, "\nErro ao esperar pela variavel de condicao do canal (%d,%d)\n", tarefaOrig, tarefaDest);
        return -1;
      }
    mess = (Message_t*) leQueRemFirst (channel->message_list);
  }

  copysize = (mess->mess_size<tamanho) ? mess->mess_size : tamanho;
  memcpy(buffer, mess->contents, copysize);

  if (channel_capacity >0) {
    free(mess->contents);
    free(mess);
  }
  else
    mess->consumed = 1;

  if(pthread_cond_signal(&(channel->wait_for_free_space)) != 0) {
    fprintf(stderr, "\nErro ao desbloquear variavel de condicao do canal (%d,%d)\n", tarefaOrig, tarefaDest);
    return -1;
  }

  if(pthread_mutex_unlock(&(channel->mutex)) != 0) {
    fprintf(stderr, "\nErro ao desbloquear mutex do canal (%d,%d)\n", tarefaOrig, tarefaDest);
    return -1;
  }

  return copysize;
}


/*--------------------------------------------------------------------
| Function: enviarMensagem
| Description: Envia uma mensagem, indicada pelo ponteiro msg, da tarefaOrig
|              para a tarefaDest, com um dado tamanho. Se o canal nao estiver
|              cheio, os dados sao copiados para um tampao temporario (ou o
|              emissor fica bloqueado, caso a capacidade do canal seja 0).
|              Se o canal estiver cheio, o emissor e bloqueado ate a tarefa
|              destino ler mensagens do canal.
|              Em caso de sucesso devolve o tamanho da mensagem.
|              Em caso de erro devolve -1.
---------------------------------------------------------------------*/

int enviarMensagem(int tarefaOrig, int tarefaDest, void *msg, int tamanho) {
  Channel_t      *channel;
  Message_t      *mess;

  mess = (Message_t*) malloc (sizeof(Message_t));

  if(mess == NULL) {
    fprintf(stderr, "\nErro ao alocar memoria para mensagem\n");
    return -1;
  }

  leQueElemInit (mess);
  mess->mess_size = tamanho;

  /* if channels are buffered, copy message to a temporary buffer */
  if (channel_capacity > 0) {
    mess->contents = malloc (tamanho);
    mess->consumed = 0;

    if(mess->contents == NULL) {
      fprintf(stderr, "\nErro ao alocar memoria para mensagem\n");
      return -1;
    }

    memcpy(mess->contents, msg, tamanho);
  }

  /* if channels are not buffered, message will be copied directly from sender to receiver */
  else {
    mess->contents = msg;
    mess->consumed = 0;
  }

  channel = (Channel_t*) channel_array[tarefaDest*number_of_tasks+tarefaOrig];


  if(pthread_mutex_lock(&(channel->mutex)) != 0) {
    fprintf(stderr, "\nErro ao bloquear mutex do canal (%d,%d)\n", tarefaOrig, tarefaDest);
    return -1;
  }


  /* if channels are buffered, wait until there is buffer available */
  if (channel_capacity > 0) {
    while (leQueSize(channel->message_list) >= channel_capacity) {
      if(pthread_cond_wait(&(channel->wait_for_free_space), &(channel->mutex)) != 0) {
        fprintf(stderr, "\nErro ao esperar pela variavel de condicao do canal (%d,%d)\n", tarefaOrig, tarefaDest);
        return -1;
      }
    }
  }

  leQueInsLast (channel->message_list, mess);

  if (pthread_cond_signal(&(channel->wait_for_messages)) != 0) {
   fprintf(stderr, "\nErro ao esperar pela variavel de condicao do canal (%d,%d)\n", tarefaOrig, tarefaDest);
   return -1;
  }

  /* if channels are not buffered, wait for message to be read */
  if (channel_capacity == 0) {
    while (mess->consumed == 0) {
      if(pthread_cond_wait(&(channel->wait_for_free_space), &(channel->mutex)) != 0) {
        fprintf(stderr, "\nErro ao esperar pela variavel de condicao do canal (%d,%d)\n", tarefaOrig, tarefaDest);
        return -1;
      }

    }
    free(mess);
  }

  if(pthread_mutex_unlock(&(channel->mutex)) != 0) {
    fprintf(stderr, "\nErro ao desbloquear mutex do canal (%d,%d)\n", tarefaOrig, tarefaDest);
    return -1;
  }

  return tamanho;
}
