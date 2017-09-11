#Rafael Pestana de Andrade
#n 86503
#LEIC-AL 2016/2017
#Projeto 2: Cifra de Playfair



#--------------------------------------------------
#Tipos abstratos de dados
#-------------------------------------------------


#1) Funcoes auxiliares: Estas funcoes ajudam na criacao e manipulacao
#   de tipos abstratos de dados.

def inteiro_positivo(x):
	"""
	-Verifica se o argumento = numero inteiro e positivo (ou zero)

	Input:
	-x: elemento a ser testado
	
	Output:
	-Booleano

	Funcoes externas ao Python usadas: --
	Nota:usada no tipo Posicao (construtor e reconhecedor)
	"""

	if isinstance(x, int) and x>=0:
		return True
	else:
		return False



def tira_espacos(str):
	"""
	-Retira todos os espacos existentes numa cadeia de caracteres

	Input:
	-str: cadeia de caracteres

	Output:
	-cod:  cadeia de caracteres sem espacos entre palavras
	
	Funcoes externas usadas:--
	Nota: usada na funcao digramas e no tipo Chave (f. auxiliar gera_ordem)
	"""
	res=''
	for char in str:
		if char!= ' ':
			res+=char
	return res



def gera_ordem(l,mgc):
	"""
	-Funcao auxiliar para a geracao de chaves

	Input:
	-l: tuplo com as 25 letras usadas na chave
	-mgc (mensagem de geracao de chave): cadeia de caracteres que inicia a construcao da chave
	
	Output:
	-ordem: lista contendo todos os caracteres de <l>, em que os primeiros sao os de <mgc>

	Funcoes externas ao Python usadas: tira_espaco
	Nota: usada no tipo Chave(construtores)
	"""


	#1o passo: formatar mgc, tirando espacos e letras repetidas
	ordem=[]
	for char in tira_espacos(mgc):
		if char not in ordem:
			ordem+=[char]
	
	#2o passo: adicionar os caracteres definidos em <l> que faltam
	for char in l:
		if char not in ordem:
			ordem+=[char]

	return ordem



#_________________________Tipo Posicao_____________________________
#
#Representacao interna: tuplo (l,c); l=n linha e c=n coluna


#Construtor:
def faz_pos(l,c):
	"""
	-Construtor do tipo abstrato posicao

	Input:
	-l,c: numeros inteiros entre 0 e 4 referentes a uma posicao

	Output:
	-posicao: tipo abstrato de dados imutavel que contem a componente 'linha' e 'coluna'

	Funcoes externas ao Python usadas: inteiro_positivo

	"""

	if inteiro_positivo(l) and inteiro_positivo(c):
		return (l,c)
	else:
		raise ValueError('faz_pos: argumentos errados')

#Seletor:
def linha_pos(p):
	"""
	-Seletor da componente 'linha' do tipo abstrato posicao

	Input:
	-p: um elemento do tipo posicao

	Output:
	-Valor numerico entre 0 e 4 correspondente ao componente 'linha' de <p>
	
	Funcoes externas ao Python usadas: --
	
	"""
	return  p[0]


def coluna_pos(p):
	"""
	-Seletor da componente 'coluna' do tipo abstrato posicao

	Input:
	-p: um elemento do tipo posicao

	Output:
	-Valor numerico entre 0 e 4 correspondente ao componente 'coluna' de <p>

	Funcoes externas ao Python usadas: --

	"""
	return p[1]



#Reconhecedor:
def e_pos(x):
	"""
	-Reconhecedor do tipo abstrato posicao

	Input:
	-p: um elemento do tipo posicao

	Output:
	-Valor booleano; True se x pertence ao tipo pos e False caso contrario

	Funcoes externas ao Python usadas: inteiro_positivo
	"""

	if isinstance(x, tuple) and len(x)==2 and inteiro_positivo(x[0]) and inteiro_positivo(x[1]):
		return True
	else:
		return False

