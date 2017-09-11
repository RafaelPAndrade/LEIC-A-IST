#Rafael Pestana de Andrade
#Semana 8 
#FP 2016/17, 1o semestre



#1
#
#a)o segundo dicionario, com as infos do americano
#
#b)dicionario composto por chaves 'nomep' e 'apelido'
#
#c)'Doe'
#
#d)'D'



#2(dict() construtor)
#iteracao
def agrupa_chave(lst):
	res={}

	for e in lst:
		if e[0] not in res:
			res[e[0]]= [e[1]]
		else:
			res[e[0]]+=[e[1]]
	return res


#3

#3a)nao usando dict
def baralho():
	"""no dict"""
	#listas de valores das cartas
	np_lst =['esp','copas','paus','ouros']
	vlr_lst=['A','2','3','4','5','6','7','8','9','10','J','Q','K']
	deck =[]

	for naipe in np_lst:
		for valor in vlr_lst:
			carta= {'np':naipe, 'vlr':valor}
			deck+= [carta]
	return deck


#3b)

def baralha(deck):
	
	def rand52():
		from random import random
		return round(random()*51)

	def aux(deck,i_carta):
		if i_carta==52:
			return deck
		else:
			deck[i_carta],deck[rand52()]= deck[rand52()],deck[i_carta]
			return aux(deck,i_carta+1)
	return aux(deck, 0)



#3c)
def distribui(deck):
	if len(deck)%4!=0 or len(deck)==0:
		raise ValueError('distribui: arg must be divisible by 4')
	else:

		a=[]
		b=[]
		c=[]
		d=[]

		for i in range(len(deck)//4):
			a+=[deck[i*4]]
			b+=[deck[i*4+1]]
			c+=[deck[i*4+2]]
			d+=[deck[i*4+3]]
	return([a,b,c,d])



#4

def metabolismo(d):
	#formatacao de d:
	#sexo-idade-altura-peso
	met={}
	for nome in d:
		if d[nome][0]== 'M':
			met[nome]= 66 + (6.8*d[nome][1]) + (12.9*d[nome][2]) + (6.63*d[nome][3])
		elif d[nome][0]== 'F':
			met[nome]= 665 + (4.7*d[nome][1]) + (4.7*d[nome][2]) + (4.3*d[nome][3])
	return met


#5->bug, palavra '' no fim
def cc(str):

	#lista das palavras
	def palavras(str):

		def parte_aux(str, words, word):
			if len(str)==0:
				return words+[word]
			elif str[0]== ' ':
				return parte_aux(str[1:],words+[word],'')
			else:
				return parte_aux(str[1:],words, word+str[0])

		return parte_aux(str, [], '')


	#pega na lista das palavras e cria dic+conta palavras
	def cria_dic(palavras_lst):
		res={}
		for e in palavras_lst:
			if e not in res:
				res[e] =1
			else:
				res[e]+=1
		return res

	return cria_dic(palavras(str))


#6

def mostra_ordenado(dict):
	res=[]			#lista com as chaves por ordem
	
	for chave in dict:	#coloca-se tudo em res
		res+=[chave] 

				#inicio do bubble sort
	Lim_sup=len(res)-1	
	No_trocas=False

	while not No_trocas:
		No_trocas= True	#este valor altera-se a seguir,
		for i in range(Lim_sup):
			if res[i]>res[i+1]:
				#a troca aqui
				res[i], res[i+1]= res[i+1], res[i]
				No_trocas= False
		Lim_sup-= 1

				#impressao dos resultados
	for chave in res:
		print(chave+'\t',dict[chave])

	

#7
#a)
def escreve_esparsa(dict):

	#1o passo: ver as dimensoes da matriz
	linha=0
	coluna=0
	for tuplo in dict:
		if tuplo[0]>linha:
			linha=tuplo[0]
		if tuplo[1]> coluna:
			coluna=tuplo[1]

	#2o passo: escrever sequencialmente tudo
	for l in range(linha+1):
		for c in range(coluna+1):
			if (l,c) in dict:
				print(dict[(l,c)],end=' ')
			else:
				print(0,end=' ')
		
		print()



#7b)
def soma_esparsa(c1,c2):

	for chave in c2:
		if not chave in c1:
			c1[chave]= c2[chave]
		else:
			c1[chave]+= c2[chave]
			
	return c1


#8

def mais_antigo(bib):
	#por observacao, o mais antigo esta na posicao:
	#bib[x]['ano']; e o titulo em
	#bib[x]['titulo']

	ano_velho= 2100
	antigo= 'Arquitetura do Século XXII'
	for livro in bib:
		if eval(livro['ano'])<ano_velho:
			antigo= livro['titulo']
	return(antigo)


#9

def ataques_rainha(jogo):

	#traduzir notacao do xadrez para algo sano
	linha=[8,7,6,5,4,3,2,1]
	coluna=['A','B','D','E','F','G','H']

	#encontrar as rainhas
	#-rainha branca
	p_rainha_b==()
	for posicao in jogo:
		if jogo[posicao]== ('branca','rainha'):
			p_rainha_b= posicao
			break
	#-rainha preta
	p_rainha_p==()
	for posicao in jogo:
		if jogo[posicao]== ('preta','rainha'):
			p_rainha_p= posicao
			break
	
	"""
	#traduzir
	for l in range(linha):
		for c in range(coluna):
			if p_rainha_p==(linha[l],coluna[c]):
				p_rainha_p=(l,c)
			elif p_rainha_b==(linha[l],coluna[c]):
				p_rainha_p=(l,c)
	"""
	
	#ver moves para rainha branca
	moves_b=[]
	if p_rainha_b!= ():
		#ver na vertical(fixa a coluna)-->(n, p[1])
		for i in linha:
			pos=(i, p_rainha_b[1])
			if pos in jogo:
				if jogo[pos][0]=='preta':
					moves_b+= [jogo[pos][1], pos]
		#ver na horizontal(fixa a linha)-->(p[0],n)
		for i in coluna:
			pos=(p_rainha_b[0],i)
			if pos in jogo:
				if jogo[pos][0]=='preta':
					moves_b+= [jogo[pos][1], pos]
