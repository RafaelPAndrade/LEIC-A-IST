/*********************************************************\
|IAED 2016/17 Projeto 1 - forum de mensagens
|Ficheiro: header.c
|
|Livio Mendes Costa
|Rafael Pestana de Andrade
\*********************************************************/

//O numero maximo de caracteres numa frase
# define MAX_LEN_FRASE 140

//O numero maximo de utilizadores
# define MAX_USERS 1000

//O numero maximo de mensagens no forum
# define MAX_MSGS 10000

//Estrutura mensagem. Contem
//  -user_id: numero de utilizador que postou a mensagem;
//  -frase: sequencia de caracteres
typedef struct mensagem{
	int user_id;
	char frase[MAX_LEN_FRASE+1];
}	Mensagem;


/*********************************************************\
------------------------PROTOTIPOS------------------------
\*********************************************************/

void funcao_A(Mensagem forum[], const int n_mensagem, int mensagens_por_user[], int *p_max_cmp_frase, int *p_n_msgs_user_mais_ativo);

void funcao_L(const Mensagem forum[], const int n_mensagens);

void funcao_U(const Mensagem forum[], const int n_mensagens, const int mensagens_por_user[]);

void funcao_O(const Mensagem forum[], const int n_mensagens, const int max_cmp_frase);

void funcao_T(const int mensagens_por_user[MAX_USERS], const int n_mensagens_mais_ativo);


void funcao_S(const Mensagem forum[],const int n_mensagens,int index[]);
int msgm_abaixo(const Mensagem msg1, const Mensagem msg2);
void merge(int index[], int l, int m, int r, const Mensagem forum[]);
void mergesort(int index[], int l, int r, const Mensagem forum[]);


void funcao_C(const Mensagem forum[],const int n_mensagens);
int n_ocorrencias(const char frase[], const char palavra[], const int comp_palavra);