#Testes:
def pos_iguais(p1,p2):
	"""
	-Teste do tipo abstrato posicao

	Input:
	-p1,p2: dois elementos do tipo posicao

	Output:
	-Valor booleano; True se pos1=pos2 e False caso contrario

	Funcoes externas ao Python usadas: linha_pos(),coluna_pos()
	"""

	if linha_pos(p1)==linha_pos(p2) and coluna_pos(p1)==coluna_pos(p2):
		return True
	else:
		return False



#_________________________Tipo Chave______________________
#
#Representacao interna: Lista contendo 5 elementos; cada
#           elemento uma lista com 5 caracteres
#
#o tipo Chave e um tipo mutavel


#constante-o universo de 25 caracteres usados
L=('A','B','C','D','E','F','G','H','I','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z')


#Construtores

def gera_chave_linhas(l,mgc):
	"""
	-Construtor do tipo abstrato Chave

	Input:
	-l: tuplo com as 25 letras usadas na chave
	-mgc (mensagem de geracao de chave): cadeia de caracteres que inicia a construcao da chave

	Output:
	-chave: elemento do tipo abstrato chave, que foi gerada em linhas

	Funcoes externas ao Python usadas: gera_ordem
	"""
	
	#1o passo: teste dos argumentos
	if not isinstance( mgc, str) or not isinstance( l, tuple) or len(l)!= 25:
		raise ValueError('gera_chave_linhas: argumentos errados')
	for char in l:
		if char not in L:
			raise ValueError('gera_chave_linhas: argumentos errados')
	for char in L:
		if char not in l:
			raise ValueError('gera_chave_linhas: argumentos errados')
	for char in tira_espacos(mgc):
		if char not in L:
			raise ValueError('gera_chave_linhas: argumentos errados')


	#2o passo: colocar os caracteres na ordem pretendida
	ordem= gera_ordem(l,mgc)
	chave= []
	for i in range(5):
		chave+= [ordem[(i*5):(i*5+5)]]
	
	return chave


def gera_chave_espiral(l,mgc,s,pos):
	"""
	-Construtor do tipo abstrato Chave

	Input:
	-l: tuplo com as 25 letras usadas na chave
	-mgc (mensagem de geracao de chave): cadeia de caracteres que inicia a construcao da chave
	-s: caractere que define a direcao da espiral, pode ser 'r' (sentido do relogio) ou 'c' (sentido inverso)
	-pos: elemento do tipo Posicao que define o canto onde a espiral inicia


	Output:
	-chave: elemento do tipo abstrato chave, que foi gerada em espiral, consoante <s> e <pos>

	Funcoes externas ao Python usadas: gera_ordem, espelho_linhas, espelho_colunas, Seletores e Reconhecedor do tipo Posicao
	"""
	
	def espelho_linhas(lst):
		"""
		Pega numa chave e inverte cada linha, mantendo a sua ordem na chave
		"""
		res=[]
		for linha in lst:
			linha_res= linha[::-1]
			res+= [linha_res]
		return res

	def espelho_colunas(lst):
		"""
		Pega numa chave e inverte a ordem das linhas na chave
		"""
		res=[]
		for linha in lst:
			res= [linha]+res
		return res

	#1o passo: teste dos argumentos, testando tambem <s> e <pos>
	if not isinstance( mgc, str) or not isinstance( l, tuple) or len(l)!= 25:
		raise ValueError('gera_chave_espiral: argumentos errados')
	for char in l:
		if char not in L:
			raise ValueError('gera_chave_espiral: argumentos errados')
	for char in L:
		if char not in l:
			raise ValueError('gera_chave_espiral: argumentos errados')

	for char in tira_espacos(mgc):
		if char not in L:
			raise ValueError('gera_chave_espiral: argumentos errados')

	if not (s=='r' or s=='c'):
		raise ValueError('gera_chave_espiral: argumentos errados')

	if not e_pos(pos):
		raise ValueError('gera_chave_espiral: argumentos errados')

	elif (linha_pos(pos)!=4 and linha_pos(pos)!=0) or (coluna_pos(pos)!=0 and coluna_pos(pos)!= 4):
		raise ValueError('gera_chave_espiral: argumentos errados')


	
	#2o passo: por os caracteres em ordem de colocacao na espiral
	ordem= gera_ordem(l,mgc)
	

	#3o passo: gerar uma ordem de colocacao em espiral (indices)

	#Casos base:
	r_0_0=[[0,1,2,3,4],[15,16,17,18,5],[14,23,24,19,6],[13,22,21,20,7],[12,11,10,9, 8]]
	r_4_0=[[4,5,6,7,8],[ 3,18,19,20,9],[2,17,24,21,10],[1,16,23,22,11],[0,15,14,13,12]]

	if s=='r':
		if coluna_pos(pos)==0:
			if linha_pos(pos)== 0:
				#'r', (0,0)
				chave=r_0_0
			else:
				#'r', (4,0)
				chave=r_4_0
		else:
			if linha_pos(pos)==4:
				#'r', (4,4)
				chave=espelho_linhas(espelho_colunas(r_0_0))
			else:
				#'r', (4,0)
				chave=espelho_linhas(espelho_colunas(r_4_0))
	elif s=='c':
		if coluna_pos(pos)==4:
			if linha_pos(pos)==0:
				#'c', (0,4)
				chave= espelho_linhas(r_0_0)
			else:
				#'c', (4,4)
				chave= espelho_linhas(r_4_0)
		else:
			if linha_pos(pos)==4:
				#'c',(4,0)
				chave= espelho_colunas(r_0_0)
			else:
				#'c',(0,0)
				chave= espelho_colunas(r_4_0)

	#4o passo: por os caracteres nas posicoes correspondentes
	for l in range(len(chave)):
		for i in range(len(chave[l])):
			chave[l][i]= ordem[chave[l][i]]

	return chave



