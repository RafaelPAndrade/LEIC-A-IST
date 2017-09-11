#Rafael Pestana de Andrade
#rafael.pestana.andrade@tecnico.ulisboa.pt


#coding:utf-8
#para fazer load de forma dinâmica dentro da shell do python, correr
# >>>exec(open("./exerciciosfp_21-X.py").read())
#no diretório que contém o ficheiro


#1- funcao ord(chr(numero))=numero
"""
def lista_codigos(str):
	res=[]
	for e in str:
		cod=ord(e)
		res=res+[cod]
	return res
"""


#2
"""
def remove_multiplos(lst, const):

	for i in range(len(lst)-1,-1,-1):
		if lst[i]%const== 0:
			del(lst[i])
	return lst
"""


#3

def junta_ordenadas(lst1,lst2):

	res=[]
	i1=0
	i2=0
	done=False

	while (i1)<len(lst1) and (i2)<len(lst2):
		if lst1[i1]<lst2[i2]:
			res+=[lst1[i1]]
			i1+=1
		else:
			res+=[lst2[i2]]
			i2+=1
	return res+lst1[i1:]+lst2[i2:]






#4
"""
def soma_cumulativa(lst):

	def prox_elemento(lst,i):
		soma=0
		for e in lst[:i+1]:
			soma+=e
		return soma


	res=[]

	for i in range(len(lst)):
		res+=[prox_elemento(lst,i)]
	return res
"""


#5
"""
def ordena(lst):


	tabela=[]
	for i in range(len(lst)):
		tabela+= [i]


	maior=len(lst)

	trocou=True

	while trocou:
		trocou=False
		for i in range(maior-1):
			if lst[tabela[i]]>lst[tabela[i+1]]:
				trocou= True
				tabela[i],tabela[i+1]=tabela[i+1],tabela[i]

		maior-=1
	return tabela

"""


#6

def elemento_matriz(m, i, j):

	if not isinstance(m, list):
		raise TypeError("Matriz tem de ser uma lista")

	for e in range(len(m)):
		if not isinstance(m[e],list):
			raise TypeError("Linha da matriz tem de ser uma lista")


	if not isinstance(i, int) or i>=len(m) or i<0:
		print("Índice inválido: linha",i)
	if not isinstance(j, int) or j>=len(m[i]) or j<0:
		print("Índice inválido: coluna", j)

	else:
		return m[i][j]



#7-usou-se o 6)


def print_matriz(m):

	for i in range(len(m)):
		for j in range(len(m[i])):
			print(elemento_matriz(m,i,j),end="   ")
		print()


#8-usou-se o 6)


def soma_matrizes(m1,m2):
	#assumindo que as matrizes têm linhas e colunas iguais;
	#se não, vai dar erro
	soma=[]
	for i in range(len(m1)):
		linha=[]
		for j in range(len(m1[i])):
			elemento= elemento_matriz(m1,i,j)+elemento_matriz(m2,i,j)
			linha+= [elemento]
		soma+= [linha]

	return soma


#9- usou-se o 6)

def produto_matriz(m1,m2):
	#assumindo que as matrizes têm formatos que deixam haver multiplicação;
	#se não, vai dar erro
	res=[]
	k_max= len(m1[0])
	def somatorio(m1,m2,i,k_max,j):
		soma=0
		for k in range(k_max):
			soma+= elemento_matriz(m1,i,k)*elemento_matriz(m2,k,j)
		return soma


	for i in range(len(m1)):
		linha=[]
		for j in range(len(m2[0])):
			elemento= somatorio(m1,m2,i,k_max,j)
			linha+=[elemento]
		res+=[linha]

	return res


#10- já foi feito para tuplos; copy paste para referência do 3º trabalho:

def seq_racaman(n):

	res=[]

	for i in range(n):
		if i==0:
			e=0
		elif res[i-1]>i and (res[i-1]-i) not in res:
			e=res[i-1]-i
		else:
			e=res[i-1]+i
		res=res+[e]
	return res














