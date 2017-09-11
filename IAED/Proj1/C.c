/*********************************************************\
|IAED 2016/17 Projeto 1 - forum de mensagens
|Ficheiro: C.c
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*********************************************************/

#include <stdio.h>
#include <string.h>
#include "header.c"

/****************************************************************************\
 Funcao funcao_C (numero de ocorrencias de uma palavra):
    -Le uma <palavra>
    -Compara <palavra> com todas as frases de forum
    -Imprime o numero de ocorrencias de <palavra>

	|Argumentos:
	|	-forum: lista de Mensagens (vide header.c)
	|	-n_mensagens: numero de mensagens no <forum>
	|
	|Input:
	|	-palavra: sequencia de caracteres sem espacos
	|
	|Output:
	|	-Numero de ocurrencias da palavra no <forum>
	|
	|Return:
	|	-void
	|
\****************************************************************************/

void funcao_C(const Mensagem forum[],const int n_mensagens)
{
	int numero_occ=0,i,c,p=0;
	char palavra[MAX_LEN_FRASE];

	//Elimina o espaco em branco antes da palavra
	getchar();

	//Le a palavra
	while ( (c=getchar())!='\n' && c!=EOF)
		palavra[p++]=c;
	palavra[p]='\0';

	for(i=0;i<n_mensagens;i++)
		numero_occ+=n_ocorrencias(forum[i].frase, palavra, p);

	printf("*WORD %s:%d\n",palavra,numero_occ);
}



//Verifica quantas ocorrencias de <palavra> houve em cada mensagem
int n_ocorrencias(const char frase[], const char palavra[], const int comp_palavra)
{
  //Indice da <frase>
	int i;
	
	//Indice de <palavra>, no sitio onde estamos a comparar
	int j=0;

	//Indica que o caractere anterior foi um caractere branco ou foi um caractere que fez match
	int flag=1;

	int num_oc=0;
	const int comp_frase=strlen(frase);


	for(i=0;i<=comp_frase;i++)
	{

    //Se os caracteres frase[i] e palavra[j] sao iguais, avanca-se para j+1
		if(frase[i]==palavra[j] && palavra[j]!='\0' && flag==1)
			j++;
		
		//Se houver uma diferenca e o caracterer diferente for um caractere separador
		else if(frase[i]==' ' || frase[i]=='\0' || frase[i]=='.' || frase[i]==',' || frase[i]=='\t' || frase[i]==';' || frase[i]=='\n')
		{
		  
		  //se ja tivermos percorrido a palavra, conta como ocorrencia
			num_oc = (j==comp_palavra) ? num_oc+1 : num_oc;
			j=0;
			flag=1;
		}
		
		//Houve uma diferenca, mas o caractere diferente nao foi um caractere branco --> nao conta como uma match
		else
			j=flag=0;
	
	}

	return num_oc;
}