#Seletor
def ref_chave(c,p):
	"""
	-Seletor do tipo abstrato Chave

	Input:
	-c: elemento do tipo abstrato Chave
	-p: elemento do tipo abstrato Posicao


	Output:
	-elemento de <c> referido pela posicao <p>

	Funcoes externas ao Python usadas: Seletores do tipo Posicao (linha_pos, coluna_pos)
	"""
	
	return c[linha_pos(p)][coluna_pos(p)]


#Modificador

def muda_chave(c,p,l):
	"""
	-Modificador do tipo abstrato Chave
	
	Input:
	-c: elemento do tipo abstrato Chave
	-p: elemento do tipo abstrato Posicao, referente a um dado ponto de <c>
	-l: um caractere

	Output:
	-c: a chave, contendo o caractere <l> na posicao <p>
	
	Funcoes externas ao Python usadas: Seletores do tipo Posicao (linha_pos, coluna_pos)
	"""
	c[linha_pos(p)][coluna_pos(p)]=l
	return c
	

#Reconhecedor

def e_chave(x):
	"""
	-Reconhecedor do tipo abstrato Chave

	Input:
	-x: elemento de qualquer tipo

	Output:
	-[Booleano] True se x for do tipo Chave, False se nao pertencer

	Funcoes externas ao Python usadas:--
	"""

	if not isinstance(x, list):
		return False
	elif len(x)!=5:
		return False
	for el in x:
		if not isinstance(el, list):
			return False
		elif len(el)!=5:
			return False
		for subel in el:
			if subel not in L:
				return False
	return True


#Transformador

def string_chave(c):
	"""
	-Transformador do tipo abstrato Chave

	Input:
	-c: elemento do tipo abstrato Chave

	Output:
	-cadeia: chave em forma de cadeia de caracteres; quando impressa, mostra chave em forma de quadrado

	Funcoes externas ao Python usadas:--
	"""
	cadeia=''
	
	for linha in c:
		for char in linha:
			cadeia+= char+' '	
		cadeia+= '\n'
	
	return cadeia




#-------------------------------------------------
#Funcoes
#-------------------------------------------------


