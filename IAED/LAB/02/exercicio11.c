# include <stdio.h>


int main(){

	int c, f_linha_vazia=1;
	long Maiusculas, minusculas, digitos, linhas, linhas_n_vazias;
	Maiusculas=minusculas=digitos=linhas=linhas_n_vazias=0;

	while((c=getchar())!=EOF){
		if (c>='a' && c<='z'){
			++minusculas;
			f_linha_vazia=0;}
		else if (c>='A' && c<='Z'){
			++Maiusculas;
			f_linha_vazia=0;}
		else if (c=='\n'){
			++linhas;
			if (f_linha_vazia==0){
				++linhas_n_vazias;
				f_linha_vazia=1;
			}}
		else if (c>='0' && c<='9'){
			++digitos;
			f_linha_vazia=0;}
	}

	putchar('\n');
	printf("Número de linhas: %ld\n", linhas);
		printf("\t-Não vazias: %ld\n", linhas_n_vazias);
		printf("\t-Vazias: %ld\n", linhas-linhas_n_vazias);
	printf("Número de Maiúsculas: %ld\n", Maiusculas);
	printf("Número de minusculas: %ld\n", minusculas);
	printf("Número de dígitos: %ld\n", digitos);

	return 0;
}
