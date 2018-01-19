/*
// Biblioteca de troca de mensagens, versao 3
// Sistemas Operativos, DEI/IST/ULisboa 2017-18
*/

#ifndef MPLIB_H
#define MPLIB_H

/*--------------------------------------------------------------------
| Function: inicializarMPlib
| Description: Inicializa a MPlib com ntasks*ntasks canais, cada um com
|              capacidade igual a capacidade_de_cada_canal.
|              Em caso de sucesso devolve 0.
|              Em caso de erro devolve -1.
|
|
| Function: libertarMPlib
| Description: Liberta a memória alocada pela MPlib. Devolve void.
|              Em caso de erro, o processo é terminado.
|
|
| Function: receberMensagem
| Description: Recebe uma mensagem da tarefaOrig para a tarefaDest,
|              com um dado tamanho máximo, e coloca a mensagem no buffer
|              recebido. Se o canal não estiver vazio, uma mensagem é removida
|              e colocada no buffer. Caso contrário, o recetor é bloqueado
|              até a tarefa de origem enviar mensagens para o canal.
|              Em caso de sucesso devolve o tamanho da mensagem recebida.
|              Em caso de erro devolve -1.
|
|
| Function: enviarMensagem
| Description: Envia uma mensagem, indicada pelo ponteiro msg, da tarefaOrig 
|              para a tarefaDest, com um dado tamanho. Se o canal não estiver
|              cheio, os dados são copiados para um tampão temporário (ou o 
|              emissor fica bloqueado, caso a capacidade do canal seja 0). 
|              Se o canal estiver cheio, o emissor é bloqueado até a tarefa 
|              destino ler mensagens do canal.
|              Em caso de sucesso devolve o tamanho da mensagem.
|              Em caso de erro devolve -1.
|
|
| Nota: as funções receberMensagem e enviarMensagem só devem ser chamadas
| após a MPlis ter sido inicializada. Caso contrário, o seu comportamento
| é imprevisto.
|
---------------------------------------------------------------------*/


int inicializarMPlib(int capacidade_de_cada_canal, int ntasks);
void libertarMPlib();

int receberMensagem(int tarefaOrig, int tarefaDest, void *buffer, int tamanho);
int enviarMensagem(int tarefaOrig, int tarefaDest, void *msg, int tamanho);

#endif