def digramas(mens):
	"""
	-Antes de ser aplicada a cifra de Playfair, formata-se a cadeia de caracteres em digramas

	Input:
	-mens: cadeia de caracteres, (escrita em maiuscula)

	Output:
	-cod:  cadeia de caracteres formatada como necessario para a cifra de Playfair

	Funcoes externas usadas: tira_espacos
	"""
	
	def digramas_aux(cad,cod):
		#4 casos: acabou, falta 1 char, 2 char diferentes, 2 char iguais
		if len(cad)==0:
			return cod
		elif len(cad)==1:
			return cod+cad+'X'
		elif cad[0]!=cad[1]:
			return digramas_aux(cad[2:],cod+cad[:2])
		else:
			return digramas_aux(cad[1:],cod+cad[0]+'X')
	
	return digramas_aux(tira_espacos(mens),'')


def figura(digrm, chave):
	"""
	-Indica que figura as letras de <digrm> formam na <chave>, bem como as suas posicoes respetivas


	Input:
	-digrm: cadeia de 2 caracteres pertencente a chave (em principio)
	-chave: elemento do tipo Chave que serve de base a codificacao

	Output:
	-res:tuplo de tres elementos:
		-'l','c', ou 'r': caractere que indica a figura formada pelos caracteres de <diagrm>
		-pos1: elemento do tipo Posicao referente ao 1o caractere de <digrm> em <chave>
		-pos2: elemento do tipo Posicao referente ao 2o caractere de <digrm> em <chave>
	
	Funcoes externas usadas:Construtor e Seletores do tipo Posicao, Seletor do tipo Chave
	"""
	
	#tuplo com as posicoes dos dois caracteres
	res=()

	#1o passo: encontrar as letras de <digrm> em <chave>
	for l in range(5):
		for c in range(5):
			if   digrm[0]== ref_chave(chave, faz_pos(l,c)):
				res= (faz_pos(l,c),)+res
			if digrm[1]== ref_chave(chave,faz_pos(l,c)):
				res= res+(faz_pos(l,c),)
	

	#2o passo: determinar a figura
	if linha_pos(res[0])==linha_pos(res[1]):
		res= ('l',)+res             #em linha
	elif coluna_pos(res[0])==coluna_pos(res[1]):
		res= ('c',)+res             #em coluna
	else:
		res= ('r',)+res             #em retangulo

	
	return res



def codifica_l(pos1,pos2,inc):
	"""
	-Codifica ou descodifica duas posicoes em linha segundo as regras da cifra de Playfair


	Input:
	-pos1,pos2: elementos tipo Posicao, referentes a caracteres (um cada)
	-inc: valor 1 ou -1 que determina se a funcao codifica ou descodifica, respetivamente

	Output:
	-tuplo de dois elementos:
		-pos1_cod: <pos1> apos a [des]codificacao
		-pos2_cod: <pos2> apos a [des]codificacao
	
	Funcoes externas usadas:Construtor e Seletores do tipo Posicao
	"""

	#Se inc= 1, incrementa-se as colunas de pos1, pos2
	#Se inc=-1, decrementa-se as colunas de pos1, pos2
	
	coluna1=coluna_pos(pos1)
	coluna2=coluna_pos(pos2)

	#Para nao sair do quadrado
	coluna1_cod= coluna1+inc
	if   coluna1_cod== -1:
		coluna1_cod=4
	elif coluna1_cod== 5:
		coluna1_cod=0


	#Para nao sair do quadrado
	coluna2_cod= coluna2+inc
	if   coluna2_cod== -1:
		coluna2_cod=4
	elif coluna2_cod== 5:
		coluna2_cod=0

	
	pos1_cod=faz_pos(linha_pos(pos1), coluna1_cod)
	pos2_cod=faz_pos(linha_pos(pos2), coluna2_cod)


	return (pos1_cod, pos2_cod)


def codifica_c(pos1,pos2,inc):
	"""
	-Codifica ou descodifica duas posicoes em coluna segundo as regras da cifra de Playfair


	Input:
	-pos1,pos2: elementos tipo Posicao, referentes a caracteres (um cada)
	-inc: valor 1 ou -1 que determina se a funcao codifica ou descodifica, respetivamente

	Output:
	-tuplo de dois elementos
		-pos1_cod: <pos1> apos a [des]codificacao
		-pos2_cod: <pos2> apos a [des]codificacao
	
	Funcoes externas usadas:Construtor e Seletores do tipo Posicao
	"""
	
	#Se inc= 1, incrementa-se as linhas de pos1, pos2
	#Se inc=-1, decrementa-se as linhas de pos1, pos2
	
	linha1=linha_pos(pos1)
	linha2=linha_pos(pos2)

	#Para nao sair do quadrado
	linha1_cod= linha1+inc
	if   linha1_cod== -1:
		linha1_cod=4
	elif linha1_cod== 5:
		linha1_cod=0

	#Para nao sair do quadrado
	linha2_cod= linha2+inc
	if   linha2_cod== -1:
		linha2_cod=4
	elif linha2_cod== 5:
		linha2_cod=0
	
	
	pos1_cod=faz_pos(linha1_cod,coluna_pos(pos1))
	pos2_cod=faz_pos(linha2_cod,coluna_pos(pos2))


	return (pos1_cod, pos2_cod)


def codifica_r(pos1,pos2):
	"""
	-Codifica ou descodifica duas posicoes em retangulo segundo as regras da cifra de Playfair


	Input:
	-pos1,pos2: elementos tipo Posicao

	Output:
	-tuplo de dois elementos
		-pos1_cod: <pos1> apos a [des]codificacao
		-pos2_cod: <pos2> apos a [des]codificacao
	
	Funcoes externas usadas:Construtor e Seletores do tipo Posicao
	"""

	#Neste caso, corresponde a uma troca de colunas
	pos1_cod=faz_pos(linha_pos(pos1), coluna_pos(pos2))
	pos2_cod=faz_pos(linha_pos(pos2), coluna_pos(pos1))

	return (pos1_cod, pos2_cod)


def codifica_digrama(digrm, chave, inc):
	"""
	-Codifica ou descodifica um digrama segundo a posicao que forma em <chave>

	Input:
	-digrm: digrama (cadeia de 2 caracteres)
	-chave: elemento do tipo Chave que serve de base a codificacao
	-inc: valor 1 ou -1 que determina se a funcao codifica ou descodifica, respetivamente

	Output:
	-digrama correspondente a transformacao de <digrm> segundo os argumentos

	Funcoes externas usadas: figura, codifica_c,codifica_l, codifica_r, ref_chave
	"""

	#1o passo: identificar a figura do digrama
	fig= figura(digrm, chave)

	#2o passo: obter as coordenadas de caracteres depois de codificados
	if fig[0] == 'l':
		digrm_cod_pos = codifica_l(fig[1],fig[2],inc)
	elif fig[0] == 'c':
		digrm_cod_pos = codifica_c(fig[1],fig[2], inc)
	else:
		digrm_cod_pos = codifica_r(fig[1],fig[2])

	#3o passo: escrever os caracteres em relacao a chave usada
	return ref_chave(chave, digrm_cod_pos[0])+ref_chave(chave, digrm_cod_pos[1])


def codifica(mens, chave, inc):
	"""
	-Codifica ou descodifica uma mensagem segundo a <chave>, usando a cifra de Playfair

	Input:
	-digrm: digrama (cadeia de 2 caracteres)
	-chave: elemento do tipo Chave que serve de base a codificacao
	-inc: valor 1 ou -1 que determina se a funcao codifica ou descodifica, respetivamente

	Output:
	-digrama correspondente a transformacao de <digrm> segundo os argumentos

	Funcoes externas usadas: figura, codifica_c,codifica_l, codifica_r, ref_chave
	"""


	#1o passo: formatar a mensagem em forma de digramas
	mens= digramas(mens)

	#2o passo: iterar codifica_digrama
	res=''
	while len(mens) !=0:
		digrm= mens[:2]
		res += codifica_digrama(digrm, chave, inc)
		mens = mens[2:]

	return res